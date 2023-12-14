/**
 * @file gihex_arc_bar.h
 * @author Yogi Astawan (yogi.astawan@gmail.com)
 * @brief Widget GihexArcBar
 * @version 0.1.0
 * @date 2023-12-14
 *
 * @copyright Copyright (c) 2023
 *
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

G_END_DECLS