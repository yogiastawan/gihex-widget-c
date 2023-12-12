#pragma once

#include <gtk/gtk.h>

#include <gihex_color.h>

G_BEGIN_DECLS

#define GIHEX_TYPE_GAUGE_BAR gihex_gauge_bar_get_type()
G_DECLARE_FINAL_TYPE(GihexGaugeBar, gihex_gauge_bar, GIHEX, GAUGE_BAR, GtkWidget);

GtkWidget *gihex_gauge_bar_new(void);
void gihex_gauge_bar_set_value(GihexGaugeBar *self, gdouble value);
void gihex_gauge_bar_set_min_value(GihexGaugeBar *self, gdouble min_value);
void gihex_gauge_bar_set_max_value(GihexGaugeBar *self, gdouble max_value);
void gihex_gauge_bar_set_color_track(GihexGaugeBar *self, GihexColor color);
void gihex_gauge_bar_set_color_stroke(GihexGaugeBar *self, GihexColor color);
void gihex_gauge_bar_set_color_bar(GihexGaugeBar *self, GihexColor color);

G_END_DECLS