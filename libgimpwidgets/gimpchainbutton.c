/* LIBGIMP - The GIMP Library
 * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball
 *
 * gimpchainbutton.c
 * Copyright (C) 1999-2000 Sven Neumann <sven@gimp.org>
 *
 * This library is free software: you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 3 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library.  If not, see
 * <http://www.gnu.org/licenses/>.
 */

#include "config.h"

#include <gtk/gtk.h>

#include "gimpwidgetstypes.h"

#include "gimpchainbutton.h"
#include "gimpicons.h"


/**
 * SECTION: gimpchainbutton
 * @title: GimpChainButton
 * @short_description: Widget to visually connect two entry widgets.
 * @see_also: You may want to use the convenience function
 *            gimp_coordinates_new() to set up two GimpSizeEntries
 *            (see #GimpSizeEntry) linked with a #GimpChainButton.
 *
 * This widget provides a button showing either a linked or a broken
 * chain that can be used to link two entries, spinbuttons, colors or
 * other GUI elements and show that they may be locked. Use it for
 * example to connect X and Y ratios to provide the possibility of a
 * constrained aspect ratio.
 *
 * The #GimpChainButton only gives visual feedback, it does not really
 * connect widgets. You have to take care of locking the values
 * yourself by checking the state of the #GimpChainButton whenever a
 * value changes in one of the connected widgets and adjusting the
 * other value if necessary.
 **/


enum
{
  PROP_0,
  PROP_POSITION
};

enum
{
  TOGGLED,
  LAST_SIGNAL
};

static void      gimp_chain_button_constructed      (GObject         *object);
static void      gimp_chain_button_set_property     (GObject         *object,
                                                     guint            property_id,
                                                     const GValue    *value,
                                                     GParamSpec      *pspec);
static void      gimp_chain_button_get_property     (GObject         *object,
                                                     guint            property_id,
                                                     GValue          *value,
                                                     GParamSpec      *pspec);

static void      gimp_chain_button_clicked_callback (GtkWidget       *widget,
                                                     GimpChainButton *button);
static void      gimp_chain_button_update_image     (GimpChainButton *button);

static GtkWidget * gimp_chain_line_new            (GimpChainPosition  position,
                                                   gint               which);


G_DEFINE_TYPE (GimpChainButton, gimp_chain_button, GTK_TYPE_TABLE)

#define parent_class gimp_chain_button_parent_class

static guint gimp_chain_button_signals[LAST_SIGNAL] = { 0 };

static const gchar * const gimp_chain_icon_names[] =
{
  GIMP_STOCK_HCHAIN,
  GIMP_STOCK_HCHAIN_BROKEN,
  GIMP_STOCK_VCHAIN,
  GIMP_STOCK_VCHAIN_BROKEN
};


static void
gimp_chain_button_class_init (GimpChainButtonClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);

  object_class->constructed  = gimp_chain_button_constructed;
  object_class->set_property = gimp_chain_button_set_property;
  object_class->get_property = gimp_chain_button_get_property;

  gimp_chain_button_signals[TOGGLED] =
    g_signal_new ("toggled",
                  G_TYPE_FROM_CLASS (klass),
                  G_SIGNAL_RUN_FIRST,
                  G_STRUCT_OFFSET (GimpChainButtonClass, toggled),
                  NULL, NULL,
                  g_cclosure_marshal_VOID__VOID,
                  G_TYPE_NONE, 0);

  klass->toggled = NULL;

  /**
   * GimpChainButton:position:
   *
   * The position in which the chain button will be used.
   *
   * Since: 2.4
   */
  g_object_class_install_property (object_class, PROP_POSITION,
                                   g_param_spec_enum ("position", NULL, NULL,
                                                      GIMP_TYPE_CHAIN_POSITION,
                                                      GIMP_CHAIN_TOP,
                                                      G_PARAM_CONSTRUCT_ONLY |
                                                      GIMP_PARAM_READWRITE));
}

static void
gimp_chain_button_init (GimpChainButton *button)
{
  button->position = GIMP_CHAIN_TOP;
  button->active   = FALSE;
  button->image    = gtk_image_new ();
  button->button   = gtk_button_new ();

  gtk_button_set_relief (GTK_BUTTON (button->button), GTK_RELIEF_NONE);
  gtk_container_add (GTK_CONTAINER (button->button), button->image);
  gtk_widget_show (button->image);

  g_signal_connect (button->button, "clicked",
                    G_CALLBACK (gimp_chain_button_clicked_callback),
                    button);
}

static void
gimp_chain_button_constructed (GObject *object)
{
  GimpChainButton *button = GIMP_CHAIN_BUTTON (object);

  G_OBJECT_CLASS (parent_class)->constructed (object);

  button->line1 = gimp_chain_line_new (button->position, 1);
  button->line2 = gimp_chain_line_new (button->position, -1);

  gimp_chain_button_update_image (button);

  if (button->position & GIMP_CHAIN_LEFT) /* are we a vertical chainbutton? */
    {
      gtk_table_resize (GTK_TABLE (button), 3, 1);
      gtk_table_attach (GTK_TABLE (button), button->button, 0, 1, 1, 2,
                        GTK_SHRINK, GTK_SHRINK, 0, 0);
      gtk_table_attach_defaults (GTK_TABLE (button),
                                 button->line1, 0, 1, 0, 1);
      gtk_table_attach_defaults (GTK_TABLE (button),
                                 button->line2, 0, 1, 2, 3);
    }
  else
    {
      gtk_table_resize (GTK_TABLE (button), 1, 3);
      gtk_table_attach (GTK_TABLE (button), button->button, 1, 2, 0, 1,
                        GTK_SHRINK, GTK_SHRINK, 0, 0);
      gtk_table_attach_defaults (GTK_TABLE (button),
                                 button->line1, 0, 1, 0, 1);
      gtk_table_attach_defaults (GTK_TABLE (button),
                                 button->line2, 2, 3, 0, 1);
    }

  gtk_widget_show (button->button);
  gtk_widget_show (button->line1);
  gtk_widget_show (button->line2);
}

static void
gimp_chain_button_set_property (GObject      *object,
                                guint         property_id,
                                const GValue *value,
                                GParamSpec   *pspec)
{
  GimpChainButton *button = GIMP_CHAIN_BUTTON (object);

  switch (property_id)
    {
    case PROP_POSITION:
      button->position = g_value_get_enum (value);
      break;

    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
      break;
    }
}

static void
gimp_chain_button_get_property (GObject    *object,
                                guint       property_id,
                                GValue     *value,
                                GParamSpec *pspec)
{
  GimpChainButton *button = GIMP_CHAIN_BUTTON (object);

  switch (property_id)
    {
    case PROP_POSITION:
      g_value_set_enum (value, button->position);
      break;

    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
      break;
    }
}

/**
 * gimp_chain_button_new:
 * @position: The position you are going to use for the button
 *            with respect to the widgets you want to chain.
 *
 * Creates a new #GimpChainButton widget.
 *
 * This returns a button showing either a broken or a linked chain and
 * small clamps attached to both sides that visually group the two widgets
 * you want to connect. This widget looks best when attached
 * to a table taking up two columns (or rows respectively) next
 * to the widgets that it is supposed to connect. It may work
 * for more than two widgets, but the look is optimized for two.
 *
 * Returns: Pointer to the new #GimpChainButton, which is inactive
 *          by default. Use gimp_chain_button_set_active() to
 *          change its state.
 */
GtkWidget *
gimp_chain_button_new (GimpChainPosition position)
{
  return g_object_new (GIMP_TYPE_CHAIN_BUTTON,
                       "position", position,
                       NULL);
}

/**
 * gimp_chain_button_set_active:
 * @button: Pointer to a #GimpChainButton.
 * @active: The new state.
 *
 * Sets the state of the #GimpChainButton to be either locked (%TRUE) or
 * unlocked (%FALSE) and changes the showed pixmap to reflect the new state.
 */
void
gimp_chain_button_set_active (GimpChainButton  *button,
                              gboolean          active)
{
  g_return_if_fail (GIMP_IS_CHAIN_BUTTON (button));

  if (button->active != active)
    {
      button->active = active ? TRUE : FALSE;

      gimp_chain_button_update_image (button);
    }
}

/**
 * gimp_chain_button_get_active
 * @button: Pointer to a #GimpChainButton.
 *
 * Checks the state of the #GimpChainButton.
 *
 * Returns: %TRUE if the #GimpChainButton is active (locked).
 */
gboolean
gimp_chain_button_get_active (GimpChainButton *button)
{
  g_return_val_if_fail (GIMP_IS_CHAIN_BUTTON (button), FALSE);

  return button->active;
}

static void
gimp_chain_button_clicked_callback (GtkWidget       *widget,
                                    GimpChainButton *button)
{
  g_return_if_fail (GIMP_IS_CHAIN_BUTTON (button));

  gimp_chain_button_set_active (button, ! button->active);

  g_signal_emit (button, gimp_chain_button_signals[TOGGLED], 0);
}

static void
gimp_chain_button_update_image (GimpChainButton *button)
{
  guint i;

  i = ((button->position & GIMP_CHAIN_LEFT) << 1) + (button->active ? 0 : 1);

  gtk_image_set_from_icon_name (GTK_IMAGE (button->image),
                                gimp_chain_icon_names[i],
                                GTK_ICON_SIZE_BUTTON);
}


/* GimpChainLine is a simple no-window widget for drawing the lines.
 *
 * Originally this used to be a GtkDrawingArea but this turned out to
 * be a bad idea. We don't need an extra window to draw on and we also
 * don't need any input events.
 */

static GType     gimp_chain_line_get_type     (void) G_GNUC_CONST;
static gboolean  gimp_chain_line_expose_event (GtkWidget       *widget,
                                               GdkEventExpose  *event);

struct _GimpChainLine
{
  GtkWidget          parent_instance;
  GimpChainPosition  position;
  gint               which;
};

typedef struct _GimpChainLine  GimpChainLine;
typedef GtkWidgetClass         GimpChainLineClass;

G_DEFINE_TYPE (GimpChainLine, gimp_chain_line, GTK_TYPE_WIDGET)

static void
gimp_chain_line_class_init (GimpChainLineClass *klass)
{
  GtkWidgetClass *widget_class = GTK_WIDGET_CLASS (klass);

  widget_class->expose_event = gimp_chain_line_expose_event;
}

static void
gimp_chain_line_init (GimpChainLine *line)
{
  gtk_widget_set_has_window (GTK_WIDGET (line), FALSE);
}

static GtkWidget *
gimp_chain_line_new (GimpChainPosition  position,
                     gint               which)
{
  GimpChainLine *line = g_object_new (gimp_chain_line_get_type (), NULL);

  line->position = position;
  line->which    = which;

  return GTK_WIDGET (line);
}

static gboolean
gimp_chain_line_expose_event (GtkWidget      *widget,
                              GdkEventExpose *event)
{
  GtkStyle          *style = gtk_widget_get_style (widget);
  GimpChainLine     *line  = ((GimpChainLine *) widget);
  GtkAllocation      allocation;
  GdkPoint           points[3];
  GimpChainPosition  position;
  cairo_t           *cr;

  gtk_widget_get_allocation (widget, &allocation);

  cr = gdk_cairo_create (gtk_widget_get_window (widget));
  gdk_cairo_region (cr, event->region);
  cairo_translate (cr, allocation.x, allocation.y);
  cairo_clip (cr);

#define SHORT_LINE 4
  points[0].x = allocation.width  / 2;
  points[0].y = allocation.height / 2;

  position = line->position;

  if (gtk_widget_get_direction (widget) == GTK_TEXT_DIR_RTL)
    {
      switch (position)
        {
        case GIMP_CHAIN_TOP:
        case GIMP_CHAIN_BOTTOM:
          break;

        case GIMP_CHAIN_LEFT:
          position = GIMP_CHAIN_RIGHT;
          break;

        case GIMP_CHAIN_RIGHT:
          position = GIMP_CHAIN_LEFT;
          break;
        }
    }

  switch (position)
    {
    case GIMP_CHAIN_LEFT:
      points[0].x += SHORT_LINE;
      points[1].x = points[0].x - SHORT_LINE;
      points[1].y = points[0].y;
      points[2].x = points[1].x;
      points[2].y = (line->which == 1 ? allocation.height - 1 : 0);
      break;

    case GIMP_CHAIN_RIGHT:
      points[0].x -= SHORT_LINE;
      points[1].x = points[0].x + SHORT_LINE;
      points[1].y = points[0].y;
      points[2].x = points[1].x;
      points[2].y = (line->which == 1 ? allocation.height - 1 : 0);
      break;

    case GIMP_CHAIN_TOP:
      points[0].y += SHORT_LINE;
      points[1].x = points[0].x;
      points[1].y = points[0].y - SHORT_LINE;
      points[2].x = (line->which == 1 ? allocation.width - 1 : 0);
      points[2].y = points[1].y;
      break;

    case GIMP_CHAIN_BOTTOM:
      points[0].y -= SHORT_LINE;
      points[1].x = points[0].x;
      points[1].y = points[0].y + SHORT_LINE;
      points[2].x = (line->which == 1 ? allocation.width - 1 : 0);
      points[2].y = points[1].y;
      break;

    default:
      return FALSE;
    }

  cairo_move_to (cr, points[0].x, points[0].y);
  cairo_line_to (cr, points[1].x, points[1].y);
  cairo_line_to (cr, points[2].x, points[2].y);

  cairo_set_line_width (cr, 2.0);
  cairo_set_line_cap (cr, CAIRO_LINE_CAP_BUTT);
  gdk_cairo_set_source_color (cr, &style->fg[GTK_STATE_NORMAL]);

  cairo_stroke (cr);

  cairo_destroy (cr);

  return TRUE;
}
