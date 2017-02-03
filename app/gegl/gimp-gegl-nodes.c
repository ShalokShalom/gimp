/* GIMP - The GNU Image Manipulation Program
 * Copyright (C) 1995 Spencer Kimball and Peter Mattis
 *
 * gimp-gegl-nodes.h
 * Copyright (C) 2012 Michael Natterer <mitch@gimp.org>
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

#include "gimp-gegl-types.h"

#include "core/gimp-layer-modes.h"

#include "gimp-gegl-nodes.h"
#include "gimp-gegl-utils.h"


GeglNode *
gimp_gegl_create_flatten_node (const GimpRGB *background)
{
  GeglNode  *node;
  GeglNode  *input;
  GeglNode  *output;
  GeglNode  *color;
  GeglNode  *over;
  GeglColor *c;

  g_return_val_if_fail (background != NULL, NULL);

  node = gegl_node_new ();

  input  = gegl_node_get_input_proxy  (node, "input");
  output = gegl_node_get_output_proxy (node, "output");

  c = gimp_gegl_color_new (background);
  color = gegl_node_new_child (node,
                               "operation", "gegl:color",
                               "value",     c,
                               NULL);
  g_object_unref (c);

  over = gegl_node_new_child (node,
                              "operation", "gegl:over",
                              NULL);

  gegl_node_connect_to (input,  "output",
                        over,   "aux");
  gegl_node_connect_to (color,  "output",
                        over,   "input");
  gegl_node_connect_to (over,   "output",
                        output, "input");

  return node;
}

GeglNode *
gimp_gegl_create_apply_opacity_node (GeglBuffer *mask,
                                     gint        mask_offset_x,
                                     gint        mask_offset_y,
                                     gdouble     opacity)
{
  GeglNode  *node;
  GeglNode  *input;
  GeglNode  *output;
  GeglNode  *opacity_node;
  GeglNode  *mask_source;

  g_return_val_if_fail (GEGL_IS_BUFFER (mask), NULL);

  node = gegl_node_new ();

  input  = gegl_node_get_input_proxy  (node, "input");
  output = gegl_node_get_output_proxy (node, "output");

  opacity_node = gegl_node_new_child (node,
                                      "operation", "gegl:opacity",
                                      "value",     opacity,
                                      NULL);

  mask_source = gimp_gegl_add_buffer_source (node, mask,
                                             mask_offset_x,
                                             mask_offset_y);

  gegl_node_connect_to (input,        "output",
                        opacity_node, "input");
  gegl_node_connect_to (mask_source,  "output",
                        opacity_node, "aux");
  gegl_node_connect_to (opacity_node, "output",
                        output,       "input");

  return node;
}

GeglNode *
gimp_gegl_add_buffer_source (GeglNode   *parent,
                             GeglBuffer *buffer,
                             gint        offset_x,
                             gint        offset_y)
{
  GeglNode *buffer_source;

  g_return_val_if_fail (GEGL_IS_NODE (parent), NULL);
  g_return_val_if_fail (GEGL_IS_BUFFER (buffer), NULL);

  buffer_source = gegl_node_new_child (parent,
                                       "operation", "gegl:buffer-source",
                                       "buffer",    buffer,
                                       NULL);

  if (offset_x != 0 || offset_y != 0)
    {
      GeglNode *translate =
        gegl_node_new_child (parent,
                             "operation", "gegl:translate",
                             "x",         (gdouble) offset_x,
                             "y",         (gdouble) offset_y,
                             NULL);

      gegl_node_connect_to (buffer_source, "output",
                            translate,     "input");

      buffer_source = translate;
    }

  return buffer_source;
}

void
gimp_gegl_mode_node_set_mode (GeglNode               *node,
                              GimpLayerMode           mode,
                              GimpLayerCompositeMode  composite)
{
  gdouble opacity;

  g_return_if_fail (GEGL_IS_NODE (node));

  if (composite == GIMP_LAYER_COMPOSITE_AUTO)
    composite = gimp_layer_mode_get_composite_mode (mode);

  gegl_node_get (node,
                 "opacity", &opacity,
                 NULL);

  /* setting the operation creates a new instance, so we have to set
   * all its properties
   */
  gegl_node_set (node,
                 "operation",       gimp_layer_mode_get_operation (mode),
                 "layer-mode",      mode,
                 "composite-mode",  composite,
                 "opacity",         opacity,
                 "linear",          gimp_layer_mode_wants_linear_data (mode),
                 "blend-space",     gimp_layer_mode_get_blend_space (mode),
                 "composite-space", gimp_layer_mode_get_composite_space (mode),
                 NULL);
}

void
gimp_gegl_mode_node_set_opacity (GeglNode *node,
                                 gdouble   opacity)
{
  g_return_if_fail (GEGL_IS_NODE (node));

  gegl_node_set (node,
                 "opacity", opacity,
                 NULL);
}

void
gimp_gegl_node_set_matrix (GeglNode          *node,
                           const GimpMatrix3 *matrix)
{
  gchar *matrix_string;

  g_return_if_fail (GEGL_IS_NODE (node));
  g_return_if_fail (matrix != NULL);

  matrix_string = gegl_matrix3_to_string ((GeglMatrix3 *) matrix);

  gegl_node_set (node,
                 "transform", matrix_string,
                 NULL);

  g_free (matrix_string);
}

void
gimp_gegl_node_set_color (GeglNode      *node,
                          const GimpRGB *color)
{
  GeglColor *gegl_color;

  g_return_if_fail (GEGL_IS_NODE (node));
  g_return_if_fail (color != NULL);

  gegl_color = gimp_gegl_color_new (color);

  gegl_node_set (node,
                 "value", gegl_color,
                 NULL);

  g_object_unref (gegl_color);
}
