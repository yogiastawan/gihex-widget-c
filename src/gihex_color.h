/**
 * @file gihex_color.h
 * @author Yogi Astawan (yogi.astawan@gmail.com)
 * @brief Utility that contain color usage for Gihex Widget.
 * @version 0.1.0
 * @date 2023-12-13
 *
 * @copyright Copyright (c) 2023
 *
 * ## Description {#gihex_color}
 * Object to setting color in most Gihex Widget.
 */

#pragma once

#include <gtk/gtk.h>

#include <stdlib.h>

G_BEGIN_DECLS

/**
 * @brief Type of GihexColor object
 */
typedef struct _GihexColor GihexColor;

/**
 * @brief _GihexColor color struct
 */
struct _GihexColor
{
    uint8_t r; ///< Red color
    uint8_t g; ///< Green color
    uint8_t b; ///< Blue Color
    uint8_t a; ///< Alpha color
};

/**
 * @brief Create copy of `GihexColor`
 *
 * @param color Pointer to GihexColor
 * @return Return pointer of GihexColor
 */
GihexColor *gihex_color_copy(GihexColor *color);

/**
 * @brief Free and destroy `GihexColor`
 * @param color Pointer to GihexColor
 */
void gihex_color_free(GihexColor *color);

/**
 * @brief Create new `GihexColor`
 *
 * @param red Value of red. Value type is `uint8_t`
 * @param green Value of green. Value type is `uint8_t`
 * @param blue Value of blue. Value type is `uint8_t`
 * @param alpha Value of alpha. Value type is `uint8_t`
 * @return New `GihexColor`
 */
GihexColor gihex_color_new(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha);

/**
 * @brief Convert `GihexColor` into `GdkRGBA`
 * 
 * @param color Pointer to GihexColor
 * @return GdkRGBA
 */
GdkRGBA gihex_color_get_RGBA(const GihexColor *color);

/**
 * @brief Get red part color of `GihexColor`.
 * 
 * @param color Pointer to GihexColor
 * @return Red value with type `double`
 */
double gihex_color_get_red(const GihexColor *color);

/**
 * @brief Get green part color of `GihexColor`.
 * 
 * @param color Pointer to GihexColor
 * @return Green value with type `double`
 */
double gihex_color_get_green(const GihexColor *color);

/**
 * @brief Get blue part color of `GihexColor`.
 * 
 * @param color Pointer to GihexColor
 * @return Blue value with type `double`
 */
double gihex_color_get_blue(const GihexColor *color);

/**
 * @brief Get alpha part color of `GihexColor`.
 * 
 * @param color Pointer to GihexColor
 * @return Alpha value with type `double`
 */
double gihex_color_get_alpha(const GihexColor *color);

G_END_DECLS