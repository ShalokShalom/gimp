/* GIMP - The GNU Image Manipulation Program
 * Copyright (C) 1995 Spencer Kimball and Peter Mattis
 *
 * gimpoperationreplace.c
 * Copyright (C) 2008 Michael Natterer <mitch@gimp.org>
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

#include <gegl-plugin.h>

#include "../operations-types.h"

#include "gimpoperationreplace.h"


static GimpLayerModeAffectMask gimp_operation_replace_get_affect_mask (GimpOperationLayerMode *layer_mode);


G_DEFINE_TYPE (GimpOperationReplace, gimp_operation_replace,
               GIMP_TYPE_OPERATION_LAYER_MODE)


static void
gimp_operation_replace_class_init (GimpOperationReplaceClass *klass)
{
  GeglOperationClass               *operation_class;
  GeglOperationPointComposer3Class *point_class;
  GimpOperationLayerModeClass      *layer_mode_class;

  operation_class  = GEGL_OPERATION_CLASS (klass);
  point_class      = GEGL_OPERATION_POINT_COMPOSER3_CLASS (klass);
  layer_mode_class = GIMP_OPERATION_LAYER_MODE_CLASS (klass);

  gegl_operation_class_set_keys (operation_class,
                                 "name",        "gimp:replace",
                                 "description", "GIMP replace mode operation",
                                 NULL);

  point_class->process = gimp_operation_replace_process;

  layer_mode_class->get_affect_mask = gimp_operation_replace_get_affect_mask;
}

static void
gimp_operation_replace_init (GimpOperationReplace *self)
{
}

gboolean
gimp_operation_replace_process (GeglOperation       *op,
                                void                *in_p,
                                void                *layer_p,
                                void                *mask_p,
                                void                *out_p,
                                glong                samples,
                                const GeglRectangle *roi,
                                gint                 level)
{
  GimpOperationLayerMode *layer_mode = (gpointer) op;
  gfloat                 *in         = in_p;
  gfloat                 *out        = out_p;
  gfloat                 *layer      = layer_p;
  gfloat                 *mask       = mask_p;
  gfloat                  opacity    = layer_mode->opacity;
  const gboolean          has_mask   = mask != NULL;

  while (samples--)
    {
      gfloat opacity_value = opacity;
      gfloat new_alpha;
      gint   b;

      if (has_mask)
        opacity_value *= *mask;

      new_alpha = (layer[ALPHA] - in[ALPHA]) * opacity_value + in[ALPHA];

      if (new_alpha)
        {
          gfloat ratio = opacity_value * layer[ALPHA] / new_alpha;

          for (b = RED; b < ALPHA; b++)
            out[b] = (layer[b] - in[b]) * ratio + in[b];
        }
      else
        {
          for (b = RED; b < ALPHA; b++)
            out[b] = in[b];
        }

      out[ALPHA] = new_alpha;

      in    += 4;
      layer += 4;
      out   += 4;

      if (has_mask)
        mask++;
    }

  return TRUE;
}

static GimpLayerModeAffectMask
gimp_operation_replace_get_affect_mask (GimpOperationLayerMode *layer_mode)
{
  GimpLayerModeAffectMask affect_mask = GIMP_LAYER_MODE_AFFECT_NONE;

  if (layer_mode->opacity != 0.0)
    affect_mask |= GIMP_LAYER_MODE_AFFECT_DST;

  /* if opacity != 1.0, or we have a mask, thne we also affect SRC, but this is
   * considered the case anyway, so no need for special handling.
   */

  return affect_mask;
}
