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

#include <gegl.h>
#include <gtk/gtk.h>

#include "libgimpwidgets/gimpwidgets.h"

#include "actions-types.h"

#include "core/gimp.h"
#include "core/gimpdrawable-equalize.h"
#include "core/gimpdrawable-levels.h"
#include "core/gimpdrawable-offset.h"
#include "core/gimpdrawable-operation.h"
#include "core/gimpimage.h"
#include "core/gimpimage-undo.h"
#include "core/gimpitem-linked.h"
#include "core/gimpitemundo.h"
#include "core/gimplayermask.h"
#include "core/gimpprogress.h"

#include "dialogs/dialogs.h"
#include "dialogs/offset-dialog.h"

#include "actions.h"
#include "drawable-commands.h"

#include "gimp-intl.h"


/*  local function prototypes  */

static void   drawable_offset_callback (GtkWidget      *dialog,
                                        GimpDrawable   *drawable,
                                        GimpContext    *context,
                                        gboolean        wrap_around,
                                        GimpOffsetType  fill_type,
                                        gint            offset_x,
                                        gint            offset_y);


/*  public functions  */

void
drawable_equalize_cmd_callback (GtkAction *action,
                                gpointer   data)
{
  GimpImage    *image;
  GimpDrawable *drawable;
  return_if_no_drawable (image, drawable, data);

  gimp_drawable_equalize (drawable, TRUE);
  gimp_image_flush (image);
}

void
drawable_invert_cmd_callback (GtkAction *action,
                              gpointer   data)
{
  GimpImage    *image;
  GimpDrawable *drawable;
  GimpDisplay  *display;
  return_if_no_drawable (image, drawable, data);
  return_if_no_display (display, data);

  gimp_drawable_apply_operation_by_name (drawable, GIMP_PROGRESS (display),
                                         _("Invert"), "gegl:invert-gamma",
                                         NULL);
  gimp_image_flush (image);
}

void
drawable_linear_invert_cmd_callback (GtkAction *action,
                                     gpointer   data)
{
  GimpImage    *image;
  GimpDrawable *drawable;
  GimpDisplay  *display;
  return_if_no_drawable (image, drawable, data);
  return_if_no_display (display, data);

  gimp_drawable_apply_operation_by_name (drawable, GIMP_PROGRESS (display),
                                         _("Linear Invert"), "gegl:invert-linear",
                                         NULL);
  gimp_image_flush (image);
}


void
drawable_value_invert_cmd_callback (GtkAction *action,
                                    gpointer   data)
{
  GimpImage    *image;
  GimpDrawable *drawable;
  GimpDisplay  *display;
  return_if_no_drawable (image, drawable, data);
  return_if_no_display (display, data);

  gimp_drawable_apply_operation_by_name (drawable, GIMP_PROGRESS (display),
                                         _("Value Invert"), "gegl:value-invert",
                                         NULL);
  gimp_image_flush (image);
}

void
drawable_levels_stretch_cmd_callback (GtkAction *action,
                                      gpointer   data)
{
  GimpImage    *image;
  GimpDrawable *drawable;
  GimpDisplay  *display;
  GtkWidget    *widget;
  return_if_no_drawable (image, drawable, data);
  return_if_no_display (display, data);
  return_if_no_widget (widget, data);

  if (! gimp_drawable_is_rgb (drawable))
    {
      gimp_message_literal (image->gimp,
                            G_OBJECT (widget), GIMP_MESSAGE_WARNING,
                            _("White Balance operates only on RGB color "
                              "layers."));
      return;
    }

  gimp_drawable_levels_stretch (drawable, GIMP_PROGRESS (display));
  gimp_image_flush (image);
}

void
drawable_dilate_cmd_callback (GtkAction *action,
                              gpointer   data)
{
  GimpImage    *image;
  GimpDrawable *drawable;
  GimpDisplay  *display;
  GeglNode     *node;
  return_if_no_drawable (image, drawable, data);
  return_if_no_display (display, data);

  node = gegl_node_new_child (NULL,
                              "operation",       "gegl:value-propagate",
                              "mode",            0, /* GEGL_VALUE_PROPAGATE_MODE_WHITE */
                              "lower-threshold", 0.0,
                              "upper-threshold", 1.0,
                              "rate",            1.0,
                              "top",             TRUE,
                              "left",            TRUE,
                              "right",           TRUE,
                              "bottom",          TRUE,
                              "value",           TRUE,
                              "alpha",           FALSE,
                              NULL);

  gimp_drawable_apply_operation (drawable, GIMP_PROGRESS (display),
                                 _("Dilate"), node);
  g_object_unref (node);

  gimp_image_flush (image);
}

void
drawable_erode_cmd_callback (GtkAction *action,
                             gpointer   data)
{
  GimpImage    *image;
  GimpDrawable *drawable;
  GimpDisplay  *display;
  GeglNode     *node;
  return_if_no_drawable (image, drawable, data);
  return_if_no_display (display, data);

  node = gegl_node_new_child (NULL,
                              "operation",       "gegl:value-propagate",
                              "mode",            1, /* GEGL_VALUE_PROPAGATE_MODE_BLACK */
                              "lower-threshold", 0.0,
                              "upper-threshold", 1.0,
                              "rate",            1.0,
                              "top",             TRUE,
                              "left",            TRUE,
                              "right",           TRUE,
                              "bottom",          TRUE,
                              "value",           TRUE,
                              "alpha",           FALSE,
                              NULL);

  gimp_drawable_apply_operation (drawable, GIMP_PROGRESS (display),
                                 _("Erode"), node);
  g_object_unref (node);

  gimp_image_flush (image);
}

void
drawable_offset_cmd_callback (GtkAction *action,
                              gpointer   data)
{
  GimpImage    *image;
  GimpDrawable *drawable;
  GtkWidget    *widget;
  GtkWidget    *dialog;
  return_if_no_drawable (image, drawable, data);
  return_if_no_widget (widget, data);

#define OFFSET_DIALOG_KEY "gimp-offset-dialog"

  dialog = dialogs_get_dialog (G_OBJECT (drawable), OFFSET_DIALOG_KEY);

  if (! dialog)
    {
      dialog = offset_dialog_new (drawable, action_data_get_context (data),
                                  widget,
                                  drawable_offset_callback,
                                  NULL);

      dialogs_attach_dialog (G_OBJECT (drawable),
                             OFFSET_DIALOG_KEY, dialog);
    }

  gtk_window_present (GTK_WINDOW (dialog));
}

void
drawable_linked_cmd_callback (GtkAction *action,
                              gpointer   data)
{
  GimpImage    *image;
  GimpDrawable *drawable;
  gboolean      linked;
  return_if_no_drawable (image, drawable, data);

  linked = gtk_toggle_action_get_active (GTK_TOGGLE_ACTION (action));

  if (GIMP_IS_LAYER_MASK (drawable))
    drawable =
      GIMP_DRAWABLE (gimp_layer_mask_get_layer (GIMP_LAYER_MASK (drawable)));

  if (linked != gimp_item_get_linked (GIMP_ITEM (drawable)))
    {
      GimpUndo *undo;
      gboolean  push_undo = TRUE;

      undo = gimp_image_undo_can_compress (image, GIMP_TYPE_ITEM_UNDO,
                                           GIMP_UNDO_ITEM_LINKED);

      if (undo && GIMP_ITEM_UNDO (undo)->item == GIMP_ITEM (drawable))
        push_undo = FALSE;

      gimp_item_set_linked (GIMP_ITEM (drawable), linked, push_undo);
      gimp_image_flush (image);
    }
}

void
drawable_visible_cmd_callback (GtkAction *action,
                               gpointer   data)
{
  GimpImage    *image;
  GimpDrawable *drawable;
  gboolean      visible;
  return_if_no_drawable (image, drawable, data);

  visible = gtk_toggle_action_get_active (GTK_TOGGLE_ACTION (action));

  if (GIMP_IS_LAYER_MASK (drawable))
    drawable =
      GIMP_DRAWABLE (gimp_layer_mask_get_layer (GIMP_LAYER_MASK (drawable)));

  if (visible != gimp_item_get_visible (GIMP_ITEM (drawable)))
    {
      GimpUndo *undo;
      gboolean  push_undo = TRUE;

      undo = gimp_image_undo_can_compress (image, GIMP_TYPE_ITEM_UNDO,
                                           GIMP_UNDO_ITEM_VISIBILITY);

      if (undo && GIMP_ITEM_UNDO (undo)->item == GIMP_ITEM (drawable))
        push_undo = FALSE;

      gimp_item_set_visible (GIMP_ITEM (drawable), visible, push_undo);
      gimp_image_flush (image);
    }
}

void
drawable_lock_content_cmd_callback (GtkAction *action,
                                    gpointer   data)
{
  GimpImage    *image;
  GimpDrawable *drawable;
  gboolean      locked;
  return_if_no_drawable (image, drawable, data);

  locked = gtk_toggle_action_get_active (GTK_TOGGLE_ACTION (action));

  if (GIMP_IS_LAYER_MASK (drawable))
    drawable =
      GIMP_DRAWABLE (gimp_layer_mask_get_layer (GIMP_LAYER_MASK (drawable)));

  if (locked != gimp_item_get_lock_content (GIMP_ITEM (drawable)))
    {
#if 0
      GimpUndo *undo;
#endif
      gboolean  push_undo = TRUE;

#if 0
      undo = gimp_image_undo_can_compress (image, GIMP_TYPE_ITEM_UNDO,
                                           GIMP_UNDO_ITEM_VISIBILITY);

      if (undo && GIMP_ITEM_UNDO (undo)->item == GIMP_ITEM (drawable))
        push_undo = FALSE;
#endif

      gimp_item_set_lock_content (GIMP_ITEM (drawable), locked, push_undo);
      gimp_image_flush (image);
    }
}

void
drawable_lock_position_cmd_callback (GtkAction *action,
                                    gpointer   data)
{
  GimpImage    *image;
  GimpDrawable *drawable;
  gboolean      locked;
  return_if_no_drawable (image, drawable, data);

  locked = gtk_toggle_action_get_active (GTK_TOGGLE_ACTION (action));

  if (GIMP_IS_LAYER_MASK (drawable))
    drawable =
      GIMP_DRAWABLE (gimp_layer_mask_get_layer (GIMP_LAYER_MASK (drawable)));

  if (locked != gimp_item_get_lock_position (GIMP_ITEM (drawable)))
    {
      GimpUndo *undo;
      gboolean  push_undo = TRUE;

      undo = gimp_image_undo_can_compress (image, GIMP_TYPE_ITEM_UNDO,
                                           GIMP_UNDO_ITEM_LOCK_POSITION);

      if (undo && GIMP_ITEM_UNDO (undo)->item == GIMP_ITEM (drawable))
        push_undo = FALSE;

      gimp_item_set_lock_position (GIMP_ITEM (drawable), locked, push_undo);
      gimp_image_flush (image);
    }
}

void
drawable_flip_cmd_callback (GtkAction *action,
                            gint       value,
                            gpointer   data)
{
  GimpImage    *image;
  GimpDrawable *drawable;
  GimpItem     *item;
  GimpContext  *context;
  gint          off_x, off_y;
  gdouble       axis = 0.0;
  return_if_no_drawable (image, drawable, data);
  return_if_no_context (context, data);

  item = GIMP_ITEM (drawable);

  gimp_item_get_offset (item, &off_x, &off_y);

  switch ((GimpOrientationType) value)
    {
    case GIMP_ORIENTATION_HORIZONTAL:
      axis = ((gdouble) off_x + (gdouble) gimp_item_get_width (item) / 2.0);
      break;

    case GIMP_ORIENTATION_VERTICAL:
      axis = ((gdouble) off_y + (gdouble) gimp_item_get_height (item) / 2.0);
      break;

    default:
      break;
    }

  if (gimp_item_get_linked (item))
    {
      gimp_item_linked_flip (item, context,
                             (GimpOrientationType) value, axis, FALSE);
    }
  else
    {
      gimp_item_flip (item, context,
                      (GimpOrientationType) value, axis, FALSE);
    }

  gimp_image_flush (image);
}

void
drawable_rotate_cmd_callback (GtkAction *action,
                              gint       value,
                              gpointer   data)
{
  GimpImage    *image;
  GimpDrawable *drawable;
  GimpContext  *context;
  GimpItem     *item;
  gint          off_x, off_y;
  gdouble       center_x, center_y;
  gboolean      clip_result = FALSE;
  return_if_no_drawable (image, drawable, data);
  return_if_no_context (context, data);

  item = GIMP_ITEM (drawable);

  gimp_item_get_offset (item, &off_x, &off_y);

  center_x = ((gdouble) off_x + (gdouble) gimp_item_get_width  (item) / 2.0);
  center_y = ((gdouble) off_y + (gdouble) gimp_item_get_height (item) / 2.0);

  if (GIMP_IS_CHANNEL (item))
    clip_result = TRUE;

  if (gimp_item_get_linked (item))
    {
      gimp_item_linked_rotate (item, context, (GimpRotationType) value,
                               center_x, center_y, FALSE);
    }
  else
    {
      gimp_item_rotate (item, context, (GimpRotationType) value,
                        center_x, center_y, clip_result);
    }

  gimp_image_flush (image);
}


/*  private functions  */

static void
drawable_offset_callback (GtkWidget      *dialog,
                          GimpDrawable   *drawable,
                          GimpContext    *context,
                          gboolean        wrap_around,
                          GimpOffsetType  fill_type,
                          gint            offset_x,
                          gint            offset_y)
{
  GimpImage *image = gimp_item_get_image (GIMP_ITEM (drawable));

  gimp_drawable_offset (drawable, context,
                        wrap_around, fill_type,
                        offset_x, offset_y);
  gimp_image_flush (image);

  gtk_widget_destroy (dialog);
}
