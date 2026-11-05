#ifndef MATERIALS_H
#define MATERIALS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#define modules_fpath "../materials/master_modules.db"
#define levels_fpath "../materials/master_levels.db"
#define events_fpath "../materials/master_status_events.db"

#define modules_idx "../materials/master_modules.idx"
#define levels_idx "../materials/master_levels.idx"
#define events_idx "../materials/master_status_events.idx"

typedef struct modules {
    int id;
    char name[30];
    int level;
    int cell;
    int flag;
} modules;

typedef struct levels {
    int level;
    int cells_num;
    int pr_flag;
} levels;

typedef struct events {
    int event_id;
    int module_id;
    int status;
    char date[11];
    char time[9];
} events;

typedef struct {
    int id;       // ID of the record
    long offset;  // Byte offset in the data file
} modules_index;

typedef struct {
    int level;  // Level number
    long offset;
} levels_index;

typedef struct {
    int event_id;  // Event ID
    long offset;
} events_index;

#endif
