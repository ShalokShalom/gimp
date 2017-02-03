/* LIBGIMP - The GIMP Library
 * Copyright (C) 1995-2003 Peter Mattis and Spencer Kimball
 *
 * gimpitem_pdb.h
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

#ifndef __GIMP_ITEM_PDB_H__
#define __GIMP_ITEM_PDB_H__

G_BEGIN_DECLS

/* For information look into the C source or the html documentation */


gboolean      gimp_item_is_valid          (gint32              item_ID);
gint32        gimp_item_get_image         (gint32              item_ID);
gboolean      gimp_item_delete            (gint32              item_ID);
gboolean      gimp_item_is_drawable       (gint32              item_ID);
gboolean      gimp_item_is_layer          (gint32              item_ID);
gboolean      gimp_item_is_text_layer     (gint32              item_ID);
gboolean      gimp_item_is_channel        (gint32              item_ID);
gboolean      gimp_item_is_layer_mask     (gint32              item_ID);
gboolean      gimp_item_is_selection      (gint32              item_ID);
gboolean      gimp_item_is_vectors        (gint32              item_ID);
gboolean      gimp_item_is_group          (gint32              item_ID);
gint32        gimp_item_get_parent        (gint32              item_ID);
gint*         gimp_item_get_children      (gint32              item_ID,
                                           gint               *num_children);
gchar*        gimp_item_get_name          (gint32              item_ID);
gboolean      gimp_item_set_name          (gint32              item_ID,
                                           const gchar        *name);
gboolean      gimp_item_get_visible       (gint32              item_ID);
gboolean      gimp_item_set_visible       (gint32              item_ID,
                                           gboolean            visible);
gboolean      gimp_item_get_linked        (gint32              item_ID);
gboolean      gimp_item_set_linked        (gint32              item_ID,
                                           gboolean            linked);
gboolean      gimp_item_get_lock_content  (gint32              item_ID);
gboolean      gimp_item_set_lock_content  (gint32              item_ID,
                                           gboolean            lock_content);
gboolean      gimp_item_get_lock_position (gint32              item_ID);
gboolean      gimp_item_set_lock_position (gint32              item_ID,
                                           gboolean            lock_position);
GimpColorTag  gimp_item_get_color_tag     (gint32              item_ID);
gboolean      gimp_item_set_color_tag     (gint32              item_ID,
                                           GimpColorTag        color_tag);
gint          gimp_item_get_tattoo        (gint32              item_ID);
gboolean      gimp_item_set_tattoo        (gint32              item_ID,
                                           gint                tattoo);
gboolean      gimp_item_attach_parasite   (gint32              item_ID,
                                           const GimpParasite *parasite);
gboolean      gimp_item_detach_parasite   (gint32              item_ID,
                                           const gchar        *name);
GimpParasite* gimp_item_get_parasite      (gint32              item_ID,
                                           const gchar        *name);
gchar**       gimp_item_get_parasite_list (gint32              item_ID,
                                           gint               *num_parasites);


G_END_DECLS

#endif /* __GIMP_ITEM_PDB_H__ */
