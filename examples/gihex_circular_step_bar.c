// Include gtk
#include <gtk/gtk.h>

#include <gihex_circular_step_bar.h>

static void on_activate(GtkApplication *app)
{
    // Create a new window
    GtkWidget *window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "Gihex Circular Step Bar");
    // Create a new box
    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 20);
    // Create new circular_step
    GtkWidget *circular_step = gihex_circular_step_bar_new();
    gtk_box_append(GTK_BOX(box), circular_step);
    gtk_window_set_child(GTK_WINDOW(window), box);
    gtk_window_present(GTK_WINDOW(window));
}

int main(int argc, char *argv[])
{
    // Create a new application
    GtkApplication *app = gtk_application_new("com.example.GtkApplication",
                                              G_APPLICATION_FLAGS_NONE);
    g_signal_connect(app, "activate", G_CALLBACK(on_activate), NULL);
    return g_application_run(G_APPLICATION(app), argc, argv);
}
