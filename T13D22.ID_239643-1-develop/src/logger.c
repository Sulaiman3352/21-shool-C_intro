#include "./logger.h"

#include <string.h>
#include <time.h>

FILE *log_init(const char *filename) {
    FILE *log_file = fopen(filename, "a");
    return log_file;
}

int logcat(FILE *log_file, const char *message, log_level level) {
    if (!log_file || !message) {
        return -1;
    }

    // Get current time
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    if (!t) {
        return -1;
    }

    // Format time string
    char time_str[64];
    if (strftime(time_str, sizeof(time_str), "%Y-%m-%d %H:%M:%S", t) == 0) {
        return -1;
    }

    // Get level string
    const char *level_str = "";
    switch (level) {
        case DEBUG:
            level_str = "DEBUG";
            break;
        case INFO:
            level_str = "INFO";
            break;
        case WARNING:
            level_str = "WARNING";
            break;
        case ERROR:
            level_str = "ERROR";
            break;
        default:
            level_str = "INFO";
            break;
    }

    // Write the formatted message into the log file.
    int written = fprintf(log_file, "[%s] [%s] %s\n", level_str, time_str, message);
    fflush(log_file);
    return (written < 0) ? -1 : written;
}

int log_close(FILE *log_file) {
    if (!log_file) {
        return -1;
    }
    return fclose(log_file);
}
