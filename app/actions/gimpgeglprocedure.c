/* GIMP - The GNU Image Manipulation Program
 * Copyright (C) 1995 Spencer Kimball and Peter Mattis
 *
 * gimpgeglprocedure.c
 * Copyright (C) 2016 Michael Natterer <mitch@gimp.org>
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

#include "libgimpbase/gimpbase.h"
#include "libgimpconfig/gimpconfig.h"

#include "actions-types.h"

#include "core/gimp.h"
#include "core/gimp-memsize.h"
#include "core/gimpcontainer.h"
#include "core/gimpcontext.h"
#include "core/gimpdrawable-operation.h"
#include "core/gimpimage.h"
#include "core/gimplayermask.h"
#include "core/gimpparamspecs.h"
#include "core/gimpsettings.h"
#include "core/gimptoolinfo.h"

#include "gegl/gimp-gegl-config.h"

#include "display/gimpdisplay.h"

#include "tools/gimpoperationtool.h"
#include "tools/tool_manager.h"

#include "gimpgeglprocedure.h"

#include "gimp-intl.h"


static void     gimp_gegl_procedure_finalize            (GObject        *object);

static gint64   gimp_gegl_procedure_get_memsize         (GimpObject     *object,
                                                         gint64         *gui_size);

static gchar  * gimp_gegl_procedure_get_description     (GimpViewable   *viewable,
                                                         gchar         **tooltip);

static const gchar * gimp_gegl_procedure_get_label      (GimpProcedure  *procedure);
static const gchar * gimp_gegl_procedure_get_menu_label (GimpProcedure  *procedure);
static const gchar * gimp_gegl_procedure_get_help_id    (GimpProcedure  *procedure);
static gboolean      gimp_gegl_procedure_get_sensitive  (GimpProcedure  *procedure,
                                                         GimpObject     *object);
static GimpValueArray * gimp_gegl_procedure_execute     (GimpProcedure  *procedure,
                                                         Gimp           *gimp,
                                                         GimpContext    *context,
                                                         GimpProgress   *progress,
                                                         GimpValueArray *args,
                                                         GError        **error);
static void     gimp_gegl_procedure_execute_async       (GimpProcedure  *procedure,
                                                         Gimp           *gimp,
                                                         GimpContext    *context,
                                                         GimpProgress   *progress,
                                                         GimpValueArray *args,
                                                         GimpObject     *display);


G_DEFINE_TYPE (GimpGeglProcedure, gimp_gegl_procedure,
               GIMP_TYPE_PROCEDURE)

#define parent_class gimp_gegl_procedure_parent_class


static void
gimp_gegl_procedure_class_init (GimpGeglProcedureClass *klass)
{
  GObjectClass       *object_class      = G_OBJECT_CLASS (klass);
  GimpObjectClass    *gimp_object_class = GIMP_OBJECT_CLASS (klass);
  GimpViewableClass  *viewable_class    = GIMP_VIEWABLE_CLASS (klass);
  GimpProcedureClass *proc_class        = GIMP_PROCEDURE_CLASS (klass);

  object_class->finalize            = gimp_gegl_procedure_finalize;

  gimp_object_class->get_memsize    = gimp_gegl_procedure_get_memsize;

  viewable_class->default_icon_name = "gimp-gegl";
  viewable_class->get_description   = gimp_gegl_procedure_get_description;

  proc_class->get_label             = gimp_gegl_procedure_get_label;
  proc_class->get_menu_label        = gimp_gegl_procedure_get_menu_label;
  proc_class->get_help_id           = gimp_gegl_procedure_get_help_id;
  proc_class->get_sensitive         = gimp_gegl_procedure_get_sensitive;
  proc_class->execute               = gimp_gegl_procedure_execute;
  proc_class->execute_async         = gimp_gegl_procedure_execute_async;
}

static void
gimp_gegl_procedure_init (GimpGeglProcedure *proc)
{
}

static void
gimp_gegl_procedure_finalize (GObject *object)
{
  GimpGeglProcedure *proc = GIMP_GEGL_PROCEDURE (object);

  g_free (proc->menu_label);
  g_free (proc->label);
  g_free (proc->help_id);

  G_OBJECT_CLASS (parent_class)->finalize (object);
}

static gint64
gimp_gegl_procedure_get_memsize (GimpObject *object,
                                    gint64     *gui_size)
{
  GimpGeglProcedure *proc    = GIMP_GEGL_PROCEDURE (object);
  gint64             memsize = 0;

  memsize += gimp_string_get_memsize (proc->menu_label);
  memsize += gimp_string_get_memsize (proc->label);

  return memsize + GIMP_OBJECT_CLASS (parent_class)->get_memsize (object,
                                                                  gui_size);
}

static gchar *
gimp_gegl_procedure_get_description (GimpViewable  *viewable,
                                        gchar        **tooltip)
{
  GimpProcedure *procedure = GIMP_PROCEDURE (viewable);

  if (tooltip)
    *tooltip = g_strdup (gimp_procedure_get_blurb (procedure));

  return g_strdup (gimp_procedure_get_label (procedure));
}

static const gchar *
gimp_gegl_procedure_get_label (GimpProcedure *procedure)
{
  GimpGeglProcedure *proc = GIMP_GEGL_PROCEDURE (procedure);
  gchar             *ellipsis;
  gchar             *label;

  if (proc->label)
    return proc->label;

  label = gimp_strip_uline (gimp_procedure_get_menu_label (procedure));

  ellipsis = strstr (label, "...");

  if (! ellipsis)
    ellipsis = strstr (label, "\342\200\246" /* U+2026 HORIZONTAL ELLIPSIS */);

  if (ellipsis && ellipsis == (label + strlen (label) - 3))
    *ellipsis = '\0';

  proc->label = label;

  return proc->label;
}

static const gchar *
gimp_gegl_procedure_get_menu_label (GimpProcedure *procedure)
{
  GimpGeglProcedure *proc = GIMP_GEGL_PROCEDURE (procedure);

  if (proc->menu_label)
    return proc->menu_label;

  return GIMP_PROCEDURE_CLASS (parent_class)->get_menu_label (procedure);
}

static const gchar *
gimp_gegl_procedure_get_help_id (GimpProcedure *procedure)
{
  GimpGeglProcedure *proc = GIMP_GEGL_PROCEDURE (procedure);

  return proc->help_id;
}

static gboolean
gimp_gegl_procedure_get_sensitive (GimpProcedure *procedure,
                                   GimpObject    *object)
{
  GimpDrawable *drawable;
  gboolean      sensitive = FALSE;

  g_return_val_if_fail (object == NULL || GIMP_IS_DRAWABLE (object), FALSE);

  drawable = GIMP_DRAWABLE (object);

  if (drawable)
    {
      GimpItem *item;

      if (GIMP_IS_LAYER_MASK (drawable))
        item = GIMP_ITEM (gimp_layer_mask_get_layer (GIMP_LAYER_MASK (drawable)));
      else
        item = GIMP_ITEM (drawable);

      sensitive = ! gimp_item_is_content_locked (item);

      if (gimp_viewable_get_children (GIMP_VIEWABLE (drawable)))
        sensitive = FALSE;
    }

  return sensitive;
}

static GimpValueArray *
gimp_gegl_procedure_execute (GimpProcedure   *procedure,
                             Gimp            *gimp,
                             GimpContext     *context,
                             GimpProgress    *progress,
                             GimpValueArray  *args,
                             GError         **error)
{
  return GIMP_PROCEDURE_CLASS (parent_class)->execute (procedure, gimp,
                                                       context, progress,
                                                       args, error);
}

static void
gimp_gegl_procedure_execute_async (GimpProcedure  *procedure,
                                   Gimp           *gimp,
                                   GimpContext    *context,
                                   GimpProgress   *progress,
                                   GimpValueArray *args,
                                   GimpObject     *display)
{
  GimpRunMode    run_mode = g_value_get_int (gimp_value_array_index (args, 0));
  GimpObject    *settings;
  GimpContainer *container;
  GimpTool      *active_tool;

  settings = gimp_gegl_config_new (procedure->original_name,
                                   gimp_viewable_get_icon_name (GIMP_VIEWABLE (procedure)),
                                   GIMP_TYPE_SETTINGS);

  container = gimp_gegl_config_get_container (G_TYPE_FROM_INSTANCE (settings));

  g_object_unref (settings);

  /*  the last used settings  */
  settings = gimp_container_get_child_by_index (container, 0);

  /*  only use the settings if they are automatically created "last used"
   *  values, not if they were saved explicitly and have a zero timestamp
   */
  if (settings && GIMP_SETTINGS (settings)->time == 0)
    settings = NULL;

  if (run_mode == GIMP_RUN_WITH_LAST_VALS)
    {
      if (settings)
        {
          GimpImage    *image;
          GimpDrawable *drawable;
          GeglNode     *node;

          node = gegl_node_new_child (NULL,
                                      "operation", procedure->original_name,
                                      NULL);
          gimp_gegl_config_sync_node (settings, node);

          image = gimp_value_get_image (gimp_value_array_index (args, 1),
                                        gimp);
          drawable = gimp_value_get_drawable (gimp_value_array_index (args, 2),
                                              gimp);

          gimp_drawable_apply_operation (drawable, progress,
                                         gimp_procedure_get_label (procedure),
                                         node);
          g_object_unref (node);

          gimp_image_flush (image);
          return;
        }

      gimp_message (gimp,
                    G_OBJECT (progress), GIMP_MESSAGE_WARNING,
                    _("There are no last settings for '%s', "
                      "showing the filter dialog instead."),
                    gimp_procedure_get_label (procedure));
    }

  active_tool = tool_manager_get_active (gimp);

  /*  do not use the passed context because we need to set the active
   *  tool on the global user context
   */
  context = gimp_get_user_context (gimp);

  if (G_TYPE_FROM_INSTANCE (active_tool) != GIMP_TYPE_OPERATION_TOOL)
    {
      GimpToolInfo *tool_info = gimp_get_tool_info (gimp,
                                                    "gimp-operation-tool");

      if (GIMP_IS_TOOL_INFO (tool_info))
        gimp_context_set_tool (context, tool_info);
    }
  else
    {
      gimp_context_tool_changed (context);
    }

  active_tool = tool_manager_get_active (gimp);

  if (GIMP_IS_OPERATION_TOOL (active_tool))
    {
      /*  Remember the prodecure that created this tool, because we
       *  can't just switch to an operation tool using
       *  gimp_context_set_tool(), we also have to go through the
       *  initialization code below, otherwise we end up with a dummy
       *  tool that does nothing. See bug #776370.
       */
      g_object_set_data_full (G_OBJECT (active_tool), "gimp-gegl-procedure",
                              g_object_ref (procedure),
                              (GDestroyNotify) g_object_unref);

      gimp_operation_tool_set_operation (GIMP_OPERATION_TOOL (active_tool),
                                         procedure->original_name,
                                         gimp_procedure_get_label (procedure),
                                         gimp_procedure_get_label (procedure),
                                         gimp_procedure_get_label (procedure),
                                         gimp_viewable_get_icon_name (GIMP_VIEWABLE (procedure)),
                                         gimp_procedure_get_help_id (procedure));

      tool_manager_initialize_active (gimp, GIMP_DISPLAY (display));

      if (settings)
        {
          GObject *tool_config = GIMP_FILTER_TOOL (active_tool)->config;

          gimp_config_copy (GIMP_CONFIG (settings),
                            GIMP_CONFIG (tool_config), 0);

          /* see comment in gimp_settings_box_setting_selected() */
          g_object_set (tool_config, "time", 0, NULL);
        }
    }
}


/*  public functions  */

GimpProcedure *
gimp_gegl_procedure_new (Gimp        *gimp,
                         const gchar *operation,
                         const gchar *name,
                         const gchar *menu_label,
                         const gchar *tooltip,
                         const gchar *icon_name,
                         const gchar *help_id)
{
  GimpProcedure *procedure;

  g_return_val_if_fail (GIMP_IS_GIMP (gimp), NULL);
  g_return_val_if_fail (operation != NULL, NULL);
  g_return_val_if_fail (name != NULL, NULL);
  g_return_val_if_fail (menu_label != NULL, NULL);

  procedure = g_object_new (GIMP_TYPE_GEGL_PROCEDURE, NULL);

  GIMP_GEGL_PROCEDURE (procedure)->menu_label = g_strdup (menu_label);
  GIMP_GEGL_PROCEDURE (procedure)->help_id    = g_strdup (help_id);

  gimp_object_set_name (GIMP_OBJECT (procedure), name);
  gimp_viewable_set_icon_name (GIMP_VIEWABLE (procedure), icon_name);
  gimp_procedure_set_strings (procedure,
                              operation,
                              tooltip,
                              tooltip,
                              "author", "copyright", "date",
                              NULL);

  gimp_procedure_add_argument (procedure,
                               gimp_param_spec_int32 ("dummy-param",
                                                      "Dummy Param",
                                                      "Dummy parameter",
                                                      G_MININT32, G_MAXINT32, 0,
                                                      GIMP_PARAM_READWRITE));
  gimp_procedure_add_argument (procedure,
                               gimp_param_spec_image_id ("image",
                                                         "Image",
                                                         "Input image",
                                                         gimp, FALSE,
                                                         GIMP_PARAM_READWRITE));
  gimp_procedure_add_argument (procedure,
                               gimp_param_spec_drawable_id ("drawable",
                                                            "Drawable",
                                                            "Input drawable",
                                                            gimp, TRUE,
                                                            GIMP_PARAM_READWRITE));

  return procedure;
}
