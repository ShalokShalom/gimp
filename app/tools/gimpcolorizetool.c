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

#include "libgimpconfig/gimpconfig.h"
#include "libgimpwidgets/gimpwidgets.h"

#include "tools-types.h"

#include "core/gimpdrawable.h"
#include "core/gimperror.h"
#include "core/gimpimage.h"

#include "widgets/gimpcolorpanel.h"
#include "widgets/gimphelp-ids.h"
#include "widgets/gimppropwidgets.h"
#include "widgets/gimpspinscale.h"

#include "display/gimpdisplay.h"

#include "gimpcolorizetool.h"
#include "gimpfilteroptions.h"

#include "gimp-intl.h"


/*  local function prototypes  */

static gboolean   gimp_colorize_tool_initialize    (GimpTool        *tool,
                                                    GimpDisplay     *display,
                                                    GError         **error);

static gchar    * gimp_colorize_tool_get_operation (GimpFilterTool  *filter_tool,
                                                    gchar          **title,
                                                    gchar          **description,
                                                    gchar          **undo_desc,
                                                    gchar          **icon_name,
                                                    gchar          **help_id);
static void       gimp_colorize_tool_dialog        (GimpFilterTool  *filter_tool);
static void       gimp_colorize_tool_color_picked  (GimpFilterTool  *filter_tool,
                                                    gpointer         identifier,
                                                    gdouble          x,
                                                    gdouble          y,
                                                    const Babl      *sample_format,
                                                    const GimpRGB   *color);


G_DEFINE_TYPE (GimpColorizeTool, gimp_colorize_tool, GIMP_TYPE_FILTER_TOOL)

#define parent_class gimp_colorize_tool_parent_class


void
gimp_colorize_tool_register (GimpToolRegisterCallback  callback,
                             gpointer                  data)
{
  (* callback) (GIMP_TYPE_COLORIZE_TOOL,
                GIMP_TYPE_FILTER_OPTIONS,
                gimp_color_options_gui,
                0,
                "gimp-colorize-tool",
                _("Colorize"),
                _("Colorize Tool: Colorize the image"),
                N_("Colori_ze..."), NULL,
                NULL, GIMP_HELP_TOOL_COLORIZE,
                GIMP_STOCK_TOOL_COLORIZE,
                data);
}

static void
gimp_colorize_tool_class_init (GimpColorizeToolClass *klass)
{
  GimpToolClass         *tool_class        = GIMP_TOOL_CLASS (klass);
  GimpFilterToolClass   *filter_tool_class = GIMP_FILTER_TOOL_CLASS (klass);

  tool_class->initialize                 = gimp_colorize_tool_initialize;

  filter_tool_class->settings_name       = "colorize";
  filter_tool_class->import_dialog_title = _("Import Colorize Settings");
  filter_tool_class->export_dialog_title = _("Export Colorize Settings");

  filter_tool_class->get_operation       = gimp_colorize_tool_get_operation;
  filter_tool_class->dialog              = gimp_colorize_tool_dialog;
  filter_tool_class->color_picked        = gimp_colorize_tool_color_picked;
}

static void
gimp_colorize_tool_init (GimpColorizeTool *col_tool)
{
}

static gboolean
gimp_colorize_tool_initialize (GimpTool     *tool,
                               GimpDisplay  *display,
                               GError      **error)
{
  GimpImage    *image    = gimp_display_get_image (display);
  GimpDrawable *drawable = gimp_image_get_active_drawable (image);

  if (! drawable)
    return FALSE;

  if (gimp_drawable_is_gray (drawable))
    {
      g_set_error_literal (error, GIMP_ERROR, GIMP_FAILED,
                           _("Colorize does not operate on grayscale layers."));
      return FALSE;
    }

  return GIMP_TOOL_CLASS (parent_class)->initialize (tool, display, error);
}

static gchar *
gimp_colorize_tool_get_operation (GimpFilterTool  *filter_tool,
                                  gchar          **title,
                                  gchar          **description,
                                  gchar          **undo_desc,
                                  gchar          **icon_name,
                                  gchar          **help_id)
{
  *description = g_strdup (_("Colorize the Image"));

  return g_strdup ("gimp:colorize");
}


/***************************/
/*  Hue-Saturation dialog  */
/***************************/

static void
gimp_colorize_tool_dialog (GimpFilterTool *filter_tool)
{
  GimpColorizeTool *col_tool = GIMP_COLORIZE_TOOL (filter_tool);
  GtkWidget        *main_vbox;
  GtkWidget        *frame;
  GtkWidget        *vbox;
  GtkWidget        *scale;
  GtkWidget        *hbox;
  GtkWidget        *button;

  main_vbox = gimp_filter_tool_dialog_get_vbox (filter_tool);

  frame = gimp_frame_new (_("Select Color"));
  gtk_box_pack_start (GTK_BOX (main_vbox), frame, FALSE, FALSE, 0);
  gtk_widget_show (frame);

  vbox = gtk_box_new (GTK_ORIENTATION_VERTICAL, 4);
  gtk_container_add (GTK_CONTAINER (frame), vbox);
  gtk_widget_show (vbox);

  /*  Create the hue scale widget  */
  scale = gimp_prop_spin_scale_new (filter_tool->config, "hue",
                                    _("_Hue"), 1.0 / 360.0, 15.0 / 360.0, 0);
  gimp_prop_widget_set_factor (scale, 360.0, 0.0, 0.0, 1);
  gtk_box_pack_start (GTK_BOX (vbox), scale, FALSE, FALSE, 0);
  gtk_widget_show (scale);

  /*  Create the saturation scale widget  */
  scale = gimp_prop_spin_scale_new (filter_tool->config, "saturation",
                                    _("_Saturation"), 0.01, 0.1, 0);
  gimp_prop_widget_set_factor (scale, 100.0, 0.0, 0.0, 1);
  gtk_box_pack_start (GTK_BOX (vbox), scale, FALSE, FALSE, 0);
  gtk_widget_show (scale);

  /*  Create the lightness scale widget  */
  scale = gimp_prop_spin_scale_new (filter_tool->config, "lightness",
                                    _("_Lightness"), 0.01, 0.1, 0);
  gimp_prop_widget_set_factor (scale, 100.0, 0.0, 0.0, 1);
  gtk_box_pack_start (GTK_BOX (vbox), scale, FALSE, FALSE, 0);
  gtk_widget_show (scale);

  /*  Create the color button  */
  hbox = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 4);
  gtk_box_pack_start (GTK_BOX (vbox), hbox, FALSE, FALSE, 0);
  gtk_widget_show (hbox);

  button = gimp_prop_color_button_new (filter_tool->config, "color",
                                       _("Colorize Color"),
                                       128, 24,
                                       GIMP_COLOR_AREA_FLAT);
  gimp_color_button_set_update (GIMP_COLOR_BUTTON (button), TRUE);
  gimp_color_panel_set_context (GIMP_COLOR_PANEL (button),
                                GIMP_CONTEXT (GIMP_TOOL_GET_OPTIONS (col_tool)));
  gtk_box_pack_start (GTK_BOX (hbox), button, TRUE, TRUE, 0);
  gtk_widget_show (button);

  button = gimp_filter_tool_add_color_picker (filter_tool,
                                              "colorize",
                                              GIMP_STOCK_COLOR_PICKER_GRAY,
                                              _("Pick color from image"));
  gtk_box_pack_start (GTK_BOX (hbox), button, FALSE, FALSE, 0);
  gtk_widget_show (button);
}

static void
gimp_colorize_tool_color_picked (GimpFilterTool *filter_tool,
                                 gpointer        identifier,
                                 gdouble         x,
                                 gdouble         y,
                                 const Babl     *sample_format,
                                 const GimpRGB  *color)
{
  g_object_set (filter_tool->config, "color", color, NULL);
}
