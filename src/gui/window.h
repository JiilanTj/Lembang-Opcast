#ifndef WINDOW_H
#define WINDOW_H

#include "../../include/lembang_opcast.h"

typedef struct {
    GtkWidget *window;
    GtkWidget *start_button;
    GtkWidget *stop_button;
    GtkWidget *settings_button;
    GtkWidget *status_label;
} MainWindow;

// Initialize main window
LembangStatus window_init(MainWindow *window);

// Update window status
void window_update_status(MainWindow *window, const char *status);

// Clean up resources
void window_cleanup(MainWindow *window);

#endif // WINDOW_H
