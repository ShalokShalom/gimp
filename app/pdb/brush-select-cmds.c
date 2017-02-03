/* GIMP - The GNU Image Manipulation Program
 * Copyright (C) 1995-2003 Spencer Kimball and Peter Mattis
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

/* NOTE: This file is auto-generated by pdbgen.pl. */

#include "config.h"

#include <gegl.h>

#include <gdk-pixbuf/gdk-pixbuf.h>

#include "libgimpbase/gimpbase.h"

#include "pdb-types.h"

#include "core/gimp.h"
#include "core/gimpdatafactory.h"
#include "core/gimpparamspecs.h"

#include "gimppdb.h"
#include "gimpprocedure.h"
#include "internal-procs.h"


static GimpValueArray *
brushes_popup_invoker (GimpProcedure         *procedure,
                       Gimp                  *gimp,
                       GimpContext           *context,
                       GimpProgress          *progress,
                       const GimpValueArray  *args,
                       GError               **error)
{
  gboolean success = TRUE;
  const gchar *brush_callback;
  const gchar *popup_title;
  const gchar *initial_brush;
  gdouble opacity;
  gint32 spacing;
  gint32 paint_mode;

  brush_callback = g_value_get_string (gimp_value_array_index (args, 0));
  popup_title = g_value_get_string (gimp_value_array_index (args, 1));
  initial_brush = g_value_get_string (gimp_value_array_index (args, 2));
  opacity = g_value_get_double (gimp_value_array_index (args, 3));
  spacing = g_value_get_int (gimp_value_array_index (args, 4));
  paint_mode = g_value_get_enum (gimp_value_array_index (args, 5));

  if (success)
    {
      if (paint_mode == GIMP_LAYER_MODE_OVERLAY_LEGACY)
        paint_mode = GIMP_LAYER_MODE_SOFTLIGHT_LEGACY;

      if (gimp->no_interface ||
          ! gimp_pdb_lookup_procedure (gimp->pdb, brush_callback) ||
          ! gimp_pdb_dialog_new (gimp, context, progress,
                                 gimp_data_factory_get_container (gimp->brush_factory),
                                 popup_title, brush_callback, initial_brush,
                                 "opacity",    opacity / 100.0,
                                 "paint-mode", paint_mode,
                                 "spacing",    spacing,
                                 NULL))
        success = FALSE;
    }

  return gimp_procedure_get_return_values (procedure, success,
                                           error ? *error : NULL);
}

static GimpValueArray *
brushes_close_popup_invoker (GimpProcedure         *procedure,
                             Gimp                  *gimp,
                             GimpContext           *context,
                             GimpProgress          *progress,
                             const GimpValueArray  *args,
                             GError               **error)
{
  gboolean success = TRUE;
  const gchar *brush_callback;

  brush_callback = g_value_get_string (gimp_value_array_index (args, 0));

  if (success)
    {
      if (gimp->no_interface ||
          ! gimp_pdb_lookup_procedure (gimp->pdb, brush_callback) ||
          ! gimp_pdb_dialog_close (gimp, gimp_data_factory_get_container (gimp->brush_factory),
                                   brush_callback))
        success = FALSE;
    }

  return gimp_procedure_get_return_values (procedure, success,
                                           error ? *error : NULL);
}

static GimpValueArray *
brushes_set_popup_invoker (GimpProcedure         *procedure,
                           Gimp                  *gimp,
                           GimpContext           *context,
                           GimpProgress          *progress,
                           const GimpValueArray  *args,
                           GError               **error)
{
  gboolean success = TRUE;
  const gchar *brush_callback;
  const gchar *brush_name;
  gdouble opacity;
  gint32 spacing;
  gint32 paint_mode;

  brush_callback = g_value_get_string (gimp_value_array_index (args, 0));
  brush_name = g_value_get_string (gimp_value_array_index (args, 1));
  opacity = g_value_get_double (gimp_value_array_index (args, 2));
  spacing = g_value_get_int (gimp_value_array_index (args, 3));
  paint_mode = g_value_get_enum (gimp_value_array_index (args, 4));

  if (success)
    {
      if (paint_mode == GIMP_LAYER_MODE_OVERLAY_LEGACY)
        paint_mode = GIMP_LAYER_MODE_SOFTLIGHT_LEGACY;

      if (gimp->no_interface ||
          ! gimp_pdb_lookup_procedure (gimp->pdb, brush_callback) ||
          ! gimp_pdb_dialog_set (gimp, gimp_data_factory_get_container (gimp->brush_factory),
                                 brush_callback, brush_name,
                                 "opacity",    opacity / 100.0,
                                 "paint-mode", paint_mode,
                                 "spacing",    spacing,
                                 NULL))
        success = FALSE;
    }

  return gimp_procedure_get_return_values (procedure, success,
                                           error ? *error : NULL);
}

void
register_brush_select_procs (GimpPDB *pdb)
{
  GimpProcedure *procedure;

  /*
   * gimp-brushes-popup
   */
  procedure = gimp_procedure_new (brushes_popup_invoker);
  gimp_object_set_static_name (GIMP_OBJECT (procedure),
                               "gimp-brushes-popup");
  gimp_procedure_set_static_strings (procedure,
                                     "gimp-brushes-popup",
                                     "Invokes the Gimp brush selection.",
                                     "This procedure opens the brush selection dialog.",
                                     "Andy Thomas",
                                     "Andy Thomas",
                                     "1998",
                                     NULL);
  gimp_procedure_add_argument (procedure,
                               gimp_param_spec_string ("brush-callback",
                                                       "brush callback",
                                                       "The callback PDB proc to call when brush selection is made",
                                                       FALSE, FALSE, TRUE,
                                                       NULL,
                                                       GIMP_PARAM_READWRITE));
  gimp_procedure_add_argument (procedure,
                               gimp_param_spec_string ("popup-title",
                                                       "popup title",
                                                       "Title of the brush selection dialog",
                                                       FALSE, FALSE, FALSE,
                                                       NULL,
                                                       GIMP_PARAM_READWRITE));
  gimp_procedure_add_argument (procedure,
                               gimp_param_spec_string ("initial-brush",
                                                       "initial brush",
                                                       "The name of the brush to set as the first selected",
                                                       FALSE, TRUE, FALSE,
                                                       NULL,
                                                       GIMP_PARAM_READWRITE));
  gimp_procedure_add_argument (procedure,
                               g_param_spec_double ("opacity",
                                                    "opacity",
                                                    "The initial opacity of the brush",
                                                    0, 100, 0,
                                                    GIMP_PARAM_READWRITE));
  gimp_procedure_add_argument (procedure,
                               gimp_param_spec_int32 ("spacing",
                                                      "spacing",
                                                      "The initial spacing of the brush (if < 0 then use brush default spacing)",
                                                      G_MININT32, 1000, 0,
                                                      GIMP_PARAM_READWRITE));
  gimp_procedure_add_argument (procedure,
                               g_param_spec_enum ("paint-mode",
                                                  "paint mode",
                                                  "The initial paint mode",
                                                  GIMP_TYPE_LAYER_MODE,
                                                  GIMP_LAYER_MODE_NORMAL,
                                                  GIMP_PARAM_READWRITE));
  gimp_pdb_register_procedure (pdb, procedure);
  g_object_unref (procedure);

  /*
   * gimp-brushes-close-popup
   */
  procedure = gimp_procedure_new (brushes_close_popup_invoker);
  gimp_object_set_static_name (GIMP_OBJECT (procedure),
                               "gimp-brushes-close-popup");
  gimp_procedure_set_static_strings (procedure,
                                     "gimp-brushes-close-popup",
                                     "Close the brush selection dialog.",
                                     "This procedure closes an opened brush selection dialog.",
                                     "Andy Thomas",
                                     "Andy Thomas",
                                     "1998",
                                     NULL);
  gimp_procedure_add_argument (procedure,
                               gimp_param_spec_string ("brush-callback",
                                                       "brush callback",
                                                       "The name of the callback registered for this pop-up",
                                                       FALSE, FALSE, TRUE,
                                                       NULL,
                                                       GIMP_PARAM_READWRITE));
  gimp_pdb_register_procedure (pdb, procedure);
  g_object_unref (procedure);

  /*
   * gimp-brushes-set-popup
   */
  procedure = gimp_procedure_new (brushes_set_popup_invoker);
  gimp_object_set_static_name (GIMP_OBJECT (procedure),
                               "gimp-brushes-set-popup");
  gimp_procedure_set_static_strings (procedure,
                                     "gimp-brushes-set-popup",
                                     "Sets the current brush in a brush selection dialog.",
                                     "Sets the current brush in a brush selection dialog.",
                                     "Andy Thomas",
                                     "Andy Thomas",
                                     "1998",
                                     NULL);
  gimp_procedure_add_argument (procedure,
                               gimp_param_spec_string ("brush-callback",
                                                       "brush callback",
                                                       "The name of the callback registered for this pop-up",
                                                       FALSE, FALSE, TRUE,
                                                       NULL,
                                                       GIMP_PARAM_READWRITE));
  gimp_procedure_add_argument (procedure,
                               gimp_param_spec_string ("brush-name",
                                                       "brush name",
                                                       "The name of the brush to set as selected",
                                                       FALSE, FALSE, FALSE,
                                                       NULL,
                                                       GIMP_PARAM_READWRITE));
  gimp_procedure_add_argument (procedure,
                               g_param_spec_double ("opacity",
                                                    "opacity",
                                                    "The initial opacity of the brush",
                                                    0, 100, 0,
                                                    GIMP_PARAM_READWRITE));
  gimp_procedure_add_argument (procedure,
                               gimp_param_spec_int32 ("spacing",
                                                      "spacing",
                                                      "The initial spacing of the brush (if < 0 then use brush default spacing)",
                                                      G_MININT32, 1000, 0,
                                                      GIMP_PARAM_READWRITE));
  gimp_procedure_add_argument (procedure,
                               g_param_spec_enum ("paint-mode",
                                                  "paint mode",
                                                  "The initial paint mode",
                                                  GIMP_TYPE_LAYER_MODE,
                                                  GIMP_LAYER_MODE_NORMAL,
                                                  GIMP_PARAM_READWRITE));
  gimp_pdb_register_procedure (pdb, procedure);
  g_object_unref (procedure);
}
