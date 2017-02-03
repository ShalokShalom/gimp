/* GIMP - The GNU Image Manipulation Program
 * Copyright (C) 1995 Spencer Kimball and Peter Mattis
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "config.h"

#include <string.h>

#include <gegl.h>
#include <gtk/gtk.h>

#include "libgimpmath/gimpmath.h"
#include "libgimpwidgets/gimpwidgets.h"

#include "tools-types.h"

#include "config/gimpdisplayconfig.h"
#include "config/gimpguiconfig.h"

#include "core/gimp.h"
#include "core/gimp-cairo.h"
#include "core/gimpguide.h"
#include "core/gimpimage.h"
#include "core/gimpimage-guides.h"
#include "core/gimpimage-pick-layer.h"
#include "core/gimplayer.h"
#include "core/gimpimage-undo.h"
#include "core/gimplayermask.h"
#include "core/gimplayer-floating-selection.h"
#include "core/gimpundostack.h"

#include "widgets/gimphelp-ids.h"
#include "widgets/gimpwidgets-utils.h"

#include "display/gimpcanvasitem.h"
#include "display/gimpdisplay.h"
#include "display/gimpdisplayshell.h"
#include "display/gimpdisplayshell-appearance.h"
#include "display/gimpdisplayshell-selection.h"
#include "display/gimpdisplayshell-transform.h"

#include "gimpeditselectiontool.h"
#include "gimpguidetool.h"
#include "gimpmoveoptions.h"
#include "gimpmovetool.h"
#include "gimptoolcontrol.h"

#include "gimp-intl.h"


/*  local function prototypes  */

static void   gimp_move_tool_button_press   (GimpTool              *tool,
                                             const GimpCoords      *coords,
                                             guint32                time,
                                             GdkModifierType        state,
                                             GimpButtonPressType    press_type,
                                             GimpDisplay           *display);
static void   gimp_move_tool_button_release (GimpTool              *tool,
                                             const GimpCoords      *coords,
                                             guint32                time,
                                             GdkModifierType        state,
                                             GimpButtonReleaseType  release_type,
                                             GimpDisplay           *display);
static gboolean gimp_move_tool_key_press    (GimpTool              *tool,
                                             GdkEventKey           *kevent,
                                             GimpDisplay           *display);
static void   gimp_move_tool_modifier_key   (GimpTool              *tool,
                                             GdkModifierType        key,
                                             gboolean               press,
                                             GdkModifierType        state,
                                             GimpDisplay           *display);
static void   gimp_move_tool_oper_update    (GimpTool              *tool,
                                             const GimpCoords      *coords,
                                             GdkModifierType        state,
                                             gboolean               proximity,
                                             GimpDisplay           *display);
static void   gimp_move_tool_cursor_update  (GimpTool              *tool,
                                             const GimpCoords      *coords,
                                             GdkModifierType        state,
                                             GimpDisplay           *display);

static void   gimp_move_tool_draw           (GimpDrawTool          *draw_tool);


G_DEFINE_TYPE (GimpMoveTool, gimp_move_tool, GIMP_TYPE_DRAW_TOOL)

#define parent_class gimp_move_tool_parent_class


void
gimp_move_tool_register (GimpToolRegisterCallback  callback,
                         gpointer                  data)
{
  (* callback) (GIMP_TYPE_MOVE_TOOL,
                GIMP_TYPE_MOVE_OPTIONS,
                gimp_move_options_gui,
                0,
                "gimp-move-tool",
                C_("tool", "Move"),
                _("Move Tool: Move layers, selections, and other objects"),
                N_("_Move"), "M",
                NULL, GIMP_HELP_TOOL_MOVE,
                GIMP_STOCK_TOOL_MOVE,
                data);
}

static void
gimp_move_tool_class_init (GimpMoveToolClass *klass)
{
  GimpToolClass     *tool_class      = GIMP_TOOL_CLASS (klass);
  GimpDrawToolClass *draw_tool_class = GIMP_DRAW_TOOL_CLASS (klass);

  tool_class->button_press   = gimp_move_tool_button_press;
  tool_class->button_release = gimp_move_tool_button_release;
  tool_class->key_press      = gimp_move_tool_key_press;
  tool_class->modifier_key   = gimp_move_tool_modifier_key;
  tool_class->oper_update    = gimp_move_tool_oper_update;
  tool_class->cursor_update  = gimp_move_tool_cursor_update;

  draw_tool_class->draw      = gimp_move_tool_draw;
}

static void
gimp_move_tool_init (GimpMoveTool *move_tool)
{
  GimpTool *tool = GIMP_TOOL (move_tool);

  gimp_tool_control_set_snap_to            (tool->control, FALSE);
  gimp_tool_control_set_handle_empty_image (tool->control, TRUE);
  gimp_tool_control_set_tool_cursor        (tool->control,
                                            GIMP_TOOL_CURSOR_MOVE);

  move_tool->floating_layer     = NULL;
  move_tool->guide              = NULL;

  move_tool->saved_type         = GIMP_TRANSFORM_TYPE_LAYER;

  move_tool->old_active_layer   = NULL;
  move_tool->old_active_vectors = NULL;
}

static void
gimp_move_tool_button_press (GimpTool            *tool,
                             const GimpCoords    *coords,
                             guint32              time,
                             GdkModifierType      state,
                             GimpButtonPressType  press_type,
                             GimpDisplay         *display)
{
  GimpMoveTool     *move           = GIMP_MOVE_TOOL (tool);
  GimpMoveOptions  *options        = GIMP_MOVE_TOOL_GET_OPTIONS (tool);
  GimpDisplayShell *shell          = gimp_display_get_shell (display);
  GimpImage        *image          = gimp_display_get_image (display);
  GimpItem         *active_item    = NULL;
  const gchar      *null_message   = NULL;
  const gchar      *locked_message = NULL;

  tool->display = display;

  move->floating_layer     = NULL;
  move->guide              = NULL;

  if (! options->move_current)
    {
      if (options->move_type == GIMP_TRANSFORM_TYPE_PATH)
        {
          GimpVectors *vectors;

          if (gimp_draw_tool_on_vectors (GIMP_DRAW_TOOL (tool), display,
                                         coords, 7, 7,
                                         NULL, NULL, NULL, NULL, NULL,
                                         &vectors))
            {
              move->old_active_vectors =
                gimp_image_get_active_vectors (image);

              gimp_image_set_active_vectors (image, vectors);
            }
          else
            {
              /*  no path picked  */
              return;
            }
        }
      else if (options->move_type == GIMP_TRANSFORM_TYPE_LAYER)
        {
          GimpGuide  *guide;
          GimpLayer  *layer;
          const gint  snap_distance = display->config->snap_distance;

          if (gimp_display_shell_get_show_guides (shell) &&
              (guide = gimp_image_find_guide (image,
                                              coords->x, coords->y,
                                              FUNSCALEX (shell, snap_distance),
                                              FUNSCALEY (shell, snap_distance))))
            {
              move->guide = guide;

              gimp_guide_tool_start_edit (tool, display, guide);

              return;
            }
          else if ((layer = gimp_image_pick_layer (image,
                                                   coords->x,
                                                   coords->y)))
            {
              if (gimp_image_get_floating_selection (image) &&
                  ! gimp_layer_is_floating_sel (layer))
                {
                  /*  If there is a floating selection, and this aint it,
                   *  use the move tool to anchor it.
                   */
                  move->floating_layer =
                    gimp_image_get_floating_selection (image);

                  gimp_tool_control_activate (tool->control);

                  return;
                }
              else
                {
                  move->old_active_layer = gimp_image_get_active_layer (image);

                  gimp_image_set_active_layer (image, layer);
                }
            }
          else
            {
              /*  no guide and no layer picked  */

              return;
            }
        }
    }

  switch (options->move_type)
    {
    case GIMP_TRANSFORM_TYPE_PATH:
      {
        active_item    = GIMP_ITEM (gimp_image_get_active_vectors (image));
        null_message   = _("There is no path to move.");
        locked_message = _("The active path's position is locked.");

        if (active_item && ! gimp_item_is_position_locked (active_item))
          {
            gimp_tool_control_activate (tool->control);
            gimp_edit_selection_tool_start (tool, display, coords,
                                            GIMP_TRANSLATE_MODE_VECTORS,
                                            TRUE);
            return;
          }
      }
      break;

    case GIMP_TRANSFORM_TYPE_SELECTION:
      {
        active_item    = GIMP_ITEM (gimp_image_get_mask (image));
        /* cannot happen, so don't translate these messages */
        null_message   = "There is no selection to move.";
        locked_message = "The selection's position is locked.";

        if (active_item && ! gimp_item_is_position_locked (active_item))
          {
            if (! gimp_channel_is_empty (gimp_image_get_mask (image)))
              {
                gimp_tool_control_activate (tool->control);
                gimp_edit_selection_tool_start (tool, display, coords,
                                                GIMP_TRANSLATE_MODE_MASK,
                                                TRUE);
                return;
              }
            else
              locked_message = _("The selection is empty.");
          }
      }
      break;

    case GIMP_TRANSFORM_TYPE_LAYER:
      {
        active_item  = GIMP_ITEM (gimp_image_get_active_drawable (image));
        null_message = _("There is no layer to move.");

        if (GIMP_IS_LAYER_MASK (active_item))
          {
            locked_message = _("The active layer's position is locked.");

            if (! gimp_item_is_position_locked (active_item))
              {
                gimp_tool_control_activate (tool->control);
                gimp_edit_selection_tool_start (tool, display, coords,
                                                GIMP_TRANSLATE_MODE_LAYER_MASK,
                                                TRUE);
                return;
              }
          }
        else if (GIMP_IS_CHANNEL (active_item))
          {
            locked_message = _("The active channel's position is locked.");

            if (! gimp_item_is_position_locked (active_item))
              {
                gimp_tool_control_activate (tool->control);
                gimp_edit_selection_tool_start (tool, display, coords,
                                                GIMP_TRANSLATE_MODE_CHANNEL,
                                                TRUE);
                return;
              }
          }
        else if (GIMP_IS_LAYER (active_item))
          {
            locked_message = _("The active layer's position is locked.");

            if (! gimp_item_is_position_locked (active_item))
              {
                gimp_tool_control_activate (tool->control);
                gimp_edit_selection_tool_start (tool, display, coords,
                                                GIMP_TRANSLATE_MODE_LAYER,
                                                TRUE);
                return;
              }
          }
      }
      break;
    }

  if (! active_item)
    {
      gimp_tool_message_literal (tool, display, null_message);
      gimp_tool_control (tool, GIMP_TOOL_ACTION_HALT, display);
    }
  else
    {
      gimp_tool_message_literal (tool, display, locked_message);
      gimp_tool_control (tool, GIMP_TOOL_ACTION_HALT, display);
    }
}

static void
gimp_move_tool_button_release (GimpTool              *tool,
                               const GimpCoords      *coords,
                               guint32                time,
                               GdkModifierType        state,
                               GimpButtonReleaseType  release_type,
                               GimpDisplay           *display)
{
  GimpMoveTool  *move   = GIMP_MOVE_TOOL (tool);
  GimpGuiConfig *config = GIMP_GUI_CONFIG (display->gimp->config);
  GimpImage     *image  = gimp_display_get_image (display);
  gboolean       flush  = FALSE;

  gimp_tool_control_halt (tool->control);

  if (! config->move_tool_changes_active ||
      (release_type == GIMP_BUTTON_RELEASE_CANCEL))
    {
      if (move->old_active_layer)
        {
          gimp_image_set_active_layer (image, move->old_active_layer);
          move->old_active_layer = NULL;

          flush = TRUE;
        }

      if (move->old_active_vectors)
        {
          gimp_image_set_active_vectors (image, move->old_active_vectors);
          move->old_active_vectors = NULL;

          flush = TRUE;
        }
    }

  if (release_type != GIMP_BUTTON_RELEASE_CANCEL)
    {
      if (move->floating_layer)
        {
          floating_sel_anchor (move->floating_layer);

          flush = TRUE;
        }
    }

  if (flush)
    gimp_image_flush (image);
}

static gboolean
gimp_move_tool_key_press (GimpTool    *tool,
                          GdkEventKey *kevent,
                          GimpDisplay *display)
{
  GimpMoveOptions *options = GIMP_MOVE_TOOL_GET_OPTIONS (tool);

  return gimp_edit_selection_tool_translate (tool, kevent,
                                             options->move_type,
                                             display);
}

static void
gimp_move_tool_modifier_key (GimpTool        *tool,
                             GdkModifierType  key,
                             gboolean         press,
                             GdkModifierType  state,
                             GimpDisplay     *display)
{
  GimpMoveTool    *move    = GIMP_MOVE_TOOL (tool);
  GimpMoveOptions *options = GIMP_MOVE_TOOL_GET_OPTIONS (tool);

  if (key == gimp_get_extend_selection_mask ())
    {
      g_object_set (options, "move-current", ! options->move_current, NULL);
    }
  else if (key == GDK_MOD1_MASK ||
           key == gimp_get_toggle_behavior_mask ())
    {
      GimpTransformType button_type;

      button_type = options->move_type;

      if (press)
        {
          if (key == (state & (GDK_MOD1_MASK |
                               gimp_get_toggle_behavior_mask ())))
            {
              /*  first modifier pressed  */

              move->saved_type = options->move_type;
            }
        }
      else
        {
          if (! (state & (GDK_MOD1_MASK |
                          gimp_get_toggle_behavior_mask ())))
            {
              /*  last modifier released  */

              button_type = move->saved_type;
            }
        }

      if (state & GDK_MOD1_MASK)
        {
          button_type = GIMP_TRANSFORM_TYPE_SELECTION;
        }
      else if (state & gimp_get_toggle_behavior_mask ())
        {
          button_type = GIMP_TRANSFORM_TYPE_PATH;
        }

      if (button_type != options->move_type)
        {
          g_object_set (options, "move-type", button_type, NULL);
        }
    }
}

static void
gimp_move_tool_oper_update (GimpTool         *tool,
                            const GimpCoords *coords,
                            GdkModifierType   state,
                            gboolean          proximity,
                            GimpDisplay      *display)
{
  GimpMoveTool     *move    = GIMP_MOVE_TOOL (tool);
  GimpMoveOptions  *options = GIMP_MOVE_TOOL_GET_OPTIONS (tool);
  GimpDisplayShell *shell   = gimp_display_get_shell (display);
  GimpImage        *image   = gimp_display_get_image (display);
  GimpGuide        *guide   = NULL;

  if (options->move_type == GIMP_TRANSFORM_TYPE_LAYER &&
      ! options->move_current                         &&
      gimp_display_shell_get_show_guides (shell)      &&
      proximity)
    {
      gint snap_distance = display->config->snap_distance;

      guide = gimp_image_find_guide (image, coords->x, coords->y,
                                     FUNSCALEX (shell, snap_distance),
                                     FUNSCALEY (shell, snap_distance));
    }

  if (move->guide != guide)
    {
      GimpDrawTool *draw_tool = GIMP_DRAW_TOOL (tool);

      gimp_draw_tool_pause (draw_tool);

      if (gimp_draw_tool_is_active (draw_tool) &&
          draw_tool->display != display)
        gimp_draw_tool_stop (draw_tool);

      move->guide = guide;

      if (! gimp_draw_tool_is_active (draw_tool))
        gimp_draw_tool_start (draw_tool, display);

      gimp_draw_tool_resume (draw_tool);
    }
}

static void
gimp_move_tool_cursor_update (GimpTool         *tool,
                              const GimpCoords *coords,
                              GdkModifierType   state,
                              GimpDisplay      *display)
{
  GimpMoveOptions    *options     = GIMP_MOVE_TOOL_GET_OPTIONS (tool);
  GimpDisplayShell   *shell       = gimp_display_get_shell (display);
  GimpImage          *image       = gimp_display_get_image (display);
  GimpCursorType      cursor      = GIMP_CURSOR_MOUSE;
  GimpToolCursorType  tool_cursor = GIMP_TOOL_CURSOR_MOVE;
  GimpCursorModifier  modifier    = GIMP_CURSOR_MODIFIER_NONE;

  if (options->move_type == GIMP_TRANSFORM_TYPE_PATH)
    {
      tool_cursor = GIMP_TOOL_CURSOR_PATHS;
      modifier    = GIMP_CURSOR_MODIFIER_MOVE;

      if (options->move_current)
        {
          GimpItem *item = GIMP_ITEM (gimp_image_get_active_vectors (image));

          if (! item || gimp_item_is_position_locked (item))
            modifier = GIMP_CURSOR_MODIFIER_BAD;
        }
      else
        {
          if (gimp_draw_tool_on_vectors (GIMP_DRAW_TOOL (tool), display,
                                         coords, 7, 7,
                                         NULL, NULL, NULL, NULL, NULL, NULL))
            {
              tool_cursor = GIMP_TOOL_CURSOR_HAND;
            }
          else
            {
              modifier = GIMP_CURSOR_MODIFIER_BAD;
            }
        }
    }
  else if (options->move_type == GIMP_TRANSFORM_TYPE_SELECTION)
    {
      tool_cursor = GIMP_TOOL_CURSOR_RECT_SELECT;
      modifier    = GIMP_CURSOR_MODIFIER_MOVE;

      if (gimp_channel_is_empty (gimp_image_get_mask (image)))
        modifier = GIMP_CURSOR_MODIFIER_BAD;
    }
  else if (options->move_current)
    {
      GimpItem *item = GIMP_ITEM (gimp_image_get_active_drawable (image));

      if (! item || gimp_item_is_position_locked (item))
        modifier = GIMP_CURSOR_MODIFIER_BAD;
    }
  else
    {
      GimpLayer  *layer;
      const gint  snap_distance = display->config->snap_distance;

      if (gimp_display_shell_get_show_guides (shell) &&
          gimp_image_find_guide (image, coords->x, coords->y,
                                 FUNSCALEX (shell, snap_distance),
                                 FUNSCALEY (shell, snap_distance)))
        {
          tool_cursor = GIMP_TOOL_CURSOR_HAND;
          modifier    = GIMP_CURSOR_MODIFIER_MOVE;
        }
      else if ((layer = gimp_image_pick_layer (image,
                                               coords->x, coords->y)))
        {
          /*  if there is a floating selection, and this aint it...  */
          if (gimp_image_get_floating_selection (image) &&
              ! gimp_layer_is_floating_sel (layer))
            {
              tool_cursor = GIMP_TOOL_CURSOR_MOVE;
              modifier    = GIMP_CURSOR_MODIFIER_ANCHOR;
            }
          else if (gimp_item_is_position_locked (GIMP_ITEM (layer)))
            {
              modifier = GIMP_CURSOR_MODIFIER_BAD;
            }
          else if (layer != gimp_image_get_active_layer (image))
            {
              tool_cursor = GIMP_TOOL_CURSOR_HAND;
              modifier    = GIMP_CURSOR_MODIFIER_MOVE;
            }
        }
      else
        {
          modifier = GIMP_CURSOR_MODIFIER_BAD;
        }
    }

  gimp_tool_control_set_cursor          (tool->control, cursor);
  gimp_tool_control_set_tool_cursor     (tool->control, tool_cursor);
  gimp_tool_control_set_cursor_modifier (tool->control, modifier);

  GIMP_TOOL_CLASS (parent_class)->cursor_update (tool, coords, state, display);
}

static void
gimp_move_tool_draw (GimpDrawTool *draw_tool)
{
  GimpMoveTool *move = GIMP_MOVE_TOOL (draw_tool);

  if (move->guide)
    {
      GimpCanvasItem *item;
      GimpGuideStyle  style;

      style = gimp_guide_get_style (move->guide);

      item = gimp_draw_tool_add_guide (draw_tool,
                                       gimp_guide_get_orientation (move->guide),
                                       gimp_guide_get_position (move->guide),
                                       style);
      gimp_canvas_item_set_highlight (item, TRUE);
    }
}