#ifndef SHARED_H
#define SHARED_H

#include <stdio.h>

int get_choice(int gap1, int gap2);
int show_tables();
int modules_control();
int levels_control();
int events_control();
void print_menu(const char *table_name);
void rebuild_modules_index(FILE *data_ptr);
void rebuild_events_index(FILE *data_ptr);
#endif
