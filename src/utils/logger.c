#include "logger.h"
#include <string.h>
#include <time.h>

static FILE *log_file = NULL;

void log_init(const char *filename) {
    log_file = fopen(filename, "a");
}

void log_message(LogLevel level, const char *message) {
    if (!log_file) {
        return;
    }

    time_t now;
    time(&now);
    char *date = ctime(&now);
    date[strlen(date) - 1] = '\0'; // Remove newline

    const char *level_str;
    switch (level) {
        case LOG_INFO:
            level_str = "INFO";
            break;
        case LOG_WARNING:
            level_str = "WARNING";
            break;
        case LOG_ERROR:
            level_str = "ERROR";
            break;
        default:
            level_str = "UNKNOWN";
    }

    fprintf(log_file, "[%s] %s: %s\n", date, level_str, message);
    fflush(log_file);
}

void log_cleanup(void) {
    if (log_file) {
        fclose(log_file);
    }
}
