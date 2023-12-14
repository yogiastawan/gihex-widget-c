#include <gihex_circular_step_bar.h>

struct _GihexCircularStepBar
{
    GtkWidget parent_intance;

    gdouble value;
    gdouble min_value;
    gdouble max_value;

    gdouble value_font_size;

    gdouble sub_font_size;

    GihexColor color_step_track;
    GihexColor color_circle_outest;
    GihexColor color_step_bar;
    GihexColor color_text;
    GihexColor background;

    uint8_t numb_step;
    double step_space;
    int8_t current_index;
    bool indeterminate;

    char *name;
    char *unit;
};

enum
{
    PROP_VALUE = 1,
    PROP_MIN_VALUE,
    PROP_MAX_VALUE,
    PROP_COLOR_STEP_TRACK,
    PROP_COLOR_CIRCLE_OUTEST,
    PROP_COLOR_STEP_BAR,
    PROP_FONT_SIZE_VALUE,
    PROP_SUB_FONT_SIZE,
    PROP_TEXT_COLOR,
    PROP_UNIT,
    PROP_NAME,
    PROP_NUMB_STEP,
    PROP_SPACE_STEP,
    PROP_INDETERMINATE,
    NUM_PROP
};

static GParamSpec *gauge_props[NUM_PROP] = {
    NULL,
};

G_DEFINE_TYPE(GihexCircularStepBar, gihex_circular_step_bar, GTK_TYPE_WIDGET);

static void gihex_circular_step_bar_set_property(GObject *object, guint property_id, const GValue *value, GParamSpec *pspec);
static void gihex_circular_step_bar_get_property(GObject *object, guint prop_id, GValue *value, GParamSpec *pspec);
static void gihex_circular_step_bar_dispose(GObject *object);
static void gihex_circular_step_bar_finalize(GObject *object);

static void gihex_circular_step_bar_measure(GtkWidget *widget,
                                            GtkOrientation orientation,
                                            int for_size,
                                            int *minimum,
                                            int *natural,
                                            int *minimum_baseline,
                                            int *natural_baseline);
static void gihex_circular_step_bar_snapshot(GtkWidget *widget, GtkSnapshot *snapshot);

static void gihex_circular_step_bar_init(GihexCircularStepBar *self)
{
    self->value = 30.0;
    self->min_value = 0.0;
    self->max_value = 100.0;
    self->color_step_track = gihex_color_new(181, 211, 211, 255);
    self->color_circle_outest = gihex_color_new(15, 160, 151, 255);
    self->color_step_bar = gihex_color_new(15, 160, 151, 255);
    self->color_text = gihex_color_new(15, 160, 151, 255);
    self->background = gihex_color_new(0, 51, 51, 255);
    self->numb_step = 20;
    self->step_space = 4.0;
    self->indeterminate = false;
    self->current_index = 0;
    self->value_font_size = 12.0;
    self->sub_font_size = 6.0;
    self->unit = g_strdup("\%");
    self->name = g_strdup("Circular Bar");
}

static void gihex_circular_step_bar_class_init(GihexCircularStepBarClass *klass)
{
    GObjectClass *o_class = G_OBJECT_CLASS(klass);
    o_class->set_property = gihex_circular_step_bar_set_property;
    o_class->get_property = gihex_circular_step_bar_get_property;
    o_class->dispose = gihex_circular_step_bar_dispose;
    o_class->finalize = gihex_circular_step_bar_finalize;

    GtkWidgetClass *w_class = GTK_WIDGET_CLASS(klass);
    w_class->snapshot = gihex_circular_step_bar_snapshot;
    w_class->measure = gihex_circular_step_bar_measure;

    gauge_props[PROP_VALUE] = g_param_spec_double("value", "Value", "Value of GihexCircularStepBar",
                                                  -G_MINDOUBLE, G_MAXDOUBLE, 30.0,
                                                  G_PARAM_READWRITE | G_PARAM_EXPLICIT_NOTIFY);
    gauge_props[PROP_MIN_VALUE] = g_param_spec_double("min-value", "Minimum value", "Minimum value of GihexCircularStepBar",
                                                      -G_MINDOUBLE, G_MAXDOUBLE, 0.0,
                                                      G_PARAM_READWRITE | G_PARAM_EXPLICIT_NOTIFY);
    gauge_props[PROP_MAX_VALUE] = g_param_spec_double("max-value", "Maximum value", "Maximum value of GihexCircularStepBar",
                                                      -G_MINDOUBLE, G_MAXDOUBLE, 100.0,
                                                      G_PARAM_READWRITE | G_PARAM_EXPLICIT_NOTIFY);
    gauge_props[PROP_COLOR_STEP_TRACK] = g_param_spec_boxed("color-step-track", "Color track", "Color of the track. Arc background",
                                                            GDK_TYPE_RGBA,
                                                            G_PARAM_READWRITE | G_PARAM_EXPLICIT_NOTIFY);
    gauge_props[PROP_COLOR_CIRCLE_OUTEST] = g_param_spec_boxed("color-circle-outest", "Color stroke", "Color of the stroke. Arc stroke",
                                                               GDK_TYPE_RGBA,
                                                               G_PARAM_READWRITE | G_PARAM_EXPLICIT_NOTIFY);
    gauge_props[PROP_COLOR_STEP_BAR] = g_param_spec_boxed("color-step-bar", "Color bar", "Color of the bar. Arc progress color",
                                                          GDK_TYPE_RGBA,
                                                          G_PARAM_READWRITE | G_PARAM_EXPLICIT_NOTIFY);

    gauge_props[PROP_FONT_SIZE_VALUE] = g_param_spec_double("value-font-size", "Font size of value", "Font size of value text",
                                                            -G_MINDOUBLE, G_MAXDOUBLE, 12.0,
                                                            G_PARAM_READWRITE | G_PARAM_EXPLICIT_NOTIFY);

    gauge_props[PROP_SUB_FONT_SIZE] = g_param_spec_double("sub-font-size", "Font size of sub text", "Font size of sub text",
                                                          -G_MINDOUBLE, G_MAXDOUBLE, 4.0,
                                                          G_PARAM_READWRITE | G_PARAM_EXPLICIT_NOTIFY);
    gauge_props[PROP_TEXT_COLOR] = g_param_spec_boxed("color-text", "Color text", "Color of the text",
                                                      GDK_TYPE_RGBA,
                                                      G_PARAM_READWRITE | G_PARAM_EXPLICIT_NOTIFY);

    gauge_props[PROP_UNIT] = g_param_spec_string("unit", "Unit text", "Unit of gauge bar", "\%",
                                                 G_PARAM_READWRITE | G_PARAM_EXPLICIT_NOTIFY);
    gauge_props[PROP_NAME] = g_param_spec_string("name", "Name text", "Name of gauge bar", "Gauge Bar",
                                                 G_PARAM_READWRITE | G_PARAM_EXPLICIT_NOTIFY);

    gauge_props[PROP_NUMB_STEP] = g_param_spec_uchar("numb-step", "Number steps", "Number of steps",
                                                     2, 255, 20,
                                                     G_PARAM_READWRITE | G_PARAM_EXPLICIT_NOTIFY);

    gauge_props[PROP_SPACE_STEP] = g_param_spec_double("space-step", "Space step", "Space between steps",
                                                       -G_MINDOUBLE, G_MAXDOUBLE, 6.0,
                                                       G_PARAM_READWRITE | G_PARAM_EXPLICIT_NOTIFY);

    gauge_props[PROP_INDETERMINATE] = g_param_spec_boolean("indeterminate", "Indeterminate", "Indeterminate",
                                                           false,
                                                           G_PARAM_READWRITE | G_PARAM_EXPLICIT_NOTIFY);

    g_object_class_install_properties(o_class, NUM_PROP, gauge_props);
    gtk_widget_class_set_css_name(w_class, "gihex_circular_step_bar");
}

void gihex_circular_step_bar_set_property(GObject *object, guint property_id, const GValue *value, GParamSpec *pspec)
{
    GihexCircularStepBar *self = GIHEX_CIRCULAR_STEP_BAR(object);
    switch (property_id)
    {
    case PROP_VALUE:
        gihex_circular_step_bar_set_value(self, g_value_get_double(value));
        break;
    case PROP_MIN_VALUE:
        gihex_circular_step_bar_set_min_value(self, g_value_get_double(value));
        break;
    case PROP_MAX_VALUE:
        gihex_circular_step_bar_set_max_value(self, g_value_get_double(value));
        break;
    case PROP_COLOR_STEP_TRACK:
    {
        GdkRGBA *clr = (GdkRGBA *)g_value_get_boxed(value);
        gihex_circular_step_bar_set_color_step_track(self, gihex_color_new(clr->red * 255, clr->green * 255, clr->blue * 255, clr->alpha * 255));
        break;
    }
    case PROP_COLOR_CIRCLE_OUTEST:
    {
        GdkRGBA *clr1 = g_value_get_boxed(value);
        gihex_circular_step_bar_set_color_circle_outest(self, gihex_color_new(clr1->red * 255, clr1->green * 255, clr1->blue * 255, clr1->alpha * 255));
        break;
    }
    case PROP_COLOR_STEP_BAR:
    {
        GdkRGBA *clr2 = g_value_get_boxed(value);
        gihex_circular_step_bar_set_color_step_bar(self, gihex_color_new(clr2->red * 255, clr2->green * 255, clr2->blue * 255, clr2->alpha * 255));
        break;
    }
    case PROP_FONT_SIZE_VALUE:
        gihex_circular_step_bar_set_font_size_value(self, g_value_get_double(value));
        break;
    case PROP_SUB_FONT_SIZE:
        gihex_circular_step_bar_set_sub_font_size(self, g_value_get_double(value));
        break;
    case PROP_TEXT_COLOR:
    {
        GdkRGBA *clr2 = g_value_get_boxed(value);
        gihex_circular_step_bar_set_color_text(self, gihex_color_new(clr2->red * 255, clr2->green * 255, clr2->blue * 255, clr2->alpha * 255));
        break;
    }
    case PROP_UNIT:
        gihex_circular_step_bar_set_unit(self, g_value_get_string(value));
        break;
    case PROP_NAME:
        gihex_circular_step_bar_set_name(self, g_value_get_string(value));
        break;
    case PROP_NUMB_STEP:
        gihex_circular_step_bar_set_numb_step(self, g_value_get_uchar(value));
        break;
    case PROP_INDETERMINATE:
        gihex_circular_step_bar_set_indeterminate(self, g_value_get_boolean(value));
        break;
    case PROP_SPACE_STEP:
        gihex_circular_step_bar_set_step_space(self, g_value_get_double(value));
    default:
        G_OBJECT_WARN_INVALID_PROPERTY_ID(object, property_id, pspec);
        break;
    }
}

void gihex_circular_step_bar_get_property(GObject *object, guint prop_id, GValue *value, GParamSpec *pspec)
{

    GihexCircularStepBar *self = GIHEX_CIRCULAR_STEP_BAR(object);
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
    case PROP_COLOR_STEP_TRACK:
    {
        GdkRGBA a = {
            (float)self->color_step_track.r / 255.0,
            (float)self->color_step_track.g / 255.0,
            (float)self->color_step_track.b / 255.0,
            (float)self->color_step_track.a / 255.0};
        g_value_set_boxed(value, gdk_rgba_copy(&a));
        break;
    }
    case PROP_COLOR_CIRCLE_OUTEST:
    {
        GdkRGBA b = {
            (float)self->color_circle_outest.r / 255.0,
            (float)self->color_circle_outest.g / 255.0,
            (float)self->color_circle_outest.b / 255.0,
            (float)self->color_circle_outest.a / 255.0};
        g_value_set_boxed(value, gdk_rgba_copy(&b));
        break;
    }
    case PROP_COLOR_STEP_BAR:
    {
        GdkRGBA c = {
            (float)self->color_step_bar.r / 255.0,
            (float)self->color_step_bar.g / 255.0,
            (float)self->color_step_bar.b / 255.0,
            (float)self->color_step_bar.a / 255.0};
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
    case PROP_NUMB_STEP:
        g_value_set_uchar(value, self->numb_step);
        break;
    case PROP_INDETERMINATE:
        g_value_set_boolean(value, self->indeterminate);
        break;
    case PROP_SPACE_STEP:
        g_value_set_double(value, self->step_space);
        break;
    default:
        G_OBJECT_WARN_INVALID_PROPERTY_ID(object, prop_id, pspec);
        break;
    }
}

void gihex_circular_step_bar_dispose(GObject *object)
{
    GihexCircularStepBar *bar = GIHEX_CIRCULAR_STEP_BAR(object);

    G_OBJECT_CLASS(gihex_circular_step_bar_parent_class)->dispose(object);
}

void gihex_circular_step_bar_finalize(GObject *object)
{
    GihexCircularStepBar *bar = GIHEX_CIRCULAR_STEP_BAR(object);
    g_free(bar->name);
    g_free(bar->unit);
    G_OBJECT_CLASS(gihex_circular_step_bar_parent_class)
        ->finalize(object);
}

static void gihex_circular_step_bar_snapshot(GtkWidget *widget, GtkSnapshot *snapshot)
{
    GihexCircularStepBar *self = GIHEX_CIRCULAR_STEP_BAR(widget);

    gdouble w = (gdouble)gtk_widget_get_width(widget);
    gdouble h = (gdouble)gtk_widget_get_height(widget);

    gdouble size = w;

    if (w >= h)
    {
        size = h;
    }

    gdouble value = self->value;

    if (value > self->max_value)
    {
        value = self->max_value;
    }

    if (value < self->min_value)
    {
        value = self->min_value;
    }

    gdouble stroke_circle = 4.5 * size / 300.0;              // stroke thickness outest circle
    gdouble r_circle = (size - (stroke_circle * 2.0)) / 2.0; // outest circle radius
    gdouble s_o = 9.0 * size / 100.0;                        // space circle and step
    gdouble r_o_dash = (size - s_o) / 2.0;                   // radius outest step
    gdouble s_i = 120.0 * size / 300.0;                            // step thickness
    gdouble r_i_dash = (size - s_i) / 2.0;                   // radius inner step
    gdouble s_dash = self->step_space * size / 600.0;        // space between step
    gdouble s_angle = atan(s_dash / r_o_dash);               // space between step in radian

    int len = snprintf(NULL, 0, "%.1f", value);
    char *val = (char *)malloc(sizeof(char) * len);
    sprintf(val, "%.1f", value);
    char *p = strstr(val, ".0");
    if (p)
        *p = 0x0;
    gdouble sy_word = 16.0 * size / 300.0; // vertical space between text

    // draw background
    // gtk_snapshot_append_color(snapshot, {0, 0, 0, 0}, &GRAPHENE_RECT_INIT(0.0, 0.0, w, h));

    // draw outest circle
    {
        cairo_t *cr = gtk_snapshot_append_cairo(snapshot, &GRAPHENE_RECT_INIT(0.0, 0.0, w, h));
        cairo_arc(cr, size / 2.0, size / 2.0, r_circle, 0.0, 2.0 * G_PI);
        cairo_set_source_rgba(cr, gihex_color_get_red(&self->color_circle_outest),
                              gihex_color_get_green(&self->color_circle_outest),
                              gihex_color_get_blue(&self->color_circle_outest),
                              gihex_color_get_alpha(&self->color_circle_outest));
        cairo_set_line_width(cr, stroke_circle);
        cairo_stroke(cr);
    }

    // draw step
    {
        double id_val = (value / (self->max_value - self->min_value)) * self->numb_step;

        self->current_index = (int8_t)id_val - 1;

        double step_angle = 360.0 / self->numb_step;
        int16_t i = 0;

        cairo_t *cr = gtk_snapshot_append_cairo(snapshot, &GRAPHENE_RECT_INIT(0.0, 0.0, w, h));

        for (i = 0; i < self->numb_step; i++)
        {
            cairo_save(cr);

            cairo_arc(cr, size / 2.0,
                      size / 2.0,
                      r_o_dash,
                      ((((double)i * step_angle) - 90.0) * G_PI / 180.0) + s_angle,
                      (((((double)i + 1.0) * step_angle) - 90.0) * G_PI / 180.0) - s_angle);

            cairo_line_to(cr,
                          (size / 2.0) + (r_i_dash * cos((((((double)i + 1.0) * step_angle) - 90.0) * G_PI / 180.0) - s_angle)),
                          (size / 2.0) + (r_i_dash * sin((((((double)i + 1.0) * step_angle) - 90.0) * G_PI / 180.0) - s_angle)));

            cairo_arc_negative(cr, size / 2.0, size / 2.0,
                               r_i_dash,
                               (((((double)i + 1) * step_angle) - 90.0) * G_PI / 180.0) - s_angle,
                               ((((double)i * step_angle) - 90.0) * G_PI / 180.0) + s_angle);
            cairo_close_path(cr);

            if (i < self->current_index)
            {
                cairo_set_source_rgba(cr, gihex_color_get_red(&self->color_step_bar),
                                      gihex_color_get_green(&self->color_step_bar),
                                      gihex_color_get_blue(&self->color_step_bar),
                                      gihex_color_get_alpha(&self->color_step_bar));
            }
            else
            {
                cairo_set_source_rgba(cr, gihex_color_get_red(&self->color_step_track),
                                      gihex_color_get_green(&self->color_step_track),
                                      gihex_color_get_blue(&self->color_step_track),
                                      gihex_color_get_alpha(&self->color_step_track));
            }

            cairo_fill(cr);

            cairo_restore(cr);
        }
    }

    // draw text
    cairo_text_extents_t extent;

    {
        cairo_t *ctx = gtk_snapshot_append_cairo(snapshot, &GRAPHENE_RECT_INIT(0, 0, size, size));
        cairo_set_font_size(ctx, self->value_font_size * size / 75);
        cairo_text_extents(ctx, val, &extent);
        cairo_move_to(ctx, (size / 2) - ((extent.width / 2) + extent.x_bearing), (size / 2) - ((extent.height / 2) + extent.y_bearing));
        cairo_text_path(ctx, val);
        free(val);
        cairo_set_source_rgba(ctx, gihex_color_get_red(&self->color_text),
                              gihex_color_get_green(&self->color_text),
                              gihex_color_get_blue(&self->color_text),
                              gihex_color_get_alpha(&self->color_text));
        cairo_fill(ctx);
    }

    // draw unit
    {
        cairo_t *ctx = gtk_snapshot_append_cairo(snapshot, &GRAPHENE_RECT_INIT(0, 0, size, size));
        cairo_text_extents_t extent_name;
        cairo_set_font_size(ctx, self->sub_font_size * size / 75);
        cairo_text_extents(ctx, self->name, &extent_name);
        cairo_move_to(ctx,
                      (size / 2) - ((extent_name.width / 2) + extent_name.x_bearing),
                      (size / 2) - sy_word + ((extent.height / 2) + extent.y_bearing));
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
                      (size / 2) + sy_word + extent_unit.height - ((extent.height / 2) + extent.y_bearing));
        cairo_text_path(ctx, self->unit);
        cairo_set_source_rgba(ctx, gihex_color_get_red(&self->color_text),
                              gihex_color_get_green(&self->color_text),
                              gihex_color_get_blue(&self->color_text),
                              gihex_color_get_alpha(&self->color_text));
        cairo_fill(ctx);
    }
}

void gihex_circular_step_bar_measure(GtkWidget *widget,
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

GtkWidget *gihex_circular_step_bar_new(void)
{
    return g_object_new(GIHEX_TYPE_CIRCULAR_STEP_BAR, NULL);
}

void gihex_circular_step_bar_set_value(GihexCircularStepBar *self, gdouble value)
{
    g_return_if_fail(GIHEX_IS_CIRCULAR_STEP_BAR(self));
    self->value = value;
    gtk_widget_queue_draw(GTK_WIDGET(self));
}

gdouble gihex_circular_step_bar_get_value(GihexCircularStepBar *self)
{
    return self->value;
}

void gihex_circular_step_bar_set_min_value(GihexCircularStepBar *self, gdouble min_value)
{
    g_return_if_fail(GIHEX_IS_CIRCULAR_STEP_BAR(self));
    self->min_value = min_value;
    gtk_widget_queue_draw(GTK_WIDGET(self));
}

double gihex_circular_step_bar_get_min_value(GihexCircularStepBar *self)
{
    return self->min_value;
}

void gihex_circular_step_bar_set_max_value(GihexCircularStepBar *self, gdouble max_value)
{
    g_return_if_fail(GIHEX_IS_CIRCULAR_STEP_BAR(self));
    self->max_value = max_value;
    gtk_widget_queue_draw(GTK_WIDGET(self));
}

double gihex_circular_step_bar_get_max_value(GihexCircularStepBar *self)
{
    return self->max_value;
}

void gihex_circular_step_bar_set_color_step_track(GihexCircularStepBar *self, GihexColor color)
{
    g_return_if_fail(GIHEX_IS_CIRCULAR_STEP_BAR(self));
    self->color_step_track = color;
    gtk_widget_queue_draw(GTK_WIDGET(self));
}
void gihex_circular_step_bar_set_color_circle_outest(GihexCircularStepBar *self, GihexColor color)
{
    g_return_if_fail(GIHEX_IS_CIRCULAR_STEP_BAR(self));
    self->color_circle_outest = color;
    gtk_widget_queue_draw(GTK_WIDGET(self));
}
void gihex_circular_step_bar_set_color_step_bar(GihexCircularStepBar *self, GihexColor color)
{
    g_return_if_fail(GIHEX_IS_CIRCULAR_STEP_BAR(self));
    self->color_step_bar = color;
    gtk_widget_queue_draw(GTK_WIDGET(self));
}

void gihex_circular_step_bar_set_font_size_value(GihexCircularStepBar *self, gdouble size)
{
    g_return_if_fail(GIHEX_IS_CIRCULAR_STEP_BAR(self));
    self->value_font_size = size;
    gtk_widget_queue_draw(GTK_WIDGET(self));
}

void gihex_circular_step_bar_set_sub_font_size(GihexCircularStepBar *self, gdouble size)
{
    g_return_if_fail(GIHEX_IS_CIRCULAR_STEP_BAR(self));
    self->sub_font_size = size;
    gtk_widget_queue_draw(GTK_WIDGET(self));
}

void gihex_circular_step_bar_set_color_text(GihexCircularStepBar *self, GihexColor color)
{
    g_return_if_fail(GIHEX_IS_CIRCULAR_STEP_BAR(self));
    self->color_text = color;
    gtk_widget_queue_draw(GTK_WIDGET(self));
}

void gihex_circular_step_bar_set_unit(GihexCircularStepBar *self, const char *unit)
{
    g_return_if_fail(GIHEX_IS_CIRCULAR_STEP_BAR(self));
    if (g_strcmp0(self->unit, unit) == 0)
        return;
    g_free(self->unit);
    self->unit = g_strdup(unit);
    gtk_widget_queue_draw(GTK_WIDGET(self));
}

void gihex_circular_step_bar_set_name(GihexCircularStepBar *self, const char *name)
{
    g_return_if_fail(GIHEX_IS_CIRCULAR_STEP_BAR(self));

    if (g_strcmp0(self->name, name) == 0)
        return;
    g_free(self->name);
    self->name = g_strdup(name);
    gtk_widget_queue_draw(GTK_WIDGET(self));
}

void gihex_circular_step_bar_set_numb_step(GihexCircularStepBar *self, uint8_t numb)
{
    g_return_if_fail(GIHEX_IS_CIRCULAR_STEP_BAR(self));
    self->numb_step = numb;
    gtk_widget_queue_draw(GTK_WIDGET(self));
}

void gihex_circular_step_bar_set_indeterminate(GihexCircularStepBar *self, bool state)
{
    g_return_if_fail(GIHEX_IS_CIRCULAR_STEP_BAR(self));
    self->indeterminate = state;
    gtk_widget_queue_draw(GTK_WIDGET(self));
}

void gihex_circular_step_bar_set_step_space(GihexCircularStepBar *self, double space)
{
    g_return_if_fail(GIHEX_IS_CIRCULAR_STEP_BAR(self));
    self->step_space = space;
    gtk_widget_queue_draw(GTK_WIDGET(self));
}
