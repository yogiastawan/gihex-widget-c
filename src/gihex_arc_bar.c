#include <gihex_arc_bar.h>

struct _GihexArcBar
{
    GtkWidget parent_intance;

    gdouble value;
    gdouble min_value;
    gdouble max_value;

    gdouble value_font_size;

    gdouble sub_font_size;

    gdouble thickness;

    gdouble indicator_size;

    GihexColor color_track;
    GihexColor color_indicator;
    GihexColor color_bar;
    GihexColor color_text;

    char *name;
    char *unit;
};

enum
{
    PROP_VALUE = 1,
    PROP_MIN_VALUE,
    PROP_MAX_VALUE,
    PROP_COLOR_TRACK,
    PROP_COLOR_INDICATOR,
    PROP_COLOR_BAR,
    PROP_FONT_SIZE_VALUE,
    PROP_SUB_FONT_SIZE,
    PROP_TEXT_COLOR,
    PROP_UNIT,
    PROP_NAME,
    PROP_THICKNESS,
    PROP_INDICATOR_SIZE,
    NUM_PROP
};

static GParamSpec *arc_props[NUM_PROP] = {
    NULL,
};

G_DEFINE_TYPE(GihexArcBar, gihex_arc_bar, GTK_TYPE_WIDGET);

static void gihex_arc_bar_set_property(GObject *object, guint property_id, const GValue *value, GParamSpec *pspec);
static void gihex_arc_bar_get_property(GObject *object, guint prop_id, GValue *value, GParamSpec *pspec);
static void gihex_arc_bar_dispose(GObject *object);
static void gihex_arc_bar_finalize(GObject *object);

static void gihex_arc_bar_measure(GtkWidget *widget,
                                  GtkOrientation orientation,
                                  int for_size,
                                  int *minimum,
                                  int *natural,
                                  int *minimum_baseline,
                                  int *natural_baseline);
static void gihex_arc_bar_snapshot(GtkWidget *widget, GtkSnapshot *snapshot);

static void gihex_arc_bar_init(GihexArcBar *self)
{
    self->value = 30.0;
    self->min_value = 0.0;
    self->max_value = 100.0;
    self->color_track = gihex_color_new(42, 56, 53, 255);
    self->color_indicator = gihex_color_new(0, 168, 174, 255);
    self->color_bar = gihex_color_new(0, 168, 174, 255);
    self->color_text = gihex_color_new(0, 168, 174, 255);
    self->value_font_size = 24.0;
    self->sub_font_size = 12.0;
    self->thickness = 9.0;
    self->indicator_size = 48.0;
    self->unit = g_strdup("\%");
    self->name = g_strdup("Arc Bar");
}

static void gihex_arc_bar_class_init(GihexArcBarClass *klass)
{
    GObjectClass *o_class = G_OBJECT_CLASS(klass);
    o_class->set_property = gihex_arc_bar_set_property;
    o_class->get_property = gihex_arc_bar_get_property;
    o_class->dispose = gihex_arc_bar_dispose;
    o_class->finalize = gihex_arc_bar_finalize;

    GtkWidgetClass *w_class = GTK_WIDGET_CLASS(klass);
    w_class->snapshot = gihex_arc_bar_snapshot;
    w_class->measure = gihex_arc_bar_measure;

    arc_props[PROP_VALUE] = g_param_spec_double("value", "Value", "Value of GihexArcBar",
                                                -G_MINDOUBLE, G_MAXDOUBLE, 30.0,
                                                G_PARAM_READWRITE | G_PARAM_EXPLICIT_NOTIFY);
    arc_props[PROP_MIN_VALUE] = g_param_spec_double("min-value", "Minimum value", "Minimum value of GihexArcBar",
                                                    -G_MINDOUBLE, G_MAXDOUBLE, 0.0,
                                                    G_PARAM_READWRITE | G_PARAM_EXPLICIT_NOTIFY);
    arc_props[PROP_MAX_VALUE] = g_param_spec_double("max-value", "Maximum value", "Maximum value of GihexArcBar",
                                                    -G_MINDOUBLE, G_MAXDOUBLE, 100.0,
                                                    G_PARAM_READWRITE | G_PARAM_EXPLICIT_NOTIFY);
    arc_props[PROP_COLOR_TRACK] = g_param_spec_boxed("color-track", "Color track", "Color of the track. Arc background",
                                                     GDK_TYPE_RGBA,
                                                     G_PARAM_READWRITE | G_PARAM_EXPLICIT_NOTIFY);
    arc_props[PROP_COLOR_INDICATOR] = g_param_spec_boxed("color-indicator", "Color indicator", "Color of the indicator",
                                                         GDK_TYPE_RGBA,
                                                         G_PARAM_READWRITE | G_PARAM_EXPLICIT_NOTIFY);
    arc_props[PROP_COLOR_BAR] = g_param_spec_boxed("color-bar", "Color bar", "Color of the bar. Arc progress color",
                                                   GDK_TYPE_RGBA,
                                                   G_PARAM_READWRITE | G_PARAM_EXPLICIT_NOTIFY);

    arc_props[PROP_FONT_SIZE_VALUE] = g_param_spec_double("value-font-size", "Font size of value", "Font size of value text",
                                                          -G_MINDOUBLE, G_MAXDOUBLE, 12.0,
                                                          G_PARAM_READWRITE | G_PARAM_EXPLICIT_NOTIFY);

    arc_props[PROP_SUB_FONT_SIZE] = g_param_spec_double("sub-font-size", "Font size of sub text", "Font size of sub text",
                                                        -G_MINDOUBLE, G_MAXDOUBLE, 6.0,
                                                        G_PARAM_READWRITE | G_PARAM_EXPLICIT_NOTIFY);
    arc_props[PROP_TEXT_COLOR] = g_param_spec_boxed("color-text", "Color text", "Color of the text",
                                                    GDK_TYPE_RGBA,
                                                    G_PARAM_READWRITE | G_PARAM_EXPLICIT_NOTIFY);

    arc_props[PROP_UNIT] = g_param_spec_string("unit", "Unit text", "Unit of arc bar", "\%",
                                               G_PARAM_READWRITE | G_PARAM_EXPLICIT_NOTIFY);
    arc_props[PROP_NAME] = g_param_spec_string("name", "Name text", "Name of arc bar", "Arc Bar",
                                               G_PARAM_READWRITE | G_PARAM_EXPLICIT_NOTIFY);

    arc_props[PROP_THICKNESS] = g_param_spec_double("thickness", "Thickness", "Bar Thickness",
                                                    -G_MINDOUBLE, G_MAXDOUBLE, 9.0,
                                                    G_PARAM_READWRITE | G_PARAM_EXPLICIT_NOTIFY);

    arc_props[PROP_INDICATOR_SIZE] = g_param_spec_double("indicator-size", "Indicator size", "Size of side triangle indicator",
                                                         -G_MINDOUBLE, G_MAXDOUBLE, 48.0,
                                                         G_PARAM_READWRITE | G_PARAM_EXPLICIT_NOTIFY);

    g_object_class_install_properties(o_class, NUM_PROP, arc_props);
    gtk_widget_class_set_css_name(w_class, "gihex_arc_bar");
}

void gihex_arc_bar_set_property(GObject *object, guint property_id, const GValue *value, GParamSpec *pspec)
{
    GihexArcBar *self = GIHEX_ARC_BAR(object);
    switch (property_id)
    {
    case PROP_VALUE:
        gihex_arc_bar_set_value(self, g_value_get_double(value));
        break;
    case PROP_MIN_VALUE:
        gihex_arc_bar_set_min_value(self, g_value_get_double(value));
        break;
    case PROP_MAX_VALUE:
        gihex_arc_bar_set_max_value(self, g_value_get_double(value));
        break;
    case PROP_COLOR_TRACK:
    {
        GdkRGBA *clr = (GdkRGBA *)g_value_get_boxed(value);
        gihex_arc_bar_set_color_track(self, gihex_color_new(clr->red * 255, clr->green * 255, clr->blue * 255, clr->alpha * 255));
        break;
    }
    case PROP_COLOR_INDICATOR:
    {
        GdkRGBA *clr1 = g_value_get_boxed(value);
        gihex_arc_bar_set_color_indicator(self, gihex_color_new(clr1->red * 255, clr1->green * 255, clr1->blue * 255, clr1->alpha * 255));
        break;
    }
    case PROP_COLOR_BAR:
    {
        GdkRGBA *clr2 = g_value_get_boxed(value);
        gihex_arc_bar_set_color_bar(self, gihex_color_new(clr2->red * 255, clr2->green * 255, clr2->blue * 255, clr2->alpha * 255));
        break;
    }
    case PROP_FONT_SIZE_VALUE:
        gihex_arc_bar_set_font_size_value(self, g_value_get_double(value));
        break;
    case PROP_SUB_FONT_SIZE:
        gihex_arc_bar_set_sub_font_size(self, g_value_get_double(value));
        break;
    case PROP_TEXT_COLOR:
    {
        GdkRGBA *clr2 = g_value_get_boxed(value);
        gihex_arc_bar_set_color_text(self, gihex_color_new(clr2->red * 255, clr2->green * 255, clr2->blue * 255, clr2->alpha * 255));
        break;
    }
    case PROP_UNIT:
        gihex_arc_bar_set_unit(self, g_value_get_string(value));
        break;
    case PROP_NAME:
        gihex_arc_bar_set_name(self, g_value_get_string(value));
        break;
    case PROP_THICKNESS:
        gihex_arc_bar_set_thickness(self, g_value_get_double(value));
        break;
    case PROP_INDICATOR_SIZE:
        gihex_arc_bar_set_indicator_size(self, g_value_get_double(value));
        break;
    default:
        G_OBJECT_WARN_INVALID_PROPERTY_ID(object, property_id, pspec);
        break;
    }
}

void gihex_arc_bar_get_property(GObject *object, guint prop_id, GValue *value, GParamSpec *pspec)
{

    GihexArcBar *self = GIHEX_ARC_BAR(object);
    switch (prop_id)
    {
    case PROP_VALUE:
        g_value_set_double(value, self->value);
        break;
    case PROP_MIN_VALUE:
        g_value_set_double(value, self->min_value);
        break;
    case PROP_MAX_VALUE:
        g_value_set_double(value, self->max_value);
        break;
    case PROP_COLOR_TRACK:
    {
        GdkRGBA a = {
            (float)self->color_track.r / 255.0,
            (float)self->color_track.g / 255.0,
            (float)self->color_track.b / 255.0,
            (float)self->color_track.a / 255.0};
        g_value_set_boxed(value, gdk_rgba_copy(&a));
        break;
    }
    case PROP_COLOR_INDICATOR:
    {
        GdkRGBA b = {
            (float)self->color_indicator.r / 255.0,
            (float)self->color_indicator.g / 255.0,
            (float)self->color_indicator.b / 255.0,
            (float)self->color_indicator.a / 255.0};
        g_value_set_boxed(value, gdk_rgba_copy(&b));
        break;
    }
    case PROP_COLOR_BAR:
    {
        GdkRGBA c = {
            (float)self->color_bar.r / 255.0,
            (float)self->color_bar.g / 255.0,
            (float)self->color_bar.b / 255.0,
            (float)self->color_bar.a / 255.0};
        g_value_set_boxed(value, gdk_rgba_copy(&c));
        break;
    }
    case PROP_FONT_SIZE_VALUE:
        g_value_set_double(value, self->value_font_size);
        break;
    case PROP_SUB_FONT_SIZE:
        g_value_set_double(value, self->sub_font_size);
        break;
    case PROP_TEXT_COLOR:
    {
        GdkRGBA c = {
            (float)self->color_text.r / 255.0,
            (float)self->color_text.g / 255.0,
            (float)self->color_text.b / 255.0,
            (float)self->color_text.a / 255.0};
        g_value_set_boxed(value, gdk_rgba_copy(&c));
        break;
    }
    case PROP_UNIT:
        g_value_set_string(value, self->unit);
        break;
    case PROP_NAME:
        g_value_set_string(value, self->name);
        break;
    case PROP_THICKNESS:
        g_value_set_double(value, self->thickness);
        break;
    case PROP_INDICATOR_SIZE:
        g_value_set_double(value, self->indicator_size);
        break;
    default:
        G_OBJECT_WARN_INVALID_PROPERTY_ID(object, prop_id, pspec);
        break;
    }
}

void gihex_arc_bar_dispose(GObject *object)
{
    GihexArcBar *bar = GIHEX_ARC_BAR(object);

    G_OBJECT_CLASS(gihex_arc_bar_parent_class)->dispose(object);
}

void gihex_arc_bar_finalize(GObject *object)
{
    GihexArcBar *bar = GIHEX_ARC_BAR(object);
    g_free(bar->name);
    g_free(bar->unit);
    G_OBJECT_CLASS(gihex_arc_bar_parent_class)
        ->finalize(object);
}

void gihex_arc_bar_snapshot(GtkWidget *widget, GtkSnapshot *snapshot)
{
    GihexArcBar *self = GIHEX_ARC_BAR(widget);

    double w = (double)gtk_widget_get_width(widget);
    double h = (double)gtk_widget_get_height(widget);
    gdouble size = w;
    if (w > h)
    {
        size = h;
    }

    gdouble indicator_side = self->indicator_size * size / 300.0;

    gdouble thickness = self->thickness * size / 300.0;
    gdouble ro = (size - thickness) / 2.0;

    gdouble value = self->value;
    gdouble min_value = self->min_value;
    gdouble max_value = self->max_value;

    if (value > max_value)
    {
        value = max_value;
    }

    if (value < min_value)
    {
        value = min_value;
    }

    int len = snprintf(NULL, 0, "%.0f", value);
    char *val = (char *)malloc(sizeof(char) * len);
    sprintf(val, "%.0f", value);
    char *p = strstr(val, ".0");
    if (p)
        *p = 0x0;

    double sy_word = 16.0 * size / 300.0;

    // draw track
    {
        cairo_t *ctx_track = gtk_snapshot_append_cairo(snapshot, &GRAPHENE_RECT_INIT(0, 0, size, size));
        cairo_arc(ctx_track, size / 2.0, size / 2.0, ro, 2.0 * G_PI / 3.0, 0.0);
        cairo_set_source_rgba(ctx_track, gihex_color_get_red(&self->color_track),
                              gihex_color_get_green(&self->color_track),
                              gihex_color_get_blue(&self->color_track),
                              gihex_color_get_alpha(&self->color_track));
        cairo_set_line_width(ctx_track, thickness);
        cairo_set_line_cap(ctx_track, CAIRO_LINE_CAP_ROUND);
        cairo_stroke(ctx_track);
    }

    // draw bar
    {
        cairo_t *ctx = gtk_snapshot_append_cairo(snapshot, &GRAPHENE_RECT_INIT(0, 0, size, size));
        cairo_arc(ctx, size / 2.0,
                  size / 2.0,
                  ro,
                  2.0 * G_PI / 3.0,
                  ((240.0 * (value - min_value) / (max_value - min_value)) + 120.0) * G_PI / 180.0);

        cairo_set_source_rgba(ctx, gihex_color_get_red(&self->color_bar),
                              gihex_color_get_green(&self->color_bar),
                              gihex_color_get_blue(&self->color_bar),
                              gihex_color_get_alpha(&self->color_bar));
        cairo_set_line_width(ctx, thickness);
        cairo_set_line_cap(ctx, CAIRO_LINE_CAP_ROUND);
        cairo_stroke(ctx);
    }

    // draw indicator
    {
        cairo_t *ctx = gtk_snapshot_append_cairo(snapshot, &GRAPHENE_RECT_INIT(0, 0, size, size));
        cairo_translate(ctx, size / 2.0, size / 2.0);
        cairo_rotate(ctx, ((240.0 * (value - min_value) / (max_value - min_value)) + 120.0) * G_PI / 180.0);
        cairo_translate(ctx, -size / 2.0, -size / 2.0);
        cairo_move_to(ctx, size, size / 2.0);
        cairo_line_to(ctx, size - (indicator_side * cos(30 * G_PI / 180.0)), size / 2.0 + (indicator_side / 2.0));
        cairo_line_to(ctx, size - (indicator_side * cos(30 * G_PI / 180.0)), size / 2.0 - (indicator_side / 2.0));
        cairo_close_path(ctx);

        cairo_set_source_rgba(ctx, gihex_color_get_red(&self->color_indicator),
                              gihex_color_get_green(&self->color_indicator),
                              gihex_color_get_blue(&self->color_indicator),
                              gihex_color_get_alpha(&self->color_indicator));
        cairo_fill(ctx);
    }

    // draw text

    {
        cairo_text_extents_t extent;

        cairo_t *ctx = gtk_snapshot_append_cairo(snapshot, &GRAPHENE_RECT_INIT(0, 0, size, size));
        cairo_set_font_size(ctx, self->value_font_size * size / 75);
        cairo_text_extents(ctx, val, &extent);
        cairo_move_to(ctx, (size) - (extent.width + extent.x_bearing),
                      (size / 2.0) + (((size / 2.0) - ((size / 2.0) * sin(120.0 * G_PI / 180.0))) / 2.0) + (indicator_side / 2.0) + extent.height);
        cairo_text_path(ctx, val);
        free(val);
        cairo_set_source_rgba(ctx, gihex_color_get_red(&self->color_text),
                              gihex_color_get_green(&self->color_text),
                              gihex_color_get_blue(&self->color_text),
                              gihex_color_get_alpha(&self->color_text));
        cairo_fill(ctx);
    }

    // draw name
    cairo_text_extents_t extent_name;

    {
        cairo_t *ctx = gtk_snapshot_append_cairo(snapshot, &GRAPHENE_RECT_INIT(0, 0, size, size));
        cairo_set_font_size(ctx, self->sub_font_size * size / 75);
        cairo_text_extents(ctx, self->name, &extent_name);
        cairo_move_to(ctx,
                      (size / 2) - ((extent_name.width / 2) + extent_name.x_bearing),
                      (size / 2) - (extent_name.height + extent_name.y_bearing));
        cairo_text_path(ctx, self->name);
        cairo_set_source_rgba(ctx, gihex_color_get_red(&self->color_text),
                              gihex_color_get_green(&self->color_text),
                              gihex_color_get_blue(&self->color_text),
                              gihex_color_get_alpha(&self->color_text));
        cairo_fill(ctx);
    }

    // draw unit
    {
        cairo_t *ctx = gtk_snapshot_append_cairo(snapshot, &GRAPHENE_RECT_INIT(0, 0, size, size));
        cairo_text_extents_t extent_unit;
        cairo_set_font_size(ctx, self->sub_font_size * size / 75);
        cairo_text_extents(ctx, self->unit, &extent_unit);
        cairo_move_to(ctx,
                      (size / 2) - ((extent_unit.width / 2) + extent_unit.x_bearing),
                      (size / 2) - sy_word - extent_name.height - ((extent_unit.height) + extent_unit.y_bearing));
        cairo_text_path(ctx, self->unit);
        cairo_set_source_rgba(ctx, gihex_color_get_red(&self->color_text),
                              gihex_color_get_green(&self->color_text),
                              gihex_color_get_blue(&self->color_text),
                              gihex_color_get_alpha(&self->color_text));
        cairo_fill(ctx);
    }
}

void gihex_arc_bar_measure(GtkWidget *widget,
                           GtkOrientation orientation,
                           int for_size,
                           int *minimum,
                           int *natural,
                           int *minimum_baseline,
                           int *natural_baseline)
{
    *minimum = 150;
    *natural = 300;
    *minimum_baseline = -1;
    *natural_baseline = -1;
}

/*Public API */

GtkWidget *gihex_arc_bar_new(void)
{
    return g_object_new(GIHEX_TYPE_ARC_BAR, NULL);
}

void gihex_arc_bar_set_value(GihexArcBar *self, gdouble value)
{
    g_return_if_fail(GIHEX_IS_ARC_BAR(self));
    self->value = value;
    gtk_widget_queue_draw(GTK_WIDGET(self));
}

gdouble gihex_arc_bar_get_value(GihexArcBar *self)
{
    return self->value;
}

void gihex_arc_bar_set_min_value(GihexArcBar *self, gdouble min_value)
{
    g_return_if_fail(GIHEX_IS_ARC_BAR(self));
    self->min_value = min_value;
    gtk_widget_queue_draw(GTK_WIDGET(self));
}

double gihex_arc_bar_get_min_value(GihexArcBar *self)
{
    return self->min_value;
}

void gihex_arc_bar_set_max_value(GihexArcBar *self, gdouble max_value)
{
    g_return_if_fail(GIHEX_IS_ARC_BAR(self));
    self->max_value = max_value;
    gtk_widget_queue_draw(GTK_WIDGET(self));
}

double gihex_arc_bar_get_max_value(GihexArcBar *self)
{
    return self->max_value;
}

void gihex_arc_bar_set_color_track(GihexArcBar *self, GihexColor color)
{
    g_return_if_fail(GIHEX_IS_ARC_BAR(self));
    self->color_track = color;
    gtk_widget_queue_draw(GTK_WIDGET(self));
}
void gihex_arc_bar_set_color_indicator(GihexArcBar *self, GihexColor color)
{
    g_return_if_fail(GIHEX_IS_ARC_BAR(self));
    self->color_indicator = color;
    gtk_widget_queue_draw(GTK_WIDGET(self));
}
void gihex_arc_bar_set_color_bar(GihexArcBar *self, GihexColor color)
{
    g_return_if_fail(GIHEX_IS_ARC_BAR(self));
    self->color_bar = color;
    gtk_widget_queue_draw(GTK_WIDGET(self));
}

void gihex_arc_bar_set_font_size_value(GihexArcBar *self, gdouble size)
{
    g_return_if_fail(GIHEX_IS_ARC_BAR(self));
    self->value_font_size = size;
    gtk_widget_queue_draw(GTK_WIDGET(self));
}

void gihex_arc_bar_set_sub_font_size(GihexArcBar *self, gdouble size)
{
    g_return_if_fail(GIHEX_IS_ARC_BAR(self));
    self->sub_font_size = size;
    gtk_widget_queue_draw(GTK_WIDGET(self));
}

void gihex_arc_bar_set_color_text(GihexArcBar *self, GihexColor color)
{
    g_return_if_fail(GIHEX_IS_ARC_BAR(self));
    self->color_text = color;
    gtk_widget_queue_draw(GTK_WIDGET(self));
}

void gihex_arc_bar_set_unit(GihexArcBar *self, const char *unit)
{
    g_return_if_fail(GIHEX_IS_ARC_BAR(self));
    if (g_strcmp0(self->unit, unit) == 0)
        return;
    g_free(self->unit);
    self->unit = g_strdup(unit);
    gtk_widget_queue_draw(GTK_WIDGET(self));
}

void gihex_arc_bar_set_name(GihexArcBar *self, const char *name)
{
    g_return_if_fail(GIHEX_IS_ARC_BAR(self));

    if (g_strcmp0(self->name, name) == 0)
        return;
    g_free(self->name);
    self->name = g_strdup(name);
    gtk_widget_queue_draw(GTK_WIDGET(self));
}

void gihex_arc_bar_set_thickness(GihexArcBar *self, double value)
{
    g_return_if_fail(GIHEX_IS_ARC_BAR(self));

    self->thickness = value;
    gtk_widget_queue_draw(GTK_WIDGET(self));
}

void gihex_arc_bar_set_indicator_size(GihexArcBar *self, double size)
{
    g_return_if_fail(GIHEX_IS_ARC_BAR(self));

    self->indicator_size = size;
    gtk_widget_queue_draw(GTK_WIDGET(self));
}
