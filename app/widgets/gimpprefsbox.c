/* GIMP - The GNU Image Manipulation Program
 * Copyright (C) 1995 Spencer Kimball and Peter Mattis
 *
 * gimpprefsbox.c
 * Copyright (C) 2013-2016 Michael Natterer <mitch@gimp.org>
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
#include <gtk/gtk.h>

#include "libgimpwidgets/gimpwidgets.h"

#include "widgets-types.h"

#include "gimpprefsbox.h"
#include "gimpwidgets-constructors.h"

#include "gimp-intl.h"


enum
{
  COLUMN_TREE_ICON_NAME,
  COLUMN_TREE_ICON_SIZE,
  COLUMN_TREE_LABEL,
  COLUMN_NOTEBOOK_ICON_NAME,
  COLUMN_NOTEBOOK_ICON_SIZE,
  COLUMN_NOTEBOOK_LABEL,
  COLUMN_PAGE_INDEX
};

typedef struct _GimpPrefsBoxPrivate GimpPrefsBoxPrivate;

struct _GimpPrefsBoxPrivate
{
  GtkTreeStore *store;
  GtkWidget    *tree_view;
  GtkWidget    *notebook;
  GtkWidget    *label;
  GtkWidget    *image;

  gint          tree_icon_size;
  gint          notebook_icon_size;

  gint          page_index;
};

#define GET_PRIVATE(item) G_TYPE_INSTANCE_GET_PRIVATE (item, \
                                                       GIMP_TYPE_PREFS_BOX, \
                                                       GimpPrefsBoxPrivate)


static void   gimp_prefs_box_tree_select_callback   (GtkTreeSelection *sel,
                                                     GimpPrefsBox     *box);
static void   gimp_prefs_box_notebook_page_callback (GtkNotebook      *notebook,
                                                     gpointer          page,
                                                     guint             page_num,
                                                     GimpPrefsBox     *box);


G_DEFINE_TYPE (GimpPrefsBox, gimp_prefs_box, GTK_TYPE_BOX)

#define parent_class gimp_prefs_box_parent_class


static void
gimp_prefs_box_class_init (GimpPrefsBoxClass *klass)
{
  g_type_class_add_private (klass, sizeof (GimpPrefsBoxPrivate));
}

static void
gimp_prefs_box_init (GimpPrefsBox *box)
{
  GimpPrefsBoxPrivate *private = GET_PRIVATE (box);
  GtkTreeViewColumn   *column;
  GtkCellRenderer     *cell;
  GtkTreeSelection    *sel;
  GtkWidget           *frame;
  GtkWidget           *hbox;
  GtkWidget           *ebox;
  GtkWidget           *vbox;

  private->tree_icon_size     = GTK_ICON_SIZE_BUTTON;
  private->notebook_icon_size = GTK_ICON_SIZE_DIALOG;

  gtk_orientable_set_orientation (GTK_ORIENTABLE (box),
                                  GTK_ORIENTATION_HORIZONTAL);
  gtk_box_set_spacing (GTK_BOX (box), 12);


  /*  the categories tree  */

  frame = gtk_scrolled_window_new (NULL, NULL);
  gtk_scrolled_window_set_shadow_type (GTK_SCROLLED_WINDOW (frame),
                                       GTK_SHADOW_IN);
  gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (frame),
                                  GTK_POLICY_NEVER, GTK_POLICY_AUTOMATIC);
  gtk_box_pack_start (GTK_BOX (box), frame, FALSE, FALSE, 0);
  gtk_widget_show (frame);

  private->store = gtk_tree_store_new (7,
                                       G_TYPE_STRING,
                                       G_TYPE_INT,
                                       G_TYPE_STRING,
                                       G_TYPE_STRING,
                                       G_TYPE_INT,
                                       G_TYPE_STRING,
                                       G_TYPE_INT);
  private->tree_view =
    gtk_tree_view_new_with_model (GTK_TREE_MODEL (private->store));
  g_object_unref (private->store);

  gtk_tree_view_set_headers_visible (GTK_TREE_VIEW (private->tree_view), FALSE);

  column = gtk_tree_view_column_new ();

  cell = gtk_cell_renderer_pixbuf_new ();
  gtk_tree_view_column_pack_start (column, cell, FALSE);
  gtk_tree_view_column_set_attributes (column, cell,
                                       "icon-name",  COLUMN_TREE_ICON_NAME,
                                       "stock-size", COLUMN_TREE_ICON_SIZE,
                                       NULL);

  cell = gtk_cell_renderer_text_new ();
  gtk_tree_view_column_pack_start (column, cell, TRUE);
  gtk_tree_view_column_set_attributes (column, cell,
                                       "text", COLUMN_TREE_LABEL,
                                       NULL);

  gtk_tree_view_append_column (GTK_TREE_VIEW (private->tree_view), column);

  gtk_container_add (GTK_CONTAINER (frame), private->tree_view);
  gtk_widget_show (private->tree_view);


  /*  the notebook  */

  vbox = gtk_box_new (GTK_ORIENTATION_VERTICAL, 12);
  gtk_box_pack_start (GTK_BOX (box), vbox, TRUE, TRUE, 0);
  gtk_widget_show (vbox);

  ebox = gtk_event_box_new ();
  gtk_widget_set_state (ebox, GTK_STATE_SELECTED);
  gtk_box_pack_start (GTK_BOX (vbox), ebox, FALSE, TRUE, 0);
  gtk_widget_show (ebox);

  hbox = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 6);
  gtk_container_set_border_width (GTK_CONTAINER (hbox), 6);
  gtk_container_add (GTK_CONTAINER (ebox), hbox);
  gtk_widget_show (hbox);

  private->label = gtk_label_new (NULL);
  gtk_label_set_xalign (GTK_LABEL (private->label), 0.0);
  gimp_label_set_attributes (GTK_LABEL (private->label),
                             PANGO_ATTR_SCALE,  PANGO_SCALE_LARGE,
                             PANGO_ATTR_WEIGHT, PANGO_WEIGHT_BOLD,
                             -1);
  gtk_box_pack_start (GTK_BOX (hbox), private->label, FALSE, FALSE, 0);
  gtk_widget_show (private->label);

  private->image = gtk_image_new ();
  gtk_box_pack_end (GTK_BOX (hbox), private->image, FALSE, FALSE, 0);
  gtk_widget_show (private->image);

  /* The main preferences notebook */
  private->notebook = gtk_notebook_new ();
  gtk_notebook_set_show_tabs (GTK_NOTEBOOK (private->notebook), FALSE);
  gtk_notebook_set_show_border (GTK_NOTEBOOK (private->notebook), FALSE);
  gtk_box_pack_start (GTK_BOX (vbox), private->notebook, TRUE, TRUE, 0);
  gtk_widget_show (private->notebook);

  sel = gtk_tree_view_get_selection (GTK_TREE_VIEW (private->tree_view));
  g_signal_connect (sel, "changed",
                    G_CALLBACK (gimp_prefs_box_tree_select_callback),
                    box);
  g_signal_connect (private->notebook, "switch-page",
                    G_CALLBACK (gimp_prefs_box_notebook_page_callback),
                    box);
}

static void
gimp_prefs_box_tree_select_callback (GtkTreeSelection *sel,
                                     GimpPrefsBox     *box)
{
  GimpPrefsBoxPrivate *private = GET_PRIVATE (box);
  GtkTreeModel        *model;
  GtkTreeIter          iter;
  gchar               *notebook_text;
  gchar               *notebook_icon_name;
  gint                 notebook_icon_size;
  gint                 notebook_index;

  if (! gtk_tree_selection_get_selected (sel, &model, &iter))
    return;

  gtk_tree_model_get (model, &iter,
                      COLUMN_NOTEBOOK_ICON_NAME, &notebook_icon_name,
                      COLUMN_NOTEBOOK_ICON_SIZE, &notebook_icon_size,
                      COLUMN_NOTEBOOK_LABEL,     &notebook_text,
                      COLUMN_PAGE_INDEX,         &notebook_index,
                      -1);

  gtk_label_set_text (GTK_LABEL (private->label), notebook_text);
  g_free (notebook_text);

  gtk_image_set_from_icon_name (GTK_IMAGE (private->image),
                                notebook_icon_name,
                                notebook_icon_size);
  g_free (notebook_icon_name);

  g_signal_handlers_block_by_func (private->notebook,
                                   gimp_prefs_box_notebook_page_callback,
                                   sel);

  gtk_notebook_set_current_page (GTK_NOTEBOOK (private->notebook),
                                 notebook_index);

  g_signal_handlers_unblock_by_func (private->notebook,
                                     gimp_prefs_box_notebook_page_callback,
                                     sel);
}

static void
gimp_prefs_box_notebook_page_callback (GtkNotebook  *notebook,
                                       gpointer      page,
                                       guint         page_num,
                                       GimpPrefsBox *box)
{
  GimpPrefsBoxPrivate *private = GET_PRIVATE (box);
  GtkTreeSelection    *sel;
  GtkTreeModel        *model;
  GtkTreeIter          iter;
  gboolean             iter_valid;

  sel   = gtk_tree_view_get_selection (GTK_TREE_VIEW (private->tree_view));
  model = gtk_tree_view_get_model (GTK_TREE_VIEW (private->tree_view));

  for (iter_valid = gtk_tree_model_get_iter_first (model, &iter);
       iter_valid;
       iter_valid = gtk_tree_model_iter_next (model, &iter))
    {
      gint index;

      gtk_tree_model_get (model, &iter,
                          COLUMN_PAGE_INDEX, &index,
                          -1);

      if (index == page_num)
        {
          gtk_tree_selection_select_iter (sel, &iter);
          return;
        }

      if (gtk_tree_model_iter_has_child (model, &iter))
        {
          gint num_children;
          gint i;

          num_children = gtk_tree_model_iter_n_children (model, &iter);

          for (i = 0; i < num_children; i++)
            {
              GtkTreeIter child_iter;

              gtk_tree_model_iter_nth_child (model, &child_iter, &iter, i);
              gtk_tree_model_get (model, &child_iter,
                                  COLUMN_PAGE_INDEX, &index,
                                  -1);

              if (index == page_num)
                {
                  GtkTreePath *path;

                  path = gtk_tree_model_get_path (model, &child_iter);
                  gtk_tree_view_expand_to_path (GTK_TREE_VIEW (private->tree_view),
                                                path);
                  gtk_tree_selection_select_iter (sel, &child_iter);
                  return;
                }
            }
        }
    }
}


/*  public functions  */

GtkWidget *
gimp_prefs_box_new (void)
{
  return g_object_new (GIMP_TYPE_PREFS_BOX, NULL);
}

GtkWidget *
gimp_prefs_box_add_page (GimpPrefsBox      *box,
                         const gchar       *icon_name,
                         const gchar       *notebook_label,
                         const gchar       *tree_label,
                         const gchar       *help_id,
                         GtkTreeIter       *parent,
                         GtkTreeIter       *iter)
{
  GimpPrefsBoxPrivate *private;
  GtkWidget           *page_vbox;
  GtkWidget           *scrolled_win;
  GtkWidget           *viewport;
  GtkWidget           *vbox;

  g_return_val_if_fail (GIMP_IS_PREFS_BOX (box), NULL);

  private = GET_PRIVATE (box);

  page_vbox = gtk_box_new (GTK_ORIENTATION_VERTICAL, 12);
  gtk_notebook_append_page (GTK_NOTEBOOK (private->notebook), page_vbox, NULL);
  gtk_widget_show (page_vbox);

  scrolled_win = gtk_scrolled_window_new (NULL, NULL);
  gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrolled_win),
                                  GTK_POLICY_NEVER, GTK_POLICY_NEVER);
  gtk_container_add (GTK_CONTAINER (page_vbox), scrolled_win);
  gtk_widget_show (scrolled_win);

  gimp_help_set_help_data (scrolled_win, NULL, help_id);

  viewport = gtk_viewport_new (NULL, NULL);
  gtk_viewport_set_shadow_type (GTK_VIEWPORT (viewport), GTK_SHADOW_NONE);
  gtk_container_add (GTK_CONTAINER (scrolled_win), viewport);
  gtk_widget_show (viewport);

  vbox = gtk_box_new (GTK_ORIENTATION_VERTICAL, 12);
  gtk_container_add (GTK_CONTAINER (viewport), vbox);
  gtk_widget_show (vbox);

  gtk_tree_store_append (private->store, iter, parent);
  gtk_tree_store_set (private->store, iter,
                      COLUMN_TREE_ICON_NAME,     icon_name,
                      COLUMN_TREE_ICON_SIZE,     private->tree_icon_size,
                      COLUMN_TREE_LABEL,         tree_label,
                      COLUMN_NOTEBOOK_ICON_NAME, icon_name,
                      COLUMN_NOTEBOOK_ICON_SIZE, private->notebook_icon_size,
                      COLUMN_NOTEBOOK_LABEL ,    notebook_label,
                      COLUMN_PAGE_INDEX,         private->page_index++,
                      -1);

  return vbox;
}

void
gimp_prefs_box_set_page_scrollable (GimpPrefsBox *box,
                                    GtkWidget    *page,
                                    gboolean      scrollable)
{
  GimpPrefsBoxPrivate *private;
  GtkWidget           *scrolled_win;
  GtkWidget           *page_vbox;

  g_return_if_fail (GIMP_IS_PREFS_BOX (box));
  g_return_if_fail (GTK_IS_BOX (page));
  g_return_if_fail (gtk_widget_is_ancestor (page, GTK_WIDGET (box)));

  private = GET_PRIVATE (box);

  scrolled_win = gtk_widget_get_ancestor (page, GTK_TYPE_SCROLLED_WINDOW);
  page_vbox = gtk_widget_get_parent (scrolled_win);

  g_return_if_fail (gtk_widget_get_parent (page_vbox) == private->notebook);

  gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrolled_win),
                                  GTK_POLICY_NEVER,
                                  scrollable ?
                                  GTK_POLICY_AUTOMATIC : GTK_POLICY_NEVER);
}

GtkWidget *
gimp_prefs_box_set_page_resettable (GimpPrefsBox *box,
                                    GtkWidget    *page,
                                    const gchar  *label)
{
  GimpPrefsBoxPrivate *private;
  GtkWidget           *scrolled_win;
  GtkWidget           *page_vbox;
  GtkWidget           *hbox;
  GtkWidget           *button;

  g_return_val_if_fail (GIMP_IS_PREFS_BOX (box), NULL);
  g_return_val_if_fail (GTK_IS_BOX (page), NULL);
  g_return_val_if_fail (gtk_widget_is_ancestor (page, GTK_WIDGET (box)), NULL);

  private = GET_PRIVATE (box);

  scrolled_win = gtk_widget_get_ancestor (page, GTK_TYPE_SCROLLED_WINDOW);
  page_vbox = gtk_widget_get_parent (scrolled_win);

  g_return_val_if_fail (gtk_widget_get_parent (page_vbox) == private->notebook,
                        NULL);

  hbox = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 0);
  gtk_box_pack_start (GTK_BOX (page_vbox), hbox, FALSE, FALSE, 0);
  gtk_box_reorder_child (GTK_BOX (page_vbox), hbox, 0);
  gtk_widget_show (hbox);

  button = gimp_icon_button_new (GIMP_STOCK_RESET, label);
  gtk_box_pack_end (GTK_BOX (hbox), button, FALSE, FALSE, 0);
  gtk_widget_show (button);

  return button;
}

GtkWidget *
gimp_prefs_box_get_tree_view (GimpPrefsBox *box)
{
  g_return_val_if_fail (GIMP_IS_PREFS_BOX (box), NULL);

  return GET_PRIVATE (box)->tree_view;
}

GtkWidget *
gimp_prefs_box_get_notebook (GimpPrefsBox *box)
{
  g_return_val_if_fail (GIMP_IS_PREFS_BOX (box), NULL);

  return GET_PRIVATE (box)->notebook;
}

GtkWidget *
gimp_prefs_box_get_image (GimpPrefsBox *box)
{
  g_return_val_if_fail (GIMP_IS_PREFS_BOX (box), NULL);

  return GET_PRIVATE (box)->image;
}
