/**
 * @file gihex_circular_step_bar.h
 * @author Yogi Astawan (yogi.astawan@gmail.com)
 * @brief Widget GihexCircularStepBar
 * @version 0.1.0
 * @date 2023-12-13
 *
 * @copyright Copyright (c) 2023
 *
 * ## Description {#gihex_circular_step_bar}
 *
 * Create awesome circurlar step bar
 *
 * ![GihexCircularStepBar](screenshoot/gihex_circular_step_bar.png)
 *
 * ## CSS Node
 *
 * Style gauge bar using name `gihex_circular_step_bar`. Example:
 * ```css
 *
 * gihex_circular_step_bar{
 *      margin: 20px 20px;
 * }
 *
 * ```
 *
 * ## Properties
 *
 * | Property | UI Name | Setter | Getter | Type | Read | Write | Default Value | Description |
 * |----------|---------|--------|--------|------|------|-------|---------------|-------------|
 * | Value | value | gihex_circular_step_bar_set_value() | gihex_circular_step_bar_get_value() | double | Yes | Yes | 30.0 | Value of GihexCircularStepBar |
 * | Minimum value | min-value | gihex_circular_step_bar_set_min_value() | gihex_circular_step_bar_get_min_value() | double | Yes | Yes | 0.0 | Minimum value of GihexCircularStepBar |
 * | Maximum value | max-value | gihex_circular_step_bar_set_max_value() | gihex_circular_step_bar_get_max_value() | double | Yes | Yes | 100.0 | Maximum Value of GihexCircularStepBar |
 * | Color track | color-track | gihex_circular_step_bar_set_color_step_track() | - | GdkRGBA | Yes | Yes | <ul><li>r: 181</li><li>g: 211</li><li>b: 211</li><li>a: 255</li></ul> | Color of background step |
 * | Color stroke | color-stroke | gihex_circular_step_bar_set_color_circle_outest() | - | GdkRGBA | Yes | Yes | <ul><li>r: 15</li><li>g: 160</li><li>b: 151</li><li>a: 255</li></ul> | Color of outest circle |
 * | Color bar | color-bar | gihex_circular_step_bar_set_color_step_bar() | - | GdkRGBA | Yes | Yes | <ul><li>r: 15</li><li>g: 160</li><li>b: 151</li><li>a: 255</li></ul> | Color of step bar |
 * | Color text | color-text | gihex_circular_step_bar_set_color_text() | - | GdkRGBA | Yes | Yes | <ul><li>r: 15</li><li>g: 160</li><li>b: 151</li><li>a: 255</li></ul> | Color of text |
 * | Value font size | value-font-size | gihex_circular_step_bar_set_font_size_value() | - | double | Yes | Yes | 12.0 | Font size of text value |
 * | Sub font size | sub-font-size | gihex_circular_step_bar_set_sub_font_size() | - | double | Yes | Yes | 6.0 | Font size of text name and unit |
 * | Unit | unit | gihex_circular_step_bar_set_unit() | - | string | Yes | Yes | "%" | Unit of GihexCircularStepBar |
 * | Name | name | gihex_circular_step_bar_set_name() | - | string | Yes | Yes | "Gauge Bar" | Name of GihexCircularStepBar |
 * | Number steps | numb-step | gihex_circular_step_bar_set_numb_step() | - | uint8_t | Yes | Yes | 20 | Number of steps in GihexCircularStepBar |
 * | Space step | space-step | gihex_circular_step_bar_set_step_space() | - | double | Yes | Yes | 3.0 | Space between steps |
 * | Indeterminate state | indeterminate | gihex_circular_step_bar_set_indeterminate() | - | bool | Yes | Yes | false | State of the GihexCircularStepBar. (currently not work) |
 *
 * ## Example
 * ```c
 * #include <gtk/gtk.h>
 *
 * #include <gihex_circular_step_bar.h>
 *
 * static void on_activate(GtkApplication *app)
 * {
 *     // Create a new window
 *     GtkWidget *window = gtk_application_window_new(app);
 *     gtk_window_set_title(GTK_WINDOW(window), "Gihex Gauge Bar");
 *     // Create a new box
 *     GtkWidget *box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 20);
 *     // Create new gauge
 *     GtkWidget *gauge = gihex_circular_step_bar_new();
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

#include <gtk/gtk.h>

#include <gihex_color.h>

G_BEGIN_DECLS

#define GIHEX_TYPE_CIRCULAR_STEP_BAR gihex_circular_step_bar_get_type()

G_DECLARE_FINAL_TYPE(GihexCircularStepBar, gihex_circular_step_bar, GIHEX, CIRCULAR_STEP_BAR, GtkWidget);

/**
 * @brief Create new `GihexCircularStepBar` widget
 *
 * @param  NONE
 * @return Pointer of `GtkWidget`
 */
GtkWidget *gihex_circular_step_bar_new(void);

/**
 * @brief Set value to `GihexCircularStepBar`.
 * @param self Pointer of `GihexCircularStepBar`.
 * @param value Value to set with type `double`
 *
 * @note Value can also be set with property using name `value`. Property `value` must be range between property `min-value` and `max-value`.
 */
void gihex_circular_step_bar_set_value(GihexCircularStepBar *self, gdouble value);

/**
 * @brief Get current value of `GihexCircularStepBar`
 *
 * @param self Pointer to `GihexCircularStepBar`
 * @return Value of GihexCircularStepBar. Return type is `double`.
 */
gdouble gihex_circular_step_bar_get_value(GihexCircularStepBar *self);

/**
 * @brief Set minimum value of `GihexCircularStepBar`
 *
 * @param self Pointer to `GihexCircularStepBar`
 * @param min_value Minimum value to set with type double.
 *
 * @note Minimum value can also be set with property using name `min-value`. Minimum value must be lower than property `max-value`.
 */
void gihex_circular_step_bar_set_min_value(GihexCircularStepBar *self, gdouble min_value);

/**
 * @brief Get minimum value of `GihexCircularStepBar`
 *
 * @param self Pointer to `GihexCircularStepBar`
 * @return Return type is `double`
 */
double gihex_circular_step_bar_get_min_value(GihexCircularStepBar *self);

/**
 * @brief Set maximum value of `GihexCircularStepBar`
 *
 * @param self Pointer to `GihexCircularStepBar`
 * @param max_value Maximum value to set with type double.
 *
 * @note Maximum value can also be set with property using name `max-value`. Minimum value must be greather than property `min-value`.
 */
void gihex_circular_step_bar_set_max_value(GihexCircularStepBar *self, gdouble max_value);

/**
 * @brief Get maximum value of `GihexCircularStepBar`
 *
 * @param self Pointer to `GihexCircularStepBar`
 * @return Return type is `double`
 */
double gihex_circular_step_bar_get_max_value(GihexCircularStepBar *self);

/**
 * @brief Set color step track of `GihexCircularStepBar`
 *
 * @param self Pointer to `GihexCircularStepBar`
 * @param color \ref gihex_color "GihexColor" set
 *
 * @note Color track can also be set with property using name `color-track` with value `GdkRGBA`. Example:
 * ```xml
 *
 * <property name="color-track">rgb(100,100,255)</property>
 *
 * ```
 */
void gihex_circular_step_bar_set_color_step_track(GihexCircularStepBar *self, GihexColor color);

/**
 * @brief Set color outest curcle of `GihexCircularStepBar`
 *
 * @param self Pointer to `GihexCircularStepBar`
 * @param color \ref gihex_color "GihexColor" to set
 *
 * @note Color stroke can also be set with property using name `color-stroke` with value `GdkRGBA`. Example:
 * ```xml
 *
 * <property name="color-stroke">rgb(100,100,255)</property>
 *
 * ```
 */
void gihex_circular_step_bar_set_color_circle_outest(GihexCircularStepBar *self, GihexColor color);

/**
 * @brief Set color step bar of `GihexCircularStepBar`
 *
 * @param self Pointer to `GihexCircularStepBar`
 * @param color \ref gihex_color "GihexColor" to set
 *
 * @note Color bar can also be set with property using name `color-bar` with value `GdkRGBA`. Example:
 * ```xml
 *
 * <property name="color-bar">rgb(100,100,255)</property>
 *
 * ```
 */
void gihex_circular_step_bar_set_color_step_bar(GihexCircularStepBar *self, GihexColor color);

/**
 * @brief Set font size of value
 *
 * @param self Pointer to `GihexCircularStepBar`
 * @param size font size to set with type double.
 */
void gihex_circular_step_bar_set_font_size_value(GihexCircularStepBar *self, gdouble size);

/**
 * @brief Set font size of sub text (name and unit)
 *
 * @param self Pointer to `GihexCircularStepBar`
 * @param size font size to set with type double.
 */
void gihex_circular_step_bar_set_sub_font_size(GihexCircularStepBar *self, gdouble size);

/**
 * @brief Set color text of `GihexCircularStepBar`
 *
 * @param self Pointer to `GihexCircularStepBar`
 * @param color \ref gihex_color "GihexColor" to set
 *
 * @note Color text can also be set with property using name `color-text` with value `GdkRGBA`. Example:
 * ```xml
 *
 * <property name="color-text">rgb(100,100,255)</property>
 *
 * ```
 */
void gihex_circular_step_bar_set_color_text(GihexCircularStepBar *self, GihexColor color);

/**
 * @brief Set unit of `GihexCircularStepBar`
 *
 * @param self Pointer to `GihexCircularStepBar`
 * @param unit Unit to set.
 *
 * @note Property name is `unit` with type `string`
 */
void gihex_circular_step_bar_set_unit(GihexCircularStepBar *self, const char *unit);

/**
 * @brief Set name of `GihexCircularStepBar`
 *
 * @param self Pointer to `GihexCircularStepBar`
 * @param name Name to set.
 *
 * @note Property name is `name` with type `string`
 */
void gihex_circular_step_bar_set_name(GihexCircularStepBar *self, const char *name);

/**
 * @brief Set number steps of `GihexCircularStepBar`
 *
 * @param self Pointer to `GihexCircularStepBar`
 * @param numb value to set.
 *
 * @note Property name is `numb-step` with type `uint8_t`
 */
void gihex_circular_step_bar_set_numb_step(GihexCircularStepBar *self, uint8_t numb);

/**
 * @brief Set GihexCircularStepBar indeterminate state.
 *
 * @param self Pointer to `GihexCircularStepBar`
 * @param state Value to set.
 *
 * @note Property name is `indeterminate` with type `bool`
 */
void gihex_circular_step_bar_set_indeterminate(GihexCircularStepBar *self, bool state);

/**
 * @brief Set space between step of GihexCircularStepBar.
 *
 * @param self Pointer to `GihexCircularStepBar`
 * @param space Space to set.
 *
 * @note Property name is `space-step` with type `double`
 */
void gihex_circular_step_bar_set_step_space(GihexCircularStepBar *self, double space);

G_END_DECLS