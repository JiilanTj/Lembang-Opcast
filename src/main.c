#include "../include/lembang_opcast.h"
#include "capture/screen_capture.h"
#include "gui/window.h"
#include "utils/logger.h"

int main(int argc, char *argv[]) {
    // Initialize GTK
    gtk_init(&argc, &argv);
    
    // Initialize logger
    log_init("lembang-opcast.log");
    log_message(LOG_INFO, "Application started");
    
    // Initialize screen capture
    ScreenCapture capture;
    if (screen_capture_init(&capture) != LEMBANG_SUCCESS) {
        log_message(LOG_ERROR, "Failed to initialize screen capture");
        return LEMBANG_ERROR_INIT;
    }
    
    // Initialize main window
    MainWindow window;
    if (window_init(&window) != LEMBANG_SUCCESS) {
        log_message(LOG_ERROR, "Failed to initialize main window");
        return LEMBANG_ERROR_INIT;
    }
    
    // Main application loop
    gtk_main();
    
    // Cleanup
    screen_capture_cleanup(&capture);
    window_cleanup(&window);
    log_message(LOG_INFO, "Application shutdown");
    log_cleanup();
    
    return LEMBANG_SUCCESS;
}
