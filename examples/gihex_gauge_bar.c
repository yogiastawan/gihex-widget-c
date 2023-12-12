// Include gtk
#include <gtk/gtk.h>

#include <gihex_gauge_bar.h>

static void on_activate(GtkApplication *app)
{
    // Create a new window
    GtkWidget *window = gtk_application_window_new(app);
    // Create a new box
    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 20);
    // Create new gauge
    GtkWidget *gauge = gihex_gauge_bar_new();
    gtk_box_append(GTK_BOX(box), gauge);
    gtk_window_set_child(GTK_WINDOW(window), box);
    gtk_window_present(GTK_WINDOW(window));
}

int main(int argc, char *argv[])
{
    // Create a new application
    GtkApplication *app = gtk_application_new("com.example.GtkApplication",
                                              G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect(app, "activate", G_CALLBACK(on_activate), NULL);
    return g_application_run(G_APPLICATION(app), argc, argv);
}
