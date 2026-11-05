#include "./print_module.h"

#include <stdio.h>
#include <time.h>

void print_char(char ch) { putchar(ch); }

void print_log(void (*print)(char), char* message) {
    time_t current_time;
    const struct tm* time_info;
    char timeString[9];

    time(&current_time);
    time_info = localtime(&current_time);
    strftime(timeString, sizeof(timeString), "%H:%M:%S", time_info);

    printf("[LOG] %s ", timeString);

    while (*message) {
        print(*message);
        message++;
    }
    putchar('\n');
}