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

#include <string.h>

#include <gegl.h>

#include <gdk-pixbuf/gdk-pixbuf.h>

#include "libgimpbase/gimpbase.h"
#include "libgimpconfig/gimpconfig.h"
#include "libgimpmodule/gimpmodule.h"

#include "libgimpbase/gimpbase.h"

#include "pdb-types.h"

#include "config/gimprc.h"
#include "core/gimp-utils.h"
#include "core/gimp.h"
#include "core/gimpparamspecs.h"
#include "core/gimptemplate.h"

#include "gimppdb.h"
#include "gimpprocedure.h"
#include "internal-procs.h"


static GimpValueArray *
gimprc_query_invoker (GimpProcedure         *procedure,
                      Gimp                  *gimp,
                      GimpContext           *context,
                      GimpProgress          *progress,
                      const GimpValueArray  *args,
                      GError               **error)
{
  gboolean success = TRUE;
  GimpValueArray *return_vals;
  const gchar *token;
  gchar *value = NULL;

  token = g_value_get_string (gimp_value_array_index (args, 0));

  if (success)
    {
      if (strlen (token))
        {
          /*  use edit_config because unknown tokens are set there  */
          value = gimp_rc_query (GIMP_RC (gimp->edit_config), token);

          if (! value)
            success = FALSE;
        }
      else
        success = FALSE;
    }

  return_vals = gimp_procedure_get_return_values (procedure, success,
                                                  error ? *error : NULL);

  if (success)
    g_value_take_string (gimp_value_array_index (return_vals, 1), value);

  return return_vals;
}

static GimpValueArray *
gimprc_set_invoker (GimpProcedure         *procedure,
                    Gimp                  *gimp,
                    GimpContext           *context,
                    GimpProgress          *progress,
                    const GimpValueArray  *args,
                    GError               **error)
{
  gboolean success = TRUE;
  const gchar *token;
  const gchar *value;

  token = g_value_get_string (gimp_value_array_index (args, 0));
  value = g_value_get_string (gimp_value_array_index (args, 1));

  if (success)
    {
      if (strlen (token))
        {
          /*  use edit_config because that's the one that gets saved  */
          gimp_rc_set_unknown_token (GIMP_RC (gimp->edit_config), token, value);
        }
      else
        success = FALSE;
    }

  return gimp_procedure_get_return_values (procedure, success,
                                           error ? *error : NULL);
}

static GimpValueArray *
get_default_comment_invoker (GimpProcedure         *procedure,
                             Gimp                  *gimp,
                             GimpContext           *context,
                             GimpProgress          *progress,
                             const GimpValueArray  *args,
                             GError               **error)
{
  GimpValueArray *return_vals;
  gchar *comment = NULL;

  comment = g_strdup (gimp_template_get_comment (gimp->config->default_image));

  return_vals = gimp_procedure_get_return_values (procedure, TRUE, NULL);
  g_value_take_string (gimp_value_array_index (return_vals, 1), comment);

  return return_vals;
}

static GimpValueArray *
get_default_unit_invoker (GimpProcedure         *procedure,
                          Gimp                  *gimp,
                          GimpContext           *context,
                          GimpProgress          *progress,
                          const GimpValueArray  *args,
                          GError               **error)
{
  GimpValueArray *return_vals;
  GimpUnit unit_id = 0;

  unit_id = gimp_get_default_unit ();

  return_vals = gimp_procedure_get_return_values (procedure, TRUE, NULL);
  g_value_set_int (gimp_value_array_index (return_vals, 1), unit_id);

  return return_vals;
}

static GimpValueArray *
get_monitor_resolution_invoker (GimpProcedure         *procedure,
                                Gimp                  *gimp,
                                GimpContext           *context,
                                GimpProgress          *progress,
                                const GimpValueArray  *args,
                                GError               **error)
{
  GimpValueArray *return_vals;
  gdouble xres = 0.0;
  gdouble yres = 0.0;

  xres = GIMP_DISPLAY_CONFIG (gimp->config)->monitor_xres;
  yres = GIMP_DISPLAY_CONFIG (gimp->config)->monitor_yres;

  return_vals = gimp_procedure_get_return_values (procedure, TRUE, NULL);

  g_value_set_double (gimp_value_array_index (return_vals, 1), xres);
  g_value_set_double (gimp_value_array_index (return_vals, 2), yres);

  return return_vals;
}

static GimpValueArray *
get_theme_dir_invoker (GimpProcedure         *procedure,
                       Gimp                  *gimp,
                       GimpContext           *context,
                       GimpProgress          *progress,
                       const GimpValueArray  *args,
                       GError               **error)
{
  GimpValueArray *return_vals;
  gchar *theme_dir = NULL;

  GFile *file = gimp_get_theme_dir (gimp);

  if (file)
    theme_dir = g_file_get_path (file);

  return_vals = gimp_procedure_get_return_values (procedure, TRUE, NULL);
  g_value_take_string (gimp_value_array_index (return_vals, 1), theme_dir);

  return return_vals;
}

static GimpValueArray *
get_icon_theme_dir_invoker (GimpProcedure         *procedure,
                            Gimp                  *gimp,
                            GimpContext           *context,
                            GimpProgress          *progress,
                            const GimpValueArray  *args,
                            GError               **error)
{
  GimpValueArray *return_vals;
  gchar *icon_theme_dir = NULL;

  GFile *file = gimp_get_icon_theme_dir (gimp);

  if (file)
    icon_theme_dir = g_file_get_path (file);

  return_vals = gimp_procedure_get_return_values (procedure, TRUE, NULL);
  g_value_take_string (gimp_value_array_index (return_vals, 1), icon_theme_dir);

  return return_vals;
}

static GimpValueArray *
get_color_configuration_invoker (GimpProcedure         *procedure,
                                 Gimp                  *gimp,
                                 GimpContext           *context,
                                 GimpProgress          *progress,
                                 const GimpValueArray  *args,
                                 GError               **error)
{
  GimpValueArray *return_vals;
  gchar *config = NULL;

  config = gimp_config_serialize_to_string (GIMP_CONFIG (gimp->config->color_management), NULL);

  return_vals = gimp_procedure_get_return_values (procedure, TRUE, NULL);
  g_value_take_string (gimp_value_array_index (return_vals, 1), config);

  return return_vals;
}

static GimpValueArray *
get_module_load_inhibit_invoker (GimpProcedure         *procedure,
                                 Gimp                  *gimp,
                                 GimpContext           *context,
                                 GimpProgress          *progress,
                                 const GimpValueArray  *args,
                                 GError               **error)
{
  GimpValueArray *return_vals;
  gchar *load_inhibit = NULL;

  load_inhibit = g_strdup (gimp_module_db_get_load_inhibit (gimp->module_db));

  return_vals = gimp_procedure_get_return_values (procedure, TRUE, NULL);
  g_value_take_string (gimp_value_array_index (return_vals, 1), load_inhibit);

  return return_vals;
}

void
register_gimprc_procs (GimpPDB *pdb)
{
  GimpProcedure *procedure;

  /*
   * gimp-gimprc-query
   */
  procedure = gimp_procedure_new (gimprc_query_invoker);
  gimp_object_set_static_name (GIMP_OBJECT (procedure),
                               "gimp-gimprc-query");
  gimp_procedure_set_static_strings (procedure,
                                     "gimp-gimprc-query",
                                     "Queries the gimprc file parser for information on a specified token.",
                                     "This procedure is used to locate additional information contained in the gimprc file considered extraneous to the operation of GIMP. Plug-ins that need configuration information can expect it will be stored in the user gimprc file and can use this procedure to retrieve it. This query procedure will return the value associated with the specified token. This corresponds _only_ to entries with the format: (<token> <value>). The value must be a string. Entries not corresponding to this format will cause warnings to be issued on gimprc parsing and will not be queryable.",
                                     "Spencer Kimball & Peter Mattis",
                                     "Spencer Kimball & Peter Mattis",
                                     "1997",
                                     NULL);
  gimp_procedure_add_argument (procedure,
                               gimp_param_spec_string ("token",
                                                       "token",
                                                       "The token to query for",
                                                       FALSE, FALSE, FALSE,
                                                       NULL,
                                                       GIMP_PARAM_READWRITE));
  gimp_procedure_add_return_value (procedure,
                                   gimp_param_spec_string ("value",
                                                           "value",
                                                           "The value associated with the queried token",
                                                           FALSE, FALSE, FALSE,
                                                           NULL,
                                                           GIMP_PARAM_READWRITE));
  gimp_pdb_register_procedure (pdb, procedure);
  g_object_unref (procedure);

  /*
   * gimp-gimprc-set
   */
  procedure = gimp_procedure_new (gimprc_set_invoker);
  gimp_object_set_static_name (GIMP_OBJECT (procedure),
                               "gimp-gimprc-set");
  gimp_procedure_set_static_strings (procedure,
                                     "gimp-gimprc-set",
                                     "Sets a gimprc token to a value and saves it in the gimprc.",
                                     "This procedure is used to add or change additional information in the gimprc file that is considered extraneous to the operation of GIMP. Plug-ins that need configuration information can use this function to store it, and 'gimp-gimprc-query' to retrieve it. This will accept _only_ string values in UTF-8 encoding.",
                                     "Seth Burgess",
                                     "Seth Burgess",
                                     "1999",
                                     NULL);
  gimp_procedure_add_argument (procedure,
                               gimp_param_spec_string ("token",
                                                       "token",
                                                       "The token to add or modify",
                                                       FALSE, FALSE, FALSE,
                                                       NULL,
                                                       GIMP_PARAM_READWRITE));
  gimp_procedure_add_argument (procedure,
                               gimp_param_spec_string ("value",
                                                       "value",
                                                       "The value to set the token to",
                                                       FALSE, FALSE, FALSE,
                                                       NULL,
                                                       GIMP_PARAM_READWRITE));
  gimp_pdb_register_procedure (pdb, procedure);
  g_object_unref (procedure);

  /*
   * gimp-get-default-comment
   */
  procedure = gimp_procedure_new (get_default_comment_invoker);
  gimp_object_set_static_name (GIMP_OBJECT (procedure),
                               "gimp-get-default-comment");
  gimp_procedure_set_static_strings (procedure,
                                     "gimp-get-default-comment",
                                     "Get the default image comment as specified in the Preferences.",
                                     "Returns a copy of the default image comment.",
                                     "Spencer Kimball & Peter Mattis",
                                     "Spencer Kimball & Peter Mattis",
                                     "1995-1996",
                                     NULL);
  gimp_procedure_add_return_value (procedure,
                                   gimp_param_spec_string ("comment",
                                                           "comment",
                                                           "Default image comment",
                                                           FALSE, FALSE, FALSE,
                                                           NULL,
                                                           GIMP_PARAM_READWRITE));
  gimp_pdb_register_procedure (pdb, procedure);
  g_object_unref (procedure);

  /*
   * gimp-get-default-unit
   */
  procedure = gimp_procedure_new (get_default_unit_invoker);
  gimp_object_set_static_name (GIMP_OBJECT (procedure),
                               "gimp-get-default-unit");
  gimp_procedure_set_static_strings (procedure,
                                     "gimp-get-default-unit",
                                     "Get the default unit (taken from the user's locale).",
                                     "Returns the default unit's integer ID.",
                                     "Spencer Kimball & Peter Mattis",
                                     "Spencer Kimball & Peter Mattis",
                                     "1995-1996",
                                     NULL);
  gimp_procedure_add_return_value (procedure,
                                   gimp_param_spec_unit ("unit-id",
                                                         "unit id",
                                                         "Default unit",
                                                         TRUE,
                                                         FALSE,
                                                         GIMP_UNIT_PIXEL,
                                                         GIMP_PARAM_READWRITE));
  gimp_pdb_register_procedure (pdb, procedure);
  g_object_unref (procedure);

  /*
   * gimp-get-monitor-resolution
   */
  procedure = gimp_procedure_new (get_monitor_resolution_invoker);
  gimp_object_set_static_name (GIMP_OBJECT (procedure),
                               "gimp-get-monitor-resolution");
  gimp_procedure_set_static_strings (procedure,
                                     "gimp-get-monitor-resolution",
                                     "Get the monitor resolution as specified in the Preferences.",
                                     "Returns the resolution of the monitor in pixels/inch. This value is taken from the Preferences (or the windowing system if this is set in the Preferences) and there's no guarantee for the value to be reasonable.",
                                     "Spencer Kimball & Peter Mattis",
                                     "Spencer Kimball & Peter Mattis",
                                     "1995-1996",
                                     NULL);
  gimp_procedure_add_return_value (procedure,
                                   g_param_spec_double ("xres",
                                                        "xres",
                                                        "X resolution",
                                                        -G_MAXDOUBLE, G_MAXDOUBLE, 0,
                                                        GIMP_PARAM_READWRITE));
  gimp_procedure_add_return_value (procedure,
                                   g_param_spec_double ("yres",
                                                        "yres",
                                                        "Y resolution",
                                                        -G_MAXDOUBLE, G_MAXDOUBLE, 0,
                                                        GIMP_PARAM_READWRITE));
  gimp_pdb_register_procedure (pdb, procedure);
  g_object_unref (procedure);

  /*
   * gimp-get-theme-dir
   */
  procedure = gimp_procedure_new (get_theme_dir_invoker);
  gimp_object_set_static_name (GIMP_OBJECT (procedure),
                               "gimp-get-theme-dir");
  gimp_procedure_set_static_strings (procedure,
                                     "gimp-get-theme-dir",
                                     "Get the directory of the current GUI theme.",
                                     "Returns a copy of the current GUI theme dir.",
                                     "Spencer Kimball & Peter Mattis",
                                     "Spencer Kimball & Peter Mattis",
                                     "1995-1996",
                                     NULL);
  gimp_procedure_add_return_value (procedure,
                                   gimp_param_spec_string ("theme-dir",
                                                           "theme dir",
                                                           "The GUI theme dir",
                                                           FALSE, FALSE, FALSE,
                                                           NULL,
                                                           GIMP_PARAM_READWRITE));
  gimp_pdb_register_procedure (pdb, procedure);
  g_object_unref (procedure);

  /*
   * gimp-get-icon-theme-dir
   */
  procedure = gimp_procedure_new (get_icon_theme_dir_invoker);
  gimp_object_set_static_name (GIMP_OBJECT (procedure),
                               "gimp-get-icon-theme-dir");
  gimp_procedure_set_static_strings (procedure,
                                     "gimp-get-icon-theme-dir",
                                     "Get the directory of the current icon theme.",
                                     "Returns a copy of the current icon theme dir.",
                                     "Michael Natterer <mitch@gimp.org>",
                                     "Michael Natterer",
                                     "2015",
                                     NULL);
  gimp_procedure_add_return_value (procedure,
                                   gimp_param_spec_string ("icon-theme-dir",
                                                           "icon theme dir",
                                                           "The icon theme dir",
                                                           FALSE, FALSE, FALSE,
                                                           NULL,
                                                           GIMP_PARAM_READWRITE));
  gimp_pdb_register_procedure (pdb, procedure);
  g_object_unref (procedure);

  /*
   * gimp-get-color-configuration
   */
  procedure = gimp_procedure_new (get_color_configuration_invoker);
  gimp_object_set_static_name (GIMP_OBJECT (procedure),
                               "gimp-get-color-configuration");
  gimp_procedure_set_static_strings (procedure,
                                     "gimp-get-color-configuration",
                                     "Get a serialized version of the color management configuration.",
                                     "Returns a string that can be deserialized into a GimpColorConfig object representing the current color management configuration.",
                                     "Sven Neumann <sven@gimp.org>",
                                     "Sven Neumann",
                                     "2005",
                                     NULL);
  gimp_procedure_add_return_value (procedure,
                                   gimp_param_spec_string ("config",
                                                           "config",
                                                           "Serialized color management configuration",
                                                           FALSE, FALSE, FALSE,
                                                           NULL,
                                                           GIMP_PARAM_READWRITE));
  gimp_pdb_register_procedure (pdb, procedure);
  g_object_unref (procedure);

  /*
   * gimp-get-module-load-inhibit
   */
  procedure = gimp_procedure_new (get_module_load_inhibit_invoker);
  gimp_object_set_static_name (GIMP_OBJECT (procedure),
                               "gimp-get-module-load-inhibit");
  gimp_procedure_set_static_strings (procedure,
                                     "gimp-get-module-load-inhibit",
                                     "Get the list of modules which should not be loaded.",
                                     "Returns a copy of the list of modules which should not be loaded.",
                                     "Spencer Kimball & Peter Mattis",
                                     "Spencer Kimball & Peter Mattis",
                                     "1995-1996",
                                     NULL);
  gimp_procedure_add_return_value (procedure,
                                   gimp_param_spec_string ("load-inhibit",
                                                           "load inhibit",
                                                           "The list of modules",
                                                           FALSE, FALSE, FALSE,
                                                           NULL,
                                                           GIMP_PARAM_READWRITE));
  gimp_pdb_register_procedure (pdb, procedure);
  g_object_unref (procedure);
}
