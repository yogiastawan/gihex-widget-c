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
 * @brief Set color track of `GihexCircularStepBar`
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
void gihex_circular_step_bar_set_color_track(GihexCircularStepBar *self, GihexColor color);

/**
 * @brief Set color dtroke of `GihexCircularStepBar`
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
void gihex_circular_step_bar_set_color_stroke(GihexCircularStepBar *self, GihexColor color);

/**
 * @brief Set color bar of `GihexCircularStepBar`
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
void gihex_circular_step_bar_set_color_bar(GihexCircularStepBar *self, GihexColor color);

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
 */
void gihex_circular_step_bar_set_unit(GihexCircularStepBar *self, const char *unit);

/**
 * @brief Set name of `GihexCircularStepBar`
 *
 * @param self Pointer to `GihexCircularStepBar`
 * @param name Name to set.
 */
void gihex_circular_step_bar_set_name(GihexCircularStepBar *self, const char *name);


G_END_DECLS