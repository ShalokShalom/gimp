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

#include <cairo.h>
#include <gegl.h>
#include <gdk-pixbuf/gdk-pixbuf.h>

#include "libgimpcolor/gimpcolor.h"
#include "libgimpconfig/gimpconfig.h"

#include "gimp-gegl-types.h"

#include "core/gimplist.h"
#include "core/gimpparamspecs-duplicate.h"
#include "core/gimpviewable.h"

#include "gimp-gegl-config.h"
#include "gimp-gegl-utils.h"


/*  local function prototypes  */

static void   gimp_gegl_config_config_sync   (GObject          *config,
                                              const GParamSpec *gimp_pspec,
                                              GeglNode         *node);
static void   gimp_gegl_config_config_notify (GObject          *config,
                                              const GParamSpec *gimp_pspec,
                                              GeglNode         *node);
static void   gimp_gegl_config_node_notify   (GeglNode         *node,
                                              const GParamSpec *gegl_pspec,
                                              GObject          *config);


/*  public functions  */

static GHashTable *
gimp_gegl_config_get_type_table (void)
{
  static GHashTable *config_types = NULL;

  if (! config_types)
    config_types = g_hash_table_new_full (g_str_hash,
                                          g_str_equal,
                                          (GDestroyNotify) g_free,
                                          NULL);

  return config_types;
}

static GHashTable *
gimp_gegl_config_get_container_table (void)
{
  static GHashTable *config_containers = NULL;

  if (! config_containers)
    config_containers = g_hash_table_new_full (g_direct_hash,
                                               g_direct_equal,
                                               NULL,
                                               (GDestroyNotify) g_object_unref);

  return config_containers;
}

static GValue *
gimp_gegl_config_value_new (GParamSpec *pspec)
{
  GValue *value = g_slice_new0 (GValue);

  g_value_init (value, pspec->value_type);

  return value;
}

static void
gimp_gegl_config_value_free (GValue *value)
{
  g_value_unset (value);
  g_slice_free (GValue, value);
}

static GHashTable *
gimp_gegl_config_get_properties (GObject *object)
{
  GHashTable *properties = g_object_get_data (object, "properties");

  if (! properties)
    {
      properties = g_hash_table_new_full (g_str_hash,
                                          g_str_equal,
                                          (GDestroyNotify) g_free,
                                          (GDestroyNotify) gimp_gegl_config_value_free);

      g_object_set_data_full (object, "properties", properties,
                              (GDestroyNotify) g_hash_table_unref);
    }

  return properties;
}

static GValue *
gimp_gegl_config_value_get (GObject    *object,
                            GParamSpec *pspec)
{
  GHashTable *properties = gimp_gegl_config_get_properties (object);
  GValue     *value;

  value = g_hash_table_lookup (properties, pspec->name);

  if (! value)
    {
      value = gimp_gegl_config_value_new (pspec);
      g_hash_table_insert (properties, g_strdup (pspec->name), value);
    }

  return value;
}

static void
gimp_gegl_config_set_property (GObject      *object,
                               guint         property_id,
                               const GValue *value,
                               GParamSpec   *pspec)
{
  GValue *val = gimp_gegl_config_value_get (object, pspec);

  g_value_copy (value, val);
}

static void
gimp_gegl_config_get_property (GObject    *object,
                               guint       property_id,
                               GValue     *value,
                               GParamSpec *pspec)
{
  GValue *val = gimp_gegl_config_value_get (object, pspec);

  g_value_copy (val, value);
}

static void
gimp_gegl_config_class_init (GObjectClass *klass,
                             const gchar  *operation)
{
  GParamSpec **pspecs;
  guint        n_pspecs;
  gint         i;

  klass->set_property = gimp_gegl_config_set_property;
  klass->get_property = gimp_gegl_config_get_property;

  pspecs = gegl_operation_list_properties (operation, &n_pspecs);

  for (i = 0; i < n_pspecs; i++)
    {
      GParamSpec *pspec = pspecs[i];

      if ((pspec->flags & G_PARAM_READABLE) &&
          (pspec->flags & G_PARAM_WRITABLE) &&
          strcmp (pspec->name, "input")     &&
          strcmp (pspec->name, "output"))
        {
          GParamSpec *copy = gimp_param_spec_duplicate (pspec);

          if (copy)
            {
              g_object_class_install_property (klass, i + 1, copy);
            }
        }
    }

  g_free (pspecs);
}

static gboolean
gimp_gegl_config_equal (GimpConfig *a,
                        GimpConfig *b)
{
  GList    *diff;
  gboolean  equal = TRUE;

  diff = gimp_config_diff (G_OBJECT (a), G_OBJECT (b),
                           GIMP_CONFIG_PARAM_SERIALIZE);

  if (G_TYPE_FROM_INSTANCE (a) == G_TYPE_FROM_INSTANCE (b))
    {
      GList *list;

      for (list = diff; list; list = g_list_next (list))
        {
          GParamSpec *pspec = list->data;

          if (pspec->owner_type == G_TYPE_FROM_INSTANCE (a))
            {
              equal = FALSE;
              break;
            }
        }
    }
  else if (diff)
    {
      equal = FALSE;
    }

  g_list_free (diff);

  return equal;
}

static void
gimp_gegl_config_config_iface_init (GimpConfigInterface *iface)
{
  iface->equal = gimp_gegl_config_equal;
}


/*  public functions  */

void
gimp_gegl_config_register (const gchar *operation,
                           GType        config_type)
{
  GHashTable *config_types;

  g_return_if_fail (operation != NULL);
  g_return_if_fail (g_type_is_a (config_type, GIMP_TYPE_OBJECT));

  config_types = gimp_gegl_config_get_type_table ();

  g_hash_table_insert (config_types,
                       g_strdup (operation),
                       (gpointer) config_type);
 }

GimpObject *
gimp_gegl_config_new (const gchar *operation,
                      const gchar *icon_name,
                      GType        parent_type)
{
  GHashTable *config_types;
  GType       config_type;

  g_return_val_if_fail (operation != NULL, NULL);
  g_return_val_if_fail (g_type_is_a (parent_type, GIMP_TYPE_OBJECT), NULL);

  config_types = gimp_gegl_config_get_type_table ();

  config_type = (GType) g_hash_table_lookup (config_types, operation);

  if (! config_type)
    {
      GTypeQuery query;

      g_type_query (parent_type, &query);

      {
        GTypeInfo info =
          {
            query.class_size,
            (GBaseInitFunc) NULL,
            (GBaseFinalizeFunc) NULL,
            (GClassInitFunc) gimp_gegl_config_class_init,
            NULL,           /* class_finalize */
            operation,
            query.instance_size,
            0,              /* n_preallocs */
            (GInstanceInitFunc) NULL,
          };

        const GInterfaceInfo config_info =
          {
            (GInterfaceInitFunc) gimp_gegl_config_config_iface_init,
            NULL, /* interface_finalize */
            NULL  /* interface_data     */
          };

        gchar *type_name = g_strdup_printf ("GimpGegl-%s-config",
                                            operation);

        g_strcanon (type_name,
                    G_CSET_DIGITS "-" G_CSET_a_2_z G_CSET_A_2_Z, '-');

        config_type = g_type_register_static (parent_type, type_name,
                                              &info, 0);

        g_free (type_name);

        g_type_add_interface_static (config_type, GIMP_TYPE_CONFIG,
                                     &config_info);

        if (icon_name && g_type_is_a (config_type, GIMP_TYPE_VIEWABLE))
          {
            GimpViewableClass *viewable_class = g_type_class_ref (config_type);

            viewable_class->default_icon_name = g_strdup (icon_name);

            g_type_class_unref (viewable_class);
          }

        gimp_gegl_config_register (operation, config_type);
      }
    }

  return g_object_new (config_type, NULL);
}

GimpContainer *
gimp_gegl_config_get_container (GType config_type)
{
  GHashTable    *config_containers;
  GimpContainer *container;

  g_return_val_if_fail (g_type_is_a (config_type, GIMP_TYPE_OBJECT), NULL);

  config_containers = gimp_gegl_config_get_container_table ();

  container = g_hash_table_lookup (config_containers, (gpointer) config_type);

  if (! container)
    {
      container = gimp_list_new (config_type, TRUE);

      g_hash_table_insert (config_containers,
                           (gpointer) config_type, container);
    }

  return container;
}

void
gimp_gegl_config_sync_node (GimpObject *config,
                            GeglNode   *node)
{
  GParamSpec **pspecs;
  gchar       *operation;
  guint        n_pspecs;
  gint         i;

  g_return_if_fail (GIMP_IS_OBJECT (config));
  g_return_if_fail (GEGL_IS_NODE (node));

  gegl_node_get (node,
                 "operation", &operation,
                 NULL);

  g_return_if_fail (operation != NULL);

  pspecs = gegl_operation_list_properties (operation, &n_pspecs);
  g_free (operation);

  for (i = 0; i < n_pspecs; i++)
    {
      GParamSpec *pspec = pspecs[i];

      /*  if the operation has an object property of the config's
       *  type, set it and done
       */
      if (G_IS_PARAM_SPEC_OBJECT (pspec) &&
          pspec->value_type == G_TYPE_FROM_INSTANCE (config))
        {
          gegl_node_set (node,
                         pspec->name, config,
                         NULL);
          g_free (pspecs);
          return;
        }
    }

  for (i = 0; i < n_pspecs; i++)
    {
      GParamSpec *gegl_pspec = pspecs[i];
      GParamSpec *gimp_pspec = g_object_class_find_property (G_OBJECT_GET_CLASS (config),
                                                             gegl_pspec->name);

      if (gimp_pspec)
        {
          GValue value = G_VALUE_INIT;

          g_value_init (&value, gimp_pspec->value_type);

          g_object_get_property (G_OBJECT (config), gimp_pspec->name,
                                 &value);

          if (GEGL_IS_PARAM_SPEC_COLOR (gegl_pspec))
            {
              GimpRGB    gimp_color;
              GeglColor *gegl_color;

              gimp_value_get_rgb (&value, &gimp_color);
              g_value_unset (&value);

              gegl_color = gimp_gegl_color_new (&gimp_color);

              g_value_init (&value, gegl_pspec->value_type);
              g_value_take_object (&value, gegl_color);
            }

          gegl_node_set_property (node, gegl_pspec->name,
                                  &value);

          g_value_unset (&value);
        }
    }

  g_free (pspecs);
}

void
gimp_gegl_config_connect_node (GimpObject *config,
                               GeglNode   *node)
{
  GParamSpec **pspecs;
  gchar       *operation;
  guint        n_pspecs;
  gint         i;

  g_return_if_fail (GIMP_IS_OBJECT (config));
  g_return_if_fail (GEGL_IS_NODE (node));

  gegl_node_get (node,
                 "operation", &operation,
                 NULL);

  g_return_if_fail (operation != NULL);

  pspecs = gegl_operation_list_properties (operation, &n_pspecs);
  g_free (operation);

  for (i = 0; i < n_pspecs; i++)
    {
      GParamSpec *pspec = pspecs[i];

      /*  if the operation has an object property of the config's
       *  type, connect it to a special callback and done
       */
      if (G_IS_PARAM_SPEC_OBJECT (pspec) &&
          pspec->value_type == G_TYPE_FROM_INSTANCE (config))
        {
          g_signal_connect_object (config, "notify",
                                   G_CALLBACK (gimp_gegl_config_config_sync),
                                   node, 0);
          g_free (pspecs);
          return;
        }
    }

  for (i = 0; i < n_pspecs; i++)
    {
      GParamSpec *gegl_pspec = pspecs[i];
      GParamSpec *gimp_pspec = g_object_class_find_property (G_OBJECT_GET_CLASS (config),
                                                             gegl_pspec->name);

      if (gimp_pspec)
        {
          gchar *notify_name = g_strconcat ("notify::", gimp_pspec->name, NULL);

          g_signal_connect_object (config, notify_name,
                                   G_CALLBACK (gimp_gegl_config_config_notify),
                                   node, 0);

          g_signal_connect_object (node, notify_name,
                                   G_CALLBACK (gimp_gegl_config_node_notify),
                                   config, 0);

          g_free (notify_name);
        }
    }

  g_free (pspecs);
}


/*  private functions  */

static void
gimp_gegl_config_config_sync (GObject          *config,
                              const GParamSpec *gimp_pspec,
                              GeglNode         *node)
{
  gimp_gegl_config_sync_node (GIMP_OBJECT (config), node);
}

static void
gimp_gegl_config_config_notify (GObject          *config,
                                const GParamSpec *gimp_pspec,
                                GeglNode         *node)
{
  GParamSpec *gegl_pspec = gegl_node_find_property (node, gimp_pspec->name);

  if (gegl_pspec)
    {
      GValue value = G_VALUE_INIT;
      gulong handler;

      g_value_init (&value, gimp_pspec->value_type);
      g_object_get_property (config, gimp_pspec->name, &value);

      if (GEGL_IS_PARAM_SPEC_COLOR (gegl_pspec))
        {
          GimpRGB    gimp_color;
          GeglColor *gegl_color;

          gimp_value_get_rgb (&value, &gimp_color);
          g_value_unset (&value);

          gegl_color = gimp_gegl_color_new (&gimp_color);

          g_value_init (&value, gegl_pspec->value_type);
          g_value_take_object (&value, gegl_color);
        }

      handler = g_signal_handler_find (node,
                                       G_SIGNAL_MATCH_DETAIL |
                                       G_SIGNAL_MATCH_FUNC   |
                                       G_SIGNAL_MATCH_DATA,
                                       0,
                                       g_quark_from_string (gegl_pspec->name),
                                       NULL,
                                       gimp_gegl_config_node_notify,
                                       config);

      if (handler)
        g_signal_handler_block (node, handler);

      gegl_node_set_property (node, gegl_pspec->name, &value);
      g_value_unset (&value);

      if (handler)
        g_signal_handler_unblock (node, handler);

    }
}

static void
gimp_gegl_config_node_notify (GeglNode         *node,
                              const GParamSpec *gegl_pspec,
                              GObject          *config)
{
  GParamSpec *gimp_pspec = g_object_class_find_property (G_OBJECT_GET_CLASS (config),
                                                         gegl_pspec->name);

  if (gimp_pspec)
    {
      GValue value = G_VALUE_INIT;
      gulong handler;

      g_value_init (&value, gegl_pspec->value_type);
      gegl_node_get_property (node, gegl_pspec->name, &value);

      if (GEGL_IS_PARAM_SPEC_COLOR (gegl_pspec))
        {
          GeglColor *gegl_color;
          GimpRGB    gimp_color;

          gegl_color = g_value_dup_object (&value);
          g_value_unset (&value);

          if (gegl_color)
            {
              gegl_color_get_rgba (gegl_color,
                                   &gimp_color.r,
                                   &gimp_color.g,
                                   &gimp_color.b,
                                   &gimp_color.a);
              g_object_unref (gegl_color);
            }
          else
            {
              gimp_rgba_set (&gimp_color, 0.0, 0.0, 0.0, 1.0);
            }

          g_value_init (&value, gimp_pspec->value_type);
          gimp_value_set_rgb (&value, &gimp_color);
        }

      handler = g_signal_handler_find (config,
                                       G_SIGNAL_MATCH_DETAIL |
                                       G_SIGNAL_MATCH_FUNC   |
                                       G_SIGNAL_MATCH_DATA,
                                       0,
                                       g_quark_from_string (gimp_pspec->name),
                                       NULL,
                                       gimp_gegl_config_config_notify,
                                       node);

      if (handler)
        g_signal_handler_block (config, handler);

      g_object_set_property (config, gimp_pspec->name, &value);
      g_value_unset (&value);

      if (handler)
        g_signal_handler_unblock (config, handler);
    }
}
