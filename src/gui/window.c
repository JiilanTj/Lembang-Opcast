#include "window.h"

static void on_start_clicked(GtkWidget *widget, gpointer data) {
    MainWindow *window = (MainWindow *)data;
    window_update_status(window, "Recording started...");
    gtk_widget_set_sensitive(window->start_button, FALSE);
    gtk_widget_set_sensitive(window->stop_button, TRUE);
}

static void on_stop_clicked(GtkWidget *widget, gpointer data) {
    MainWindow *window = (MainWindow *)data;
    window_update_status(window, "Recording stopped");
    gtk_widget_set_sensitive(window->start_button, TRUE);
    gtk_widget_set_sensitive(window->stop_button, FALSE);
}

LembangStatus window_init(MainWindow *window) {
    // Create main window
    window->window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window->window), "Lembang-Opcast");
    gtk_window_set_default_size(GTK_WINDOW(window->window), 400, 200);
    
    // Create container
    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_container_add(GTK_CONTAINER(window->window), box);
    
    // Create buttons
    window->start_button = gtk_button_new_with_label("Start Recording");
    window->stop_button = gtk_button_new_with_label("Stop Recording");
    window->settings_button = gtk_button_new_with_label("Settings");
    
    gtk_widget_set_sensitive(window->stop_button, FALSE);
    
    // Create status label
    window->status_label = gtk_label_new("Ready");
    
    // Add widgets to container
    gtk_box_pack_start(GTK_BOX(box), window->start_button, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(box), window->stop_button, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(box), window->settings_button, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(box), window->status_label, TRUE, TRUE, 0);
    
    // Connect signals
    g_signal_connect(window->start_button, "clicked", G_CALLBACK(on_start_clicked), window);
    g_signal_connect(window->stop_button, "clicked", G_CALLBACK(on_stop_clicked), window);
    g_signal_connect(window->window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    
    gtk_widget_show_all(window->window);
    
    return LEMBANG_SUCCESS;
}

void window_update_status(MainWindow *window, const char *status) {
    gtk_label_set_text(GTK_LABEL(window->status_label), status);
}

void window_cleanup(MainWindow *window) {
    gtk_widget_destroy(window->window);
}
