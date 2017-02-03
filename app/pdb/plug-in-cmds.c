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

#include <stdlib.h>
#include <string.h>

#include <gegl.h>

#include <gdk-pixbuf/gdk-pixbuf.h>

#include "libgimpbase/gimpbase.h"

#include "libgimpbase/gimpbase.h"

#include "pdb-types.h"

#include "core/gimp.h"
#include "core/gimpparamspecs.h"
#include "plug-in/gimpplugin.h"
#include "plug-in/gimpplugindef.h"
#include "plug-in/gimppluginmanager-menu-branch.h"
#include "plug-in/gimppluginmanager-query.h"
#include "plug-in/gimppluginmanager.h"
#include "plug-in/gimppluginprocedure.h"

#include "gimppdb.h"
#include "gimpprocedure.h"
#include "internal-procs.h"


static GimpValueArray *
plugins_query_invoker (GimpProcedure         *procedure,
                       Gimp                  *gimp,
                       GimpContext           *context,
                       GimpProgress          *progress,
                       const GimpValueArray  *args,
                       GError               **error)
{
  GimpValueArray *return_vals;
  const gchar *search_string;
  gint32 num_plugins = 0;
  gchar **menu_path = NULL;
  gchar **plugin_accelerator = NULL;
  gchar **plugin_location = NULL;
  gchar **plugin_image_type = NULL;
  gint32 *plugin_install_time = NULL;
  gchar **plugin_real_name = NULL;

  search_string = g_value_get_string (gimp_value_array_index (args, 0));

  num_plugins = gimp_plug_in_manager_query (gimp->plug_in_manager,
                                            search_string,
                                            &menu_path,
                                            &plugin_accelerator,
                                            &plugin_location,
                                            &plugin_image_type,
                                            &plugin_real_name,
                                            &plugin_install_time);

  return_vals = gimp_procedure_get_return_values (procedure, TRUE, NULL);

  g_value_set_int (gimp_value_array_index (return_vals, 1), num_plugins);
  gimp_value_take_stringarray (gimp_value_array_index (return_vals, 2), menu_path, num_plugins);
  g_value_set_int (gimp_value_array_index (return_vals, 3), num_plugins);
  gimp_value_take_stringarray (gimp_value_array_index (return_vals, 4), plugin_accelerator, num_plugins);
  g_value_set_int (gimp_value_array_index (return_vals, 5), num_plugins);
  gimp_value_take_stringarray (gimp_value_array_index (return_vals, 6), plugin_location, num_plugins);
  g_value_set_int (gimp_value_array_index (return_vals, 7), num_plugins);
  gimp_value_take_stringarray (gimp_value_array_index (return_vals, 8), plugin_image_type, num_plugins);
  g_value_set_int (gimp_value_array_index (return_vals, 9), num_plugins);
  gimp_value_take_int32array (gimp_value_array_index (return_vals, 10), plugin_install_time, num_plugins);
  g_value_set_int (gimp_value_array_index (return_vals, 11), num_plugins);
  gimp_value_take_stringarray (gimp_value_array_index (return_vals, 12), plugin_real_name, num_plugins);

  return return_vals;
}

static GimpValueArray *
plugin_domain_register_invoker (GimpProcedure         *procedure,
                                Gimp                  *gimp,
                                GimpContext           *context,
                                GimpProgress          *progress,
                                const GimpValueArray  *args,
                                GError               **error)
{
  gboolean success = TRUE;
  const gchar *domain_name;
  const gchar *domain_path;

  domain_name = g_value_get_string (gimp_value_array_index (args, 0));
  domain_path = g_value_get_string (gimp_value_array_index (args, 1));

  if (success)
    {
      GimpPlugIn *plug_in = gimp->plug_in_manager->current_plug_in;

      if (plug_in && plug_in->call_mode == GIMP_PLUG_IN_CALL_QUERY)
        {
          gimp_plug_in_def_set_locale_domain (plug_in->plug_in_def,
                                              domain_name, domain_path);
        }
      else
        {
          success = FALSE;
        }
    }

  return gimp_procedure_get_return_values (procedure, success,
                                           error ? *error : NULL);
}

static GimpValueArray *
plugin_help_register_invoker (GimpProcedure         *procedure,
                              Gimp                  *gimp,
                              GimpContext           *context,
                              GimpProgress          *progress,
                              const GimpValueArray  *args,
                              GError               **error)
{
  gboolean success = TRUE;
  const gchar *domain_name;
  const gchar *domain_uri;

  domain_name = g_value_get_string (gimp_value_array_index (args, 0));
  domain_uri = g_value_get_string (gimp_value_array_index (args, 1));

  if (success)
    {
      GimpPlugIn *plug_in = gimp->plug_in_manager->current_plug_in;

      if (plug_in && plug_in->call_mode == GIMP_PLUG_IN_CALL_QUERY)
        {
          gimp_plug_in_def_set_help_domain (plug_in->plug_in_def,
                                            domain_name, domain_uri);
        }
      else
        {
          success = FALSE;
        }
    }

  return gimp_procedure_get_return_values (procedure, success,
                                           error ? *error : NULL);
}

static GimpValueArray *
plugin_menu_register_invoker (GimpProcedure         *procedure,
                              Gimp                  *gimp,
                              GimpContext           *context,
                              GimpProgress          *progress,
                              const GimpValueArray  *args,
                              GError               **error)
{
  gboolean success = TRUE;
  const gchar *procedure_name;
  const gchar *menu_path;

  procedure_name = g_value_get_string (gimp_value_array_index (args, 0));
  menu_path = g_value_get_string (gimp_value_array_index (args, 1));

  if (success)
    {
      GimpPlugIn *plug_in = gimp->plug_in_manager->current_plug_in;

      if (plug_in)
        {
          gchar *canonical = gimp_canonicalize_identifier (procedure_name);
          success = gimp_plug_in_menu_register (plug_in, canonical, menu_path);
          g_free (canonical);
        }
      else
        {
          success = FALSE;
        }
    }

  return gimp_procedure_get_return_values (procedure, success,
                                           error ? *error : NULL);
}

static GimpValueArray *
plugin_menu_branch_register_invoker (GimpProcedure         *procedure,
                                     Gimp                  *gimp,
                                     GimpContext           *context,
                                     GimpProgress          *progress,
                                     const GimpValueArray  *args,
                                     GError               **error)
{
  gboolean success = TRUE;
  const gchar *menu_path;
  const gchar *menu_name;

  menu_path = g_value_get_string (gimp_value_array_index (args, 0));
  menu_name = g_value_get_string (gimp_value_array_index (args, 1));

  if (success)
    {
      GimpPlugIn *plug_in = gimp->plug_in_manager->current_plug_in;

      if (plug_in)
        {
          gimp_plug_in_manager_add_menu_branch (gimp->plug_in_manager,
                                                plug_in->file, menu_path, menu_name);
        }
      else
        {
          success = FALSE;
        }
    }

  return gimp_procedure_get_return_values (procedure, success,
                                           error ? *error : NULL);
}

static GimpValueArray *
plugin_icon_register_invoker (GimpProcedure         *procedure,
                              Gimp                  *gimp,
                              GimpContext           *context,
                              GimpProgress          *progress,
                              const GimpValueArray  *args,
                              GError               **error)
{
  gboolean success = TRUE;
  const gchar *procedure_name;
  gint32 icon_type;
  gint32 icon_data_length;
  const guint8 *icon_data;

  procedure_name = g_value_get_string (gimp_value_array_index (args, 0));
  icon_type = g_value_get_enum (gimp_value_array_index (args, 1));
  icon_data_length = g_value_get_int (gimp_value_array_index (args, 2));
  icon_data = gimp_value_get_int8array (gimp_value_array_index (args, 3));

  if (success)
    {
      GimpPlugIn *plug_in = gimp->plug_in_manager->current_plug_in;

      if (plug_in && plug_in->call_mode == GIMP_PLUG_IN_CALL_QUERY)
        {
          GimpPlugInProcedure *proc;
          gchar               *canonical;

          canonical = gimp_canonicalize_identifier (procedure_name);

          proc = gimp_plug_in_procedure_find (plug_in->plug_in_def->procedures,
                                              canonical);

          g_free (canonical);

          if (proc)
            gimp_plug_in_procedure_set_icon (proc, icon_type,
                                             icon_data, icon_data_length);
          else
            success = FALSE;
        }
      else
        {
          success = FALSE;
        }
    }

  return gimp_procedure_get_return_values (procedure, success,
                                           error ? *error : NULL);
}

static GimpValueArray *
plugin_set_pdb_error_handler_invoker (GimpProcedure         *procedure,
                                      Gimp                  *gimp,
                                      GimpContext           *context,
                                      GimpProgress          *progress,
                                      const GimpValueArray  *args,
                                      GError               **error)
{
  gboolean success = TRUE;
  gint32 handler;

  handler = g_value_get_enum (gimp_value_array_index (args, 0));

  if (success)
    {
      GimpPlugIn *plug_in = gimp->plug_in_manager->current_plug_in;

      if (plug_in)
        {
          gimp_plug_in_set_error_handler (plug_in, handler);
        }
      else
        {
          success = FALSE;
        }
    }

  return gimp_procedure_get_return_values (procedure, success,
                                           error ? *error : NULL);
}

static GimpValueArray *
plugin_get_pdb_error_handler_invoker (GimpProcedure         *procedure,
                                      Gimp                  *gimp,
                                      GimpContext           *context,
                                      GimpProgress          *progress,
                                      const GimpValueArray  *args,
                                      GError               **error)
{
  gboolean success = TRUE;
  GimpValueArray *return_vals;
  gint32 handler = 0;

  GimpPlugIn *plug_in = gimp->plug_in_manager->current_plug_in;

  if (plug_in)
    {
      handler = gimp_plug_in_get_error_handler (plug_in);
    }
  else
    {
      success = FALSE;
    }

  return_vals = gimp_procedure_get_return_values (procedure, success,
                                                  error ? *error : NULL);

  if (success)
    g_value_set_enum (gimp_value_array_index (return_vals, 1), handler);

  return return_vals;
}

static GimpValueArray *
plugin_enable_precision_invoker (GimpProcedure         *procedure,
                                 Gimp                  *gimp,
                                 GimpContext           *context,
                                 GimpProgress          *progress,
                                 const GimpValueArray  *args,
                                 GError               **error)
{
  gboolean success = TRUE;
  GimpPlugIn *plug_in = gimp->plug_in_manager->current_plug_in;

  if (plug_in)
    {
      gimp_plug_in_enable_precision (plug_in);
    }
  else
    {
      success = FALSE;
    }

  return gimp_procedure_get_return_values (procedure, success,
                                           error ? *error : NULL);
}

static GimpValueArray *
plugin_precision_enabled_invoker (GimpProcedure         *procedure,
                                  Gimp                  *gimp,
                                  GimpContext           *context,
                                  GimpProgress          *progress,
                                  const GimpValueArray  *args,
                                  GError               **error)
{
  gboolean success = TRUE;
  GimpValueArray *return_vals;
  gboolean enabled = FALSE;

  GimpPlugIn *plug_in = gimp->plug_in_manager->current_plug_in;

  if (plug_in)
    {
      enabled = gimp_plug_in_precision_enabled (plug_in);
    }
  else
    {
      success = FALSE;
    }

  return_vals = gimp_procedure_get_return_values (procedure, success,
                                                  error ? *error : NULL);

  if (success)
    g_value_set_boolean (gimp_value_array_index (return_vals, 1), enabled);

  return return_vals;
}

void
register_plug_in_procs (GimpPDB *pdb)
{
  GimpProcedure *procedure;

  /*
   * gimp-plugins-query
   */
  procedure = gimp_procedure_new (plugins_query_invoker);
  gimp_object_set_static_name (GIMP_OBJECT (procedure),
                               "gimp-plugins-query");
  gimp_procedure_set_static_strings (procedure,
                                     "gimp-plugins-query",
                                     "Queries the plugin database for its contents.",
                                     "This procedure queries the contents of the plugin database.",
                                     "Andy Thomas",
                                     "Andy Thomas",
                                     "1998",
                                     NULL);
  gimp_procedure_add_argument (procedure,
                               gimp_param_spec_string ("search-string",
                                                       "search string",
                                                       "If not an empty string then use this as a search pattern",
                                                       FALSE, FALSE, FALSE,
                                                       NULL,
                                                       GIMP_PARAM_READWRITE | GIMP_PARAM_NO_VALIDATE));
  gimp_procedure_add_return_value (procedure,
                                   gimp_param_spec_int32 ("num-plugins",
                                                          "num plugins",
                                                          "The number of plugins",
                                                          0, G_MAXINT32, 0,
                                                          GIMP_PARAM_READWRITE));
  gimp_procedure_add_return_value (procedure,
                                   gimp_param_spec_string_array ("menu-path",
                                                                 "menu path",
                                                                 "The menu path of the plugin",
                                                                 GIMP_PARAM_READWRITE));
  gimp_procedure_add_return_value (procedure,
                                   gimp_param_spec_int32 ("num-plugins",
                                                          "num plugins",
                                                          "The number of plugins",
                                                          0, G_MAXINT32, 0,
                                                          GIMP_PARAM_READWRITE));
  gimp_procedure_add_return_value (procedure,
                                   gimp_param_spec_string_array ("plugin-accelerator",
                                                                 "plugin accelerator",
                                                                 "String representing keyboard accelerator (could be empty string)",
                                                                 GIMP_PARAM_READWRITE));
  gimp_procedure_add_return_value (procedure,
                                   gimp_param_spec_int32 ("num-plugins",
                                                          "num plugins",
                                                          "The number of plugins",
                                                          0, G_MAXINT32, 0,
                                                          GIMP_PARAM_READWRITE));
  gimp_procedure_add_return_value (procedure,
                                   gimp_param_spec_string_array ("plugin-location",
                                                                 "plugin location",
                                                                 "Location of the plugin program",
                                                                 GIMP_PARAM_READWRITE));
  gimp_procedure_add_return_value (procedure,
                                   gimp_param_spec_int32 ("num-plugins",
                                                          "num plugins",
                                                          "The number of plugins",
                                                          0, G_MAXINT32, 0,
                                                          GIMP_PARAM_READWRITE));
  gimp_procedure_add_return_value (procedure,
                                   gimp_param_spec_string_array ("plugin-image-type",
                                                                 "plugin image type",
                                                                 "Type of image that this plugin will work on",
                                                                 GIMP_PARAM_READWRITE));
  gimp_procedure_add_return_value (procedure,
                                   gimp_param_spec_int32 ("num-plugins",
                                                          "num plugins",
                                                          "The number of plugins",
                                                          0, G_MAXINT32, 0,
                                                          GIMP_PARAM_READWRITE));
  gimp_procedure_add_return_value (procedure,
                                   gimp_param_spec_int32_array ("plugin-install-time",
                                                                "plugin install time",
                                                                "Time that the plugin was installed",
                                                                GIMP_PARAM_READWRITE));
  gimp_procedure_add_return_value (procedure,
                                   gimp_param_spec_int32 ("num-plugins",
                                                          "num plugins",
                                                          "The number of plugins",
                                                          0, G_MAXINT32, 0,
                                                          GIMP_PARAM_READWRITE));
  gimp_procedure_add_return_value (procedure,
                                   gimp_param_spec_string_array ("plugin-real-name",
                                                                 "plugin real name",
                                                                 "The internal name of the plugin",
                                                                 GIMP_PARAM_READWRITE));
  gimp_pdb_register_procedure (pdb, procedure);
  g_object_unref (procedure);

  /*
   * gimp-plugin-domain-register
   */
  procedure = gimp_procedure_new (plugin_domain_register_invoker);
  gimp_object_set_static_name (GIMP_OBJECT (procedure),
                               "gimp-plugin-domain-register");
  gimp_procedure_set_static_strings (procedure,
                                     "gimp-plugin-domain-register",
                                     "Registers a textdomain for localisation.",
                                     "This procedure adds a textdomain to the list of domains Gimp searches for strings when translating its menu entries. There is no need to call this function for plug-ins that have their strings included in the 'gimp-std-plugins' domain as that is used by default. If the compiled message catalog is not in the standard location, you may specify an absolute path to another location. This procedure can only be called in the query function of a plug-in and it has to be called before any procedure is installed.",
                                     "Sven Neumann <sven@gimp.org>",
                                     "Sven Neumann",
                                     "2000",
                                     NULL);
  gimp_procedure_add_argument (procedure,
                               gimp_param_spec_string ("domain-name",
                                                       "domain name",
                                                       "The name of the textdomain (must be unique)",
                                                       FALSE, FALSE, FALSE,
                                                       NULL,
                                                       GIMP_PARAM_READWRITE));
  gimp_procedure_add_argument (procedure,
                               gimp_param_spec_string ("domain-path",
                                                       "domain path",
                                                       "The absolute path to the compiled message catalog (may be NULL)",
                                                       FALSE, FALSE, FALSE,
                                                       NULL,
                                                       GIMP_PARAM_READWRITE | GIMP_PARAM_NO_VALIDATE));
  gimp_pdb_register_procedure (pdb, procedure);
  g_object_unref (procedure);

  /*
   * gimp-plugin-help-register
   */
  procedure = gimp_procedure_new (plugin_help_register_invoker);
  gimp_object_set_static_name (GIMP_OBJECT (procedure),
                               "gimp-plugin-help-register");
  gimp_procedure_set_static_strings (procedure,
                                     "gimp-plugin-help-register",
                                     "Register a help path for a plug-in.",
                                     "This procedure registers user documentation for the calling plug-in with the GIMP help system. The domain_uri parameter points to the root directory where the plug-in help is installed. For each supported language there should be a file called 'gimp-help.xml' that maps the help IDs to the actual help files.",
                                     "Michael Natterer <mitch@gimp.org>",
                                     "Michael Natterer",
                                     "2000",
                                     NULL);
  gimp_procedure_add_argument (procedure,
                               gimp_param_spec_string ("domain-name",
                                                       "domain name",
                                                       "The XML namespace of the plug-in's help pages",
                                                       FALSE, FALSE, FALSE,
                                                       NULL,
                                                       GIMP_PARAM_READWRITE));
  gimp_procedure_add_argument (procedure,
                               gimp_param_spec_string ("domain-uri",
                                                       "domain uri",
                                                       "The root URI of the plug-in's help pages",
                                                       FALSE, FALSE, FALSE,
                                                       NULL,
                                                       GIMP_PARAM_READWRITE));
  gimp_pdb_register_procedure (pdb, procedure);
  g_object_unref (procedure);

  /*
   * gimp-plugin-menu-register
   */
  procedure = gimp_procedure_new (plugin_menu_register_invoker);
  gimp_object_set_static_name (GIMP_OBJECT (procedure),
                               "gimp-plugin-menu-register");
  gimp_procedure_set_static_strings (procedure,
                                     "gimp-plugin-menu-register",
                                     "Register an additional menu path for a plug-in procedure.",
                                     "This procedure installs an additional menu entry for the given procedure.",
                                     "Michael Natterer <mitch@gimp.org>",
                                     "Michael Natterer",
                                     "2004",
                                     NULL);
  gimp_procedure_add_argument (procedure,
                               gimp_param_spec_string ("procedure-name",
                                                       "procedure name",
                                                       "The procedure for which to install the menu path",
                                                       FALSE, FALSE, TRUE,
                                                       NULL,
                                                       GIMP_PARAM_READWRITE));
  gimp_procedure_add_argument (procedure,
                               gimp_param_spec_string ("menu-path",
                                                       "menu path",
                                                       "The procedure's additional menu path",
                                                       FALSE, FALSE, FALSE,
                                                       NULL,
                                                       GIMP_PARAM_READWRITE));
  gimp_pdb_register_procedure (pdb, procedure);
  g_object_unref (procedure);

  /*
   * gimp-plugin-menu-branch-register
   */
  procedure = gimp_procedure_new (plugin_menu_branch_register_invoker);
  gimp_object_set_static_name (GIMP_OBJECT (procedure),
                               "gimp-plugin-menu-branch-register");
  gimp_procedure_set_static_strings (procedure,
                                     "gimp-plugin-menu-branch-register",
                                     "Register a sub-menu.",
                                     "This procedure installs a sub-menu which does not belong to any procedure. The menu-name should be the untranslated menu label. GIMP will look up the translation in the textdomain registered for the plug-in.",
                                     "Michael Natterer <mitch@gimp.org>",
                                     "Michael Natterer",
                                     "2005",
                                     NULL);
  gimp_procedure_add_argument (procedure,
                               gimp_param_spec_string ("menu-path",
                                                       "menu path",
                                                       "The sub-menu's menu path",
                                                       FALSE, FALSE, FALSE,
                                                       NULL,
                                                       GIMP_PARAM_READWRITE));
  gimp_procedure_add_argument (procedure,
                               gimp_param_spec_string ("menu-name",
                                                       "menu name",
                                                       "The name of the sub-menu",
                                                       FALSE, FALSE, FALSE,
                                                       NULL,
                                                       GIMP_PARAM_READWRITE));
  gimp_pdb_register_procedure (pdb, procedure);
  g_object_unref (procedure);

  /*
   * gimp-plugin-icon-register
   */
  procedure = gimp_procedure_new (plugin_icon_register_invoker);
  gimp_object_set_static_name (GIMP_OBJECT (procedure),
                               "gimp-plugin-icon-register");
  gimp_procedure_set_static_strings (procedure,
                                     "gimp-plugin-icon-register",
                                     "Register an icon for a plug-in procedure.",
                                     "This procedure installs an icon for the given procedure.",
                                     "Michael Natterer <mitch@gimp.org>",
                                     "Michael Natterer",
                                     "2004",
                                     NULL);
  gimp_procedure_add_argument (procedure,
                               gimp_param_spec_string ("procedure-name",
                                                       "procedure name",
                                                       "The procedure for which to install the icon",
                                                       FALSE, FALSE, TRUE,
                                                       NULL,
                                                       GIMP_PARAM_READWRITE));
  gimp_procedure_add_argument (procedure,
                               g_param_spec_enum ("icon-type",
                                                  "icon type",
                                                  "The type of the icon",
                                                  GIMP_TYPE_ICON_TYPE,
                                                  GIMP_ICON_TYPE_ICON_NAME,
                                                  GIMP_PARAM_READWRITE));
  gimp_procedure_add_argument (procedure,
                               gimp_param_spec_int32 ("icon-data-length",
                                                      "icon data length",
                                                      "The length of 'icon-data'",
                                                      1, G_MAXINT32, 1,
                                                      GIMP_PARAM_READWRITE));
  gimp_procedure_add_argument (procedure,
                               gimp_param_spec_int8_array ("icon-data",
                                                           "icon data",
                                                           "The procedure's icon. The format depends on the 'icon_type' parameter",
                                                           GIMP_PARAM_READWRITE));
  gimp_pdb_register_procedure (pdb, procedure);
  g_object_unref (procedure);

  /*
   * gimp-plugin-set-pdb-error-handler
   */
  procedure = gimp_procedure_new (plugin_set_pdb_error_handler_invoker);
  gimp_object_set_static_name (GIMP_OBJECT (procedure),
                               "gimp-plugin-set-pdb-error-handler");
  gimp_procedure_set_static_strings (procedure,
                                     "gimp-plugin-set-pdb-error-handler",
                                     "Sets an error handler for procedure calls.",
                                     "This procedure changes the way that errors in procedure calls are handled. By default GIMP will raise an error dialog if a procedure call made by a plug-in fails. Using this procedure the plug-in can change this behavior. If the error handler is set to %GIMP_PDB_ERROR_HANDLER_PLUGIN, then the plug-in is responsible for calling 'gimp-get-pdb-error' and handling the error whenever one if its procedure calls fails. It can do this by displaying the error message or by forwarding it in its own return values.",
                                     "Sven Neumann <sven@gimp.org>",
                                     "Sven Neumann",
                                     "2008",
                                     NULL);
  gimp_procedure_add_argument (procedure,
                               g_param_spec_enum ("handler",
                                                  "handler",
                                                  "Who is responsible for handling procedure call errors",
                                                  GIMP_TYPE_PDB_ERROR_HANDLER,
                                                  GIMP_PDB_ERROR_HANDLER_INTERNAL,
                                                  GIMP_PARAM_READWRITE));
  gimp_pdb_register_procedure (pdb, procedure);
  g_object_unref (procedure);

  /*
   * gimp-plugin-get-pdb-error-handler
   */
  procedure = gimp_procedure_new (plugin_get_pdb_error_handler_invoker);
  gimp_object_set_static_name (GIMP_OBJECT (procedure),
                               "gimp-plugin-get-pdb-error-handler");
  gimp_procedure_set_static_strings (procedure,
                                     "gimp-plugin-get-pdb-error-handler",
                                     "Retrieves the active error handler for procedure calls.",
                                     "This procedure retrieves the currently active error handler for procedure calls made by the calling plug-in. See 'gimp-plugin-set-pdb-error-handler' for details.",
                                     "Sven Neumann <sven@gimp.org>",
                                     "Sven Neumann",
                                     "2008",
                                     NULL);
  gimp_procedure_add_return_value (procedure,
                                   g_param_spec_enum ("handler",
                                                      "handler",
                                                      "Who is responsible for handling procedure call errors",
                                                      GIMP_TYPE_PDB_ERROR_HANDLER,
                                                      GIMP_PDB_ERROR_HANDLER_INTERNAL,
                                                      GIMP_PARAM_READWRITE));
  gimp_pdb_register_procedure (pdb, procedure);
  g_object_unref (procedure);

  /*
   * gimp-plugin-enable-precision
   */
  procedure = gimp_procedure_new (plugin_enable_precision_invoker);
  gimp_object_set_static_name (GIMP_OBJECT (procedure),
                               "gimp-plugin-enable-precision");
  gimp_procedure_set_static_strings (procedure,
                                     "gimp-plugin-enable-precision",
                                     "Switches this plug-in to using the real bit depth of drawables.",
                                     "Switches this plug-in to using the real bit depth of drawables. This setting can only be enabled, and not disabled again during the lifetime of the plug-in. Using 'gimp-drawable-get-buffer', 'gimp-drawable-get-shadow-buffer' or 'gimp-drawable-get-format' will automatically call this function.",
                                     "Michael Natterer <mitch@gimp.org>",
                                     "Michael Natterer",
                                     "2012",
                                     NULL);
  gimp_pdb_register_procedure (pdb, procedure);
  g_object_unref (procedure);

  /*
   * gimp-plugin-precision-enabled
   */
  procedure = gimp_procedure_new (plugin_precision_enabled_invoker);
  gimp_object_set_static_name (GIMP_OBJECT (procedure),
                               "gimp-plugin-precision-enabled");
  gimp_procedure_set_static_strings (procedure,
                                     "gimp-plugin-precision-enabled",
                                     "Whether this plug-in is using the real bit depth of drawables.",
                                     "Returns whether this plug-in is using the real bit depth of drawables, which can be more than 8 bits per channel.",
                                     "Michael Natterer <mitch@gimp.org>",
                                     "Michael Natterer",
                                     "2012",
                                     NULL);
  gimp_procedure_add_return_value (procedure,
                                   g_param_spec_boolean ("enabled",
                                                         "enabled",
                                                         "Whether precision is enabled",
                                                         FALSE,
                                                         GIMP_PARAM_READWRITE));
  gimp_pdb_register_procedure (pdb, procedure);
  g_object_unref (procedure);
}