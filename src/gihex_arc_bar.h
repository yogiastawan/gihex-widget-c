/**
 * @file gihex_arc_bar.h
 * @author Yogi Astawan (yogi.astawan@gmail.com)
 * @brief Widget GihexArcBar
 * @version 0.1.0
 * @date 2023-12-14
 *
 * @copyright Copyright (c) 2023
 *
 * ## Introduction {#gihex_arc_bar}
 *
 * Create awesome Arc bar
 *
 * ![GihexArcBar](screenshoot/gihex_arc_bar.png)
 *
 * ## CSS Node
 *
 * Style Arc bar using name `gihex_arc_bar`. Example:
 * ```css
 *
 * gihex_arc_bar{
 *      margin: 20px 20px;
 * }
 *
 * ```
 *
 * ## Properties
 *
 * | Property | UI Name | Setter | Getter | Type | Read | Write | Default Value | Description |
 * |----------|---------|--------|--------|------|------|-------|---------------|-------------|
 * | Value | value | gihex_arc_bar_set_value() | gihex_arc_bar_get_value() | double | Yes | Yes | 30.0 | Value of GihexArcBar |
 * | Minimum value | min-value | gihex_arc_bar_set_min_value() | gihex_arc_bar_get_min_value() | double | Yes | Yes | 0.0 | Minimum value of GihexArcBar |
 * | Maximum value | max-value | gihex_arc_bar_set_max_value() | gihex_arc_bar_get_max_value() | double | Yes | Yes | 100.0 | Maximum Value of GihexArcBar |
 * | Color track | color-track | gihex_arc_bar_set_color_track() | - | GdkRGBA | Yes | Yes | <ul><li>r: 42</li><li>g: 56</li><li>b: 53</li><li>a: 255</li></ul> | Color of background bar |
 * | Color stroke | color-stroke | gihex_arc_bar_set_color_stroke() | - | GdkRGBA | Yes | Yes | <ul><li>r: 42</li><li>g: 56</li><li>b: 53</li><li>a: 255</li></ul> | Color of stroke background bar |
 * | Color bar | color-bar | gihex_arc_bar_set_color_bar() | - | GdkRGBA | Yes | Yes | <ul><li>r: 0</li><li>g: 168</li><li>b: 174</li><li>a: 255</li></ul> | Color of bar |
 * | Color text | color-text | gihex_arc_bar_set_color_text() | - | GdkRGBA | Yes | Yes | <ul><li>r: 0</li><li>g: 168</li><li>b: 174</li><li>a: 255</li></ul> | Color of text |
 * | Value font size | value-font-size | gihex_arc_bar_set_font_size_value() | - | double | Yes | Yes | 24.0 | Font size of text value |
 * | Sub font size | sub-font-size | gihex_arc_bar_set_sub_font_size() | - | double | Yes | Yes | 12.0 | Font size of text name and unit |
 * | Unit | unit | gihex_arc_bar_set_unit() | - | string | Yes | Yes | "%" | Unit of GihexArcBar |
 * | Name | name | gihex_arc_bar_set_name() | - | string | Yes | Yes | "Arc Bar" | Name of GihexArcBar |
 * | Thickness | thickness | gihex_arc_bar_set_thickness() | - | double | Yes | Yes | 9.0 | Thisckness of bar |
 * | Indicator Size| indicator-size | gihex_arc_bar_set_indicator_size() | - | double | Yes | Yes | 48.0 | Size of indicator |
 *
 * ## Example
 * ```c
 * #include <gtk/gtk.h>
 *
 * #include <gihex_arc_bar.h>
 *
 * static void on_activate(GtkApplication *app)
 * {
 *     // Create a new window
 *     GtkWidget *window = gtk_application_window_new(app);
 *     gtk_window_set_title(GTK_WINDOW(window), "Gihex Arc Bar");
 *     // Create a new box
 *     GtkWidget *box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 20);
 *     // Create new arc
 *     GtkWidget *arc = gihex_arc_bar_new();
 *     gtk_box_append(GTK_BOX(box), arc);
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

#include <gtk/gtk.h>
#include <gihex_color.h>

G_BEGIN_DECLS

#define GIHEX_TYPE_ARC_BAR gihex_arc_bar_get_type()

G_DECLARE_FINAL_TYPE(GihexArcBar, gihex_arc_bar, GIHEX, ARC_BAR, GtkWidget);

/**
 * @brief Create new `GihexArcBar` widget
 *
 * @param  NONE
 * @return Pointer of `GtkWidget`
 */
GtkWidget *gihex_arc_bar_new(void);

/**
 * @brief Set value to `GihexArcBar`.
 * @param self Pointer of `GihexArcBar`.
 * @param value Value to set with type `double`
 *
 * @note Value can also be set with property using name `value`. Property `value` must be range between property `min-value` and `max-value`.
 */
void gihex_arc_bar_set_value(GihexArcBar *self, gdouble value);

/**
 * @brief Get current value of `GihexArcBar`
 *
 * @param self Pointer to `GihexArcBar`
 * @return Value of GihexArcBar. Return type is `double`.
 */
gdouble gihex_arc_bar_get_value(GihexArcBar *self);

/**
 * @brief Set minimum value of `GihexArcBar`
 *
 * @param self Pointer to `GihexArcBar`
 * @param min_value Minimum value to set with type double.
 *
 * @note Minimum value can also be set with property using name `min-value`. Minimum value must be lower than property `max-value`.
 */
void gihex_arc_bar_set_min_value(GihexArcBar *self, gdouble min_value);

/**
 * @brief Get minimum value of `GihexArcBar`
 *
 * @param self Pointer to `GihexArcBar`
 * @return Return type is `double`
 */
double gihex_arc_bar_get_min_value(GihexArcBar *self);

/**
 * @brief Set maximum value of `GihexArcBar`
 *
 * @param self Pointer to `GihexArcBar`
 * @param max_value Maximum value to set with type double.
 *
 * @note Maximum value can also be set with property using name `max-value`. Minimum value must be greather than property `min-value`.
 */
void gihex_arc_bar_set_max_value(GihexArcBar *self, gdouble max_value);

/**
 * @brief Get maximum value of `GihexArcBar`
 *
 * @param self Pointer to `GihexArcBar`
 * @return Return type is `double`
 */
double gihex_arc_bar_get_max_value(GihexArcBar *self);

/**
 * @brief Set color track of `GihexArcBar`
 *
 * @param self Pointer to `GihexArcBar`
 * @param color \ref gihex_color "GihexColor" set
 *
 * @note Color track can also be set with property using name `color-track` with value `GdkRGBA`. Example:
 * ```xml
 *
 * <property name="color-track">rgb(100,100,255)</property>
 *
 * ```
 */
void gihex_arc_bar_set_color_track(GihexArcBar *self, GihexColor color);

/**
 * @brief Set color indicator of `GihexArcBar`
 *
 * @param self Pointer to `GihexArcBar`
 * @param color \ref gihex_color "GihexColor" to set
 *
 * @note Color indicator can also be set with property using name `color-indicator` with value `GdkRGBA`. Example:
 * ```xml
 *
 * <property name="color-indicator">rgb(100,100,255)</property>
 *
 * ```
 */
void gihex_arc_bar_set_color_indicator(GihexArcBar *self, GihexColor color);

/**
 * @brief Set color bar of `GihexArcBar`
 *
 * @param self Pointer to `GihexArcBar`
 * @param color \ref gihex_color "GihexColor" to set
 *
 * @note Color bar can also be set with property using name `color-bar` with value `GdkRGBA`. Example:
 * ```xml
 *
 * <property name="color-bar">rgb(100,100,255)</property>
 *
 * ```
 */
void gihex_arc_bar_set_color_bar(GihexArcBar *self, GihexColor color);

/**
 * @brief Set font size of value
 *
 * @param self Pointer to `GihexArcBar`
 * @param size font size to set with type double.
 *
 * @note Property name is `value-font-size` with type `double`.
 */
void gihex_arc_bar_set_font_size_value(GihexArcBar *self, gdouble size);

/**
 * @brief Set font size of sub text (name and unit)
 *
 * @param self Pointer to `GihexArcBar`
 * @param size font size to set with type double.
 *
 * @note Property name is `sub-font-size` with type `double`.
 */
void gihex_arc_bar_set_sub_font_size(GihexArcBar *self, gdouble size);

/**
 * @brief Set color text of `GihexArcBar`
 *
 * @param self Pointer to `GihexArcBar`
 * @param color \ref gihex_color "GihexColor" to set
 *
 * @note Color text can also be set with property using name `color-text` with value `GdkRGBA`. Example:
 * ```xml
 *
 * <property name="color-text">rgb(100,100,255)</property>
 *
 * ```
 */
void gihex_arc_bar_set_color_text(GihexArcBar *self, GihexColor color);

/**
 * @brief Set unit of `GihexArcBar`
 *
 * @param self Pointer to `GihexArcBar`
 * @param unit Unit to set.
 *
 * @note Property name is `unit` with type `string`
 */
void gihex_arc_bar_set_unit(GihexArcBar *self, const char *unit);

/**
 * @brief Set name of `GihexArcBar`
 *
 * @param self Pointer to `GihexArcBar`
 * @param name Name to set.
 *
 * @note Property name is `name` with type `string`
 */
void gihex_arc_bar_set_name(GihexArcBar *self, const char *name);

/**
 * @brief Set thickness of bar
 *
 * @param self Pointer to GihexArcBar
 * @param value value to set
 *
 * @note Property name is `thickness` with type `double`.
 */
void gihex_arc_bar_set_thickness(GihexArcBar *self, double value);

/**
 * @brief Set size of indicator
 *
 * @param self Pointer to GihexArcBar
 * @param size Size to set
 *
 * @note Property name is `indicator-size` with type `double`.
 */
void gihex_arc_bar_set_indicator_size(GihexArcBar *self, double size);

G_END_DECLS