#ifndef LOGGER_H
#define LOGGER_H

#include <stdio.h>

// Log level enumeration.
typedef enum { DEBUG, INFO, WARNING, ERROR } log_level;

// Initialize a log file with the given filename.
FILE* log_init(const char* filename);

// Write a message to the log file with a log level and timestamp.
// Message format: [LEVEL] [TIME] message
int logcat(FILE* log_file, const char* message, log_level level);

// Close the log file.
int log_close(FILE* log_file);

#endif  // LOGGER_H
