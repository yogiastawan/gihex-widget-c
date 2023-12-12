#include <gihex_gauge_bar.h>

struct _GihexGaugeBar
{
    GtkWidget parent_intance;

    gdouble value;
    gdouble min_value;
    gdouble max_value;

    gdouble font_size_value;

    GihexColor color_track;
    GihexColor color_stroke;
    GihexColor color_bar;
};

enum
{
    PROP_VALUE = 1,
    PROP_MIN_VALUE,
    PROP_MAX_VALUE,
    PROP_COLOR_TRACK,
    PROP_COLOR_STROKE,
    PROP_COLOR_BAR,
    PROP_FONT_SIZE_VALUE,
    NUM_PROP
};

static GParamSpec *gauge_props[NUM_PROP] = {
    NULL,
};

G_DEFINE_TYPE(GihexGaugeBar, gihex_gauge_bar, GTK_TYPE_WIDGET);

static void gihex_gauge_bar_set_property(GObject *object, guint property_id, const GValue *value, GParamSpec *pspec);
static void gihex_gauge_bar_get_property(GObject *object, guint prop_id, GValue *value, GParamSpec *pspec);
static void gihex_gauge_bar_dispose(GObject *object);
static void gihex_gauge_bar_finalize(GObject *object);

static void gihex_gauge_bar_measure(GtkWidget *widget,
                                    GtkOrientation orientation,
                                    int for_size,
                                    int *minimum,
                                    int *natural,
                                    int *minimum_baseline,
                                    int *natural_baseline);
static void gihex_gauge_bar_snapshot(GtkWidget *widget, GtkSnapshot *snapshot);

static void gihex_gauge_bar_init(GihexGaugeBar *self)
{
    self->value = 30.0;
    self->min_value = 0.0;
    self->max_value = 100.0;
    self->color_track = gihex_color_new(42, 56, 53, 255);
    self->color_stroke = gihex_color_new(42, 56, 53, 255);
    self->color_bar = gihex_color_new(0, 168, 174, 255);
    self->font_size_value = 12.0;
}

static void gihex_gauge_bar_class_init(GihexGaugeBarClass *klass)
{
    GObjectClass *o_class = G_OBJECT_CLASS(klass);
    o_class->set_property = gihex_gauge_bar_set_property;
    o_class->get_property = gihex_gauge_bar_get_property;
    o_class->dispose = gihex_gauge_bar_dispose;
    o_class->finalize = gihex_gauge_bar_finalize;

    GtkWidgetClass *w_class = GTK_WIDGET_CLASS(klass);
    w_class->snapshot = gihex_gauge_bar_snapshot;
    w_class->measure = gihex_gauge_bar_measure;

    gauge_props[PROP_VALUE] = g_param_spec_double("value", "Value", "Value of GihexGaugeBar",
                                                  -G_MINDOUBLE, G_MAXDOUBLE, 30.0,
                                                  G_PARAM_READWRITE | G_PARAM_EXPLICIT_NOTIFY);
    gauge_props[PROP_MIN_VALUE] = g_param_spec_double("min-value", "Minimum value", "Minimum value of GihexGaugeBar",
                                                      -G_MINDOUBLE, G_MAXDOUBLE, 0.0,
                                                      G_PARAM_READWRITE | G_PARAM_EXPLICIT_NOTIFY);
    gauge_props[PROP_MAX_VALUE] = g_param_spec_double("max-value", "Maximum value", "Maximum value of GihexGaugeBar",
                                                      -G_MINDOUBLE, G_MAXDOUBLE, 100.0,
                                                      G_PARAM_READWRITE | G_PARAM_EXPLICIT_NOTIFY);
    gauge_props[PROP_COLOR_TRACK] = g_param_spec_boxed("color-track", "Color track", "Color of the track. Arc background",
                                                       GDK_TYPE_RGBA,
                                                       G_PARAM_READWRITE | G_PARAM_EXPLICIT_NOTIFY);
    gauge_props[PROP_COLOR_STROKE] = g_param_spec_boxed("color-stroke", "Color stroke", "Color of the stroke. Arc stroke",
                                                        GDK_TYPE_RGBA,
                                                        G_PARAM_READWRITE | G_PARAM_EXPLICIT_NOTIFY);
    gauge_props[PROP_COLOR_BAR] = g_param_spec_boxed("color-bar", "Color bar", "Color of the bar. Arc progress color",
                                                     GDK_TYPE_RGBA,
                                                     G_PARAM_READWRITE | G_PARAM_EXPLICIT_NOTIFY);

    gauge_props[PROP_FONT_SIZE_VALUE] = g_param_spec_double("font-size-value", "Font size of value", "Font size of value text",
                                                            -G_MINDOUBLE, G_MAXDOUBLE, 12.0,
                                                            G_PARAM_READWRITE | G_PARAM_EXPLICIT_NOTIFY);

    g_object_class_install_properties(o_class, NUM_PROP, gauge_props);
    gtk_widget_class_set_css_name(w_class, "gihex_gauge_bar");
}

void gihex_gauge_bar_set_property(GObject *object, guint property_id, const GValue *value, GParamSpec *pspec)
{
    GihexGaugeBar *self = GIHEX_GAUGE_BAR(object);
    switch (property_id)
    {
    case PROP_VALUE:
        gihex_gauge_bar_set_value(self, g_value_get_double(value));
        break;
    case PROP_MIN_VALUE:
        gihex_gauge_bar_set_min_value(self, g_value_get_double(value));
        break;
    case PROP_MAX_VALUE:
        gihex_gauge_bar_set_max_value(self, g_value_get_double(value));
        break;
    case PROP_COLOR_TRACK:
    {
        GdkRGBA *clr = (GdkRGBA *)g_value_get_boxed(value);
        gihex_gauge_bar_set_color_track(self, gihex_color_new(clr->red * 255, clr->green * 255, clr->blue * 255, clr->alpha * 255));
        break;
    }
    case PROP_COLOR_STROKE:
    {
        GdkRGBA *clr1 = g_value_get_boxed(value);
        gihex_gauge_bar_set_color_stroke(self, gihex_color_new(clr1->red * 255, clr1->green * 255, clr1->blue * 255, clr1->alpha * 255));
        break;
    }
    case PROP_COLOR_BAR:
    {
        GdkRGBA *clr2 = g_value_get_boxed(value);
        gihex_gauge_bar_set_color_bar(self, gihex_color_new(clr2->red * 255, clr2->green * 255, clr2->blue * 255, clr2->alpha * 255));
        break;
    }
    case PROP_FONT_SIZE_VALUE:
        gihex_gauge_bar_set_font_size_value(self, g_value_get_double(value));
        break;
    default:
        G_OBJECT_WARN_INVALID_PROPERTY_ID(object, property_id, pspec);
        break;
    }
}

void gihex_gauge_bar_get_property(GObject *object, guint prop_id, GValue *value, GParamSpec *pspec)
{

    GihexGaugeBar *self = GIHEX_GAUGE_BAR(object);
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
    case PROP_COLOR_STROKE:
    {
        GdkRGBA b = {
            (float)self->color_stroke.r / 255.0,
            (float)self->color_stroke.g / 255.0,
            (float)self->color_stroke.b / 255.0,
            (float)self->color_stroke.a / 255.0};
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
        g_value_set_double(value, self->font_size_value);
        break;
    default:
        G_OBJECT_WARN_INVALID_PROPERTY_ID(object, prop_id, pspec);
        break;
    }
}

void gihex_gauge_bar_dispose(GObject *object)
{
    G_OBJECT_CLASS(gihex_gauge_bar_parent_class)->dispose(object);
}

void gihex_gauge_bar_finalize(GObject *object)
{
    G_OBJECT_CLASS(gihex_gauge_bar_parent_class)->finalize(object);
}

void gihex_gauge_bar_snapshot(GtkWidget *widget, GtkSnapshot *snapshot)
{
    GihexGaugeBar *self = GIHEX_GAUGE_BAR(widget);

    int w = gtk_widget_get_width(widget);
    int h = gtk_widget_get_height(widget);
    gdouble size = (gdouble)w;
    if (w > h)
    {
        size = (gdouble)h;
    }

    gdouble ro = ((gdouble)size - 2.0) / 2.0;
    gdouble ri = ((gdouble)size - 2.0) / 3.0;

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

    int len = snprintf(NULL, 0, "%.1f", value);
    char *val = (char *)malloc(sizeof(char) * len);
    sprintf(val, "%.1f", value);

    // draw track
    cairo_t *ctx = gtk_snapshot_append_cairo(snapshot, &GRAPHENE_RECT_INIT(0, 0, size, size));
    cairo_arc(ctx, size / 2.0, size / 2.0, ro, 2.0 * G_PI / 3.0, G_PI / 3.0);
    cairo_arc(ctx,
              (size / 2.0) - (((ro + ri) / 2.0) * (sin(11.0 * G_PI / 6.0))),
              (size / 2.0) + (((ro + ri) / 2.0) * (cos(11.0 * G_PI / 6.0))),
              (ro - ri) / 2.0,
              G_PI / 3.0,
              4.0 * G_PI / 3.0);
    cairo_arc_negative(ctx, size / 2.0, size / 2.0, ri, G_PI / 3.0, 2.0 * G_PI / 3.0);
    cairo_arc(ctx,
              (size / 2.0) - (((ro + ri) / 2.0) * (sin(G_PI / 6.0))),
              (size / 2.0) + (((ro + ri) / 2.0) * (cos(G_PI / 6.0))),
              (ro - ri) / 2.0,
              5 * G_PI / 3.0,
              2.0 * G_PI / 3.0);
    cairo_close_path(ctx);
    cairo_set_source_rgba(ctx,
                          gihex_color_get_red(&self->color_track),
                          gihex_color_get_green(&self->color_track),
                          gihex_color_get_blue(&self->color_track),
                          gihex_color_get_alpha(&self->color_track));
    cairo_fill_preserve(ctx);
    cairo_set_source_rgba(ctx, gihex_color_get_red(&self->color_stroke),
                          gihex_color_get_green(&self->color_stroke),
                          gihex_color_get_blue(&self->color_stroke),
                          gihex_color_get_alpha(&self->color_stroke));
    cairo_stroke(ctx);
    cairo_set_line_width(ctx, 1.0);

    // draw bar
    cairo_t *ctx2 = gtk_snapshot_append_cairo(snapshot, &GRAPHENE_RECT_INIT(0, 0, size, size));
    cairo_arc(ctx2, size / 2.0,
              size / 2.0,
              ro - 2.0,
              2.0 * G_PI / 3.0,
              ((300.0 * (value - min_value) / (max_value - min_value)) + 120.0) * G_PI / 180.0);
    cairo_arc(ctx2,
              (size / 2.0) - (((ro + ri) / 2.0) * sin(((300.0 * (value - min_value) / (max_value - min_value)) + 30.0) * G_PI / 180.0)),
              (size / 2.0) + (((ro + ri) / 2.0) * cos(((300.0 * (value - min_value) / (max_value - min_value)) + 30.0) * G_PI / 180.0)),
              (ro - ri - 4.0) / 2.0,
              (120.0 + (300.0 * (value - min_value) / (max_value - min_value))) * G_PI / 180.0,
              (300.0 * (1.0 + ((value - min_value) / (max_value - min_value)))) * G_PI / 180.0);
    cairo_arc_negative(ctx2,
                       size / 2.0,
                       size / 2.0,
                       ri + 2.0,
                       ((300.0 * (value - min_value) / (max_value - min_value)) + 120.0) * G_PI / 180.0,
                       2.0 * G_PI / 3.0);
    cairo_arc(ctx2,
              (size / 2.0) - (((ro + ri) / 2.0) * sin(G_PI / 6.0)),
              (size / 2.0) + (((ro + ri) / 2.0) * cos(G_PI / 6.0)),
              (ro - ri - 4.0) / 2.0,
              5.0 * G_PI / 3.0,
              2.0 * G_PI / 3.0);
    cairo_close_path(ctx2);
    cairo_set_source_rgba(ctx2, gihex_color_get_red(&self->color_bar),
                          gihex_color_get_green(&self->color_bar),
                          gihex_color_get_blue(&self->color_bar),
                          gihex_color_get_alpha(&self->color_bar));
    cairo_fill(ctx2);

    // draw text
    cairo_t *cr = gtk_snapshot_append_cairo(snapshot, &GRAPHENE_RECT_INIT(0, 0, size, size));
    cairo_text_extents_t extent;
    cairo_set_font_size(cr, self->font_size_value * size / 75);
    cairo_text_extents(cr, val, &extent);
    cairo_move_to(cr, (size / 2) - ((extent.width / 2) + extent.x_bearing), (size / 2) - ((extent.height / 2) + extent.y_bearing));
    cairo_text_path(cr, val);
    free(val);
    cairo_set_source_rgba(cr, gihex_color_get_red(&self->color_bar),
                          gihex_color_get_green(&self->color_bar),
                          gihex_color_get_blue(&self->color_bar),
                          gihex_color_get_alpha(&self->color_bar));
    cairo_fill(cr);
}

void gihex_gauge_bar_measure(GtkWidget *widget,
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

GtkWidget *gihex_gauge_bar_new(void)
{
    return g_object_new(GIHEX_TYPE_GAUGE_BAR, NULL);
}

void gihex_gauge_bar_set_value(GihexGaugeBar *self, gdouble value)
{
    g_return_if_fail(GIHEX_IS_GAUGE_BAR(self));
    self->value = value;
    gtk_widget_queue_draw(GTK_WIDGET(self));
}

void gihex_gauge_bar_set_min_value(GihexGaugeBar *self, gdouble min_value)
{
    g_return_if_fail(GIHEX_IS_GAUGE_BAR(self));
    self->min_value = min_value;
    gtk_widget_queue_draw(GTK_WIDGET(self));
}

void gihex_gauge_bar_set_max_value(GihexGaugeBar *self, gdouble max_value)
{
    g_return_if_fail(GIHEX_IS_GAUGE_BAR(self));
    self->max_value = max_value;
    gtk_widget_queue_draw(GTK_WIDGET(self));
}

void gihex_gauge_bar_set_color_track(GihexGaugeBar *self, GihexColor color)
{
    g_return_if_fail(GIHEX_IS_GAUGE_BAR(self));
    self->color_track = color;
    gtk_widget_queue_draw(GTK_WIDGET(self));
}
void gihex_gauge_bar_set_color_stroke(GihexGaugeBar *self, GihexColor color)
{
    g_return_if_fail(GIHEX_IS_GAUGE_BAR(self));
    self->color_stroke = color;
    gtk_widget_queue_draw(GTK_WIDGET(self));
}
void gihex_gauge_bar_set_color_bar(GihexGaugeBar *self, GihexColor color)
{
    g_return_if_fail(GIHEX_IS_GAUGE_BAR(self));
    self->color_bar = color;
    gtk_widget_queue_draw(GTK_WIDGET(self));
}

void gihex_gauge_bar_set_font_size_value(GihexGaugeBar *self, gdouble size)
{
    g_return_if_fail(GIHEX_IS_GAUGE_BAR(self));
    self->font_size_value = size;
    gtk_widget_queue_draw(GTK_WIDGET(self));
}
