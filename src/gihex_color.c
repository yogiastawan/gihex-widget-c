#include <gihex_color.h>

GihexColor *gihex_color_copy(GihexColor *color)
{
    GihexColor *copy;
    copy = g_new(GihexColor, 1);
    memcpy(copy, color, sizeof(GihexColor));
    return copy;
}

void gihex_color_free(GihexColor *color)
{
    g_free(color);
}

GihexColor gihex_color_new(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha)
{
    GihexColor a = {red, green, blue, alpha};
    return a;
}

GdkRGBA gihex_color_get_RGBA(const GihexColor *color)
{
    GdkRGBA rgba = {(float)color->r / 255.0,
                    (float)color->g / 255.0,
                    (float)color->b / 255.0,
                    (float)color->a / 255.0};
    return rgba;
}

double gihex_color_get_red(const GihexColor *color)
{
    return (double)color->r / 255.0;
}

double gihex_color_get_green(const GihexColor *color)
{
    return (double)color->g / 255.0;
}

double gihex_color_get_blue(const GihexColor *color)
{
    return (double)color->b / 255.0;
}

double gihex_color_get_alpha(const GihexColor *color)
{
    return (double)color->a / 255.0;
}