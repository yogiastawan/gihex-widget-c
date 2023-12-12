#pragma once

#include <gtk/gtk.h>

#include <stdlib.h>

G_BEGIN_DECLS

typedef struct _GihexColor GihexColor;

struct _GihexColor
{
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a;
};


GihexColor *gihex_color_copy(GihexColor *color);
void gihex_color_free(GihexColor *color);

GihexColor gihex_color_new(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha);

GdkRGBA gihex_color_get_RGBA(const GihexColor *color);
double gihex_color_get_red(const GihexColor *color);
double gihex_color_get_green(const GihexColor *color);
double gihex_color_get_blue(const GihexColor *color);
double gihex_color_get_alpha(const GihexColor *color);

G_END_DECLS