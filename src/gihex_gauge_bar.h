/**
 * @file gihex_gauge_bar.h
 * @author Yogi Astawan (yogi.astawan@gmail.com)
 * @brief Widget GihexGaugeBar
 * @version 0.1.0
 * @date 2023-12-13
 *
 * @copyright Copyright (c) 2023
 *
 * ## Description {#gihex_gauge_bar}
 *
 * Create awesome gauge bar
 *
 * ![GihexGaugeBar](screenshoot/gihex_gauge_bar.png)
 *
 * ## CSS Node
 *
 * Style gauge bar using name `gihex_gauge_bar`. Example:
 * ```css
 *
 * gihex_gauge_bar{
 *      margin: 20px 20px;
 * }
 *
 * ```
 *
 * ## Properties
 *
 * | Property | UI Name | Setter | Getter | Type | Read | Write | Default Value | Description |
 * |----------|---------|--------|--------|------|------|-------|---------------|-------------|
 * | Value | value | gihex_gauge_bar_set_value() | gihex_gauge_bar_get_value() | double | Yes | Yes | 30.0 | Value of GihexGaugeBar |
 * | Minimum value | min-value | gihex_gauge_bar_set_min_value() | gihex_gauge_bar_get_min_value() | double | Yes | Yes | 0.0 | Minimum value of GihexGaugeBar |
 * | Maximum value | max-value | gihex_gauge_bar_set_max_value() | gihex_gauge_bar_get_max_value() | double | Yes | Yes | 100.0 | Maximum Value of GihexGaugeBar |
 * | Color track | color-track | gihex_gauge_bar_set_color_track() | - | GdkRGBA | Yes | Yes | <ul><li>r: 42</li><li>g: 56</li><li>b: 53</li><li>a: 255</li></ul> | Color of background bar |
 * | Color stroke | color-stroke | gihex_gauge_bar_set_color_stroke() | - | GdkRGBA | Yes | Yes | <ul><li>r: 42</li><li>g: 56</li><li>b: 53</li><li>a: 255</li></ul> | Color of stroke background bar |
 * | Color bar | color-bar | gihex_gauge_bar_set_color_bar() | - | GdkRGBA | Yes | Yes | <ul><li>r: 0</li><li>g: 168</li><li>b: 174</li><li>a: 255</li></ul> | Color of bar |
 * | Color text | color-text | gihex_gauge_bar_set_color_text() | - | GdkRGBA | Yes | Yes | <ul><li>r: 0</li><li>g: 168</li><li>b: 174</li><li>a: 255</li></ul> | Color of text |
 * | Value font size | value-font-size | gihex_gauge_bar_set_font_size_value() | - | double | Yes | Yes | 12.0 | Font size of text value |
 * | Sub font size | sub-font-size | gihex_gauge_bar_set_sub_font_size() | - | double | Yes | Yes | 6.0 | Font size of text name and unit |
 * | Unit | unit | gihex_gauge_bar_set_unit() | - | string | Yes | Yes | "%" | Unit of GihexGaugeBar |
 * | Name | name | gihex_gauge_bar_set_name() | - | string | Yes | Yes | "Gauge Bar" | Name of GihexGaugeBar |
 *
 * ## Example
 * ```c
 * #include <gtk/gtk.h>
 *
 * #include <gihex_gauge_bar.h>
 *
 * static void on_activate(GtkApplication *app)
 * {
 *     // Create a new window
 *     GtkWidget *window = gtk_application_window_new(app);
 *     gtk_window_set_title(GTK_WINDOW(window), "Gihex Gauge Bar");
 *     // Create a new box
 *     GtkWidget *box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 20);
 *     // Create new gauge
 *     GtkWidget *gauge = gihex_gauge_bar_new();
 *     gtk_box_append(GTK_BOX(box), gauge);
 *     gtk_window_set_child(GTK_WINDOW(window), box);
 *     gtk_window_present(GTK_WINDOW(window));
 * }
 *
 * int main(int argc, char *argv[])
 * {
 *     // Create a new application
 *     GtkApplication *app = gtk_application_new("com.example.GtkApplication",
 *                                               G_APPLICATION_FLAGS_NONE);
 *     g_signal_connect(app, "activate", G_CALLBACK(on_activate), NULL);
 *     return g_application_run(G_APPLICATION(app), argc, argv);
 * }
 *
 * ```
 */

#pragma once

#include <gtk/gtk.h>

#include <gihex_color.h>

G_BEGIN_DECLS

#define GIHEX_TYPE_GAUGE_BAR gihex_gauge_bar_get_type()
G_DECLARE_FINAL_TYPE(GihexGaugeBar, gihex_gauge_bar, GIHEX, GAUGE_BAR, GtkWidget);

/**
 * @brief Create new `GihexGaugeBar` widget
 *
 * @param  NONE
 * @return Pointer of `GtkWidget`
 */
GtkWidget *gihex_gauge_bar_new(void);

/**
 * @brief Set value to `GihexGaugeBar`.
 * @param self Pointer of `GihexGaugeBar`.
 * @param value Value to set with type `double`
 *
 * @note Value can also be set with property using name `value`. Property `value` must be range between property `min-value` and `max-value`.
 */
void gihex_gauge_bar_set_value(GihexGaugeBar *self, gdouble value);

/**
 * @brief Get current value of `GihexGaugeBar`
 *
 * @param self Pointer to `GihexGaugeBar`
 * @return Value of GihexGaugeBar. Return type is `double`.
 */
gdouble gihex_gauge_bar_get_value(GihexGaugeBar *self);

/**
 * @brief Set minimum value of `GihexGaugeBar`
 *
 * @param self Pointer to `GihexGaugeBar`
 * @param min_value Minimum value to set with type double.
 *
 * @note Minimum value can also be set with property using name `min-value`. Minimum value must be lower than property `max-value`.
 */
void gihex_gauge_bar_set_min_value(GihexGaugeBar *self, gdouble min_value);

/**
 * @brief Get minimum value of `GihexGaugeBar`
 * 
 * @param self Pointer to `GihexGaugeBar`
 * @return Return type is `double`
 */
double gihex_gauge_bar_get_min_value(GihexGaugeBar *self);

/**
 * @brief Set maximum value of `GihexGaugeBar`
 *
 * @param self Pointer to `GihexGaugeBar`
 * @param max_value Maximum value to set with type double.
 *
 * @note Maximum value can also be set with property using name `max-value`. Minimum value must be greather than property `min-value`.
 */
void gihex_gauge_bar_set_max_value(GihexGaugeBar *self, gdouble max_value);

/**
 * @brief Get maximum value of `GihexGaugeBar`
 * 
 * @param self Pointer to `GihexGaugeBar`
 * @return Return type is `double`
 */
double gihex_gauge_bar_get_max_value(GihexGaugeBar *self);

/**
 * @brief Set color track of `GihexGaugeBar`
 *
 * @param self Pointer to `GihexGaugeBar`
 * @param color \ref gihex_color "GihexColor" set
 *
 * @note Color track can also be set with property using name `color-track` with value `GdkRGBA`. Example:
 * ```xml
 *
 * <property name="color-track">rgb(100,100,255)</property>
 *
 * ```
 */
void gihex_gauge_bar_set_color_track(GihexGaugeBar *self, GihexColor color);

/**
 * @brief Set color dtroke of `GihexGaugeBar`
 *
 * @param self Pointer to `GihexGaugeBar`
 * @param color \ref gihex_color "GihexColor" to set
 *
 * @note Color stroke can also be set with property using name `color-stroke` with value `GdkRGBA`. Example:
 * ```xml
 *
 * <property name="color-stroke">rgb(100,100,255)</property>
 *
 * ```
 */
void gihex_gauge_bar_set_color_stroke(GihexGaugeBar *self, GihexColor color);

/**
 * @brief Set color bar of `GihexGaugeBar`
 *
 * @param self Pointer to `GihexGaugeBar`
 * @param color \ref gihex_color "GihexColor" to set
 *
 * @note Color bar can also be set with property using name `color-bar` with value `GdkRGBA`. Example:
 * ```xml
 *
 * <property name="color-bar">rgb(100,100,255)</property>
 *
 * ```
 */
void gihex_gauge_bar_set_color_bar(GihexGaugeBar *self, GihexColor color);

/**
 * @brief Set font size of value
 *
 * @param self Pointer to `GihexGaugeBar`
 * @param size font size to set with type double.
 */
void gihex_gauge_bar_set_font_size_value(GihexGaugeBar *self, gdouble size);

/**
 * @brief Set font size of sub text (name and unit)
 *
 * @param self Pointer to `GihexGaugeBar`
 * @param size font size to set with type double.
 */
void gihex_gauge_bar_set_sub_font_size(GihexGaugeBar *self, gdouble size);

/**
 * @brief Set color text of `GihexGaugeBar`
 *
 * @param self Pointer to `GihexGaugeBar`
 * @param color \ref gihex_color "GihexColor" to set
 *
 * @note Color text can also be set with property using name `color-text` with value `GdkRGBA`. Example:
 * ```xml
 *
 * <property name="color-text">rgb(100,100,255)</property>
 *
 * ```
 */
void gihex_gauge_bar_set_color_text(GihexGaugeBar *self, GihexColor color);

/**
 * @brief Set unit of `GihexGaugeBar`
 *
 * @param self Pointer to `GihexGaugeBar`
 * @param unit Unit to set.
 */
void gihex_gauge_bar_set_unit(GihexGaugeBar *self, const char *unit);

/**
 * @brief Set name of `GihexGaugeBar`
 *
 * @param self Pointer to `GihexGaugeBar`
 * @param name Name to set.
 */
void gihex_gauge_bar_set_name(GihexGaugeBar *self, const char *name);

G_END_DECLS