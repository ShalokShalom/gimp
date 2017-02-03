/* LIBGIMP - The GIMP Library
 * Copyright (C) 1995-2003 Peter Mattis and Spencer Kimball
 *
 * gimpgradients_pdb.h
 *
 * This library is free software: you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 3 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library.  If not, see
 * <http://www.gnu.org/licenses/>.
 */

/* NOTE: This file is auto-generated by pdbgen.pl */

#if !defined (__GIMP_H_INSIDE__) && !defined (GIMP_COMPILATION)
#error "Only <libgimp/gimp.h> can be included directly."
#endif

#ifndef __GIMP_GRADIENTS_PDB_H__
#define __GIMP_GRADIENTS_PDB_H__

G_BEGIN_DECLS

/* For information look into the C source or the html documentation */


gboolean gimp_gradients_refresh           (void);
gchar**  gimp_gradients_get_list          (const gchar    *filter,
                                           gint           *num_gradients);
GIMP_DEPRECATED_FOR(gimp_gradient_get_uniform_samples)
gdouble* gimp_gradients_sample_uniform    (gint            num_samples,
                                           gboolean        reverse);
GIMP_DEPRECATED_FOR(gimp_gradient_get_custom_samples)
gdouble* gimp_gradients_sample_custom     (gint            num_samples,
                                           const gdouble  *positions,
                                           gboolean        reverse);
GIMP_DEPRECATED_FOR(gimp_gradient_get_uniform_samples)
gchar*   gimp_gradients_get_gradient_data (const gchar    *name,
                                           gint            sample_size,
                                           gboolean        reverse,
                                           gint           *width,
                                           gdouble       **grad_data);


G_END_DECLS

#endif /* __GIMP_GRADIENTS_PDB_H__ */
