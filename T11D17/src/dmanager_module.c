#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "door_struct.h"

#define DOORS_COUNT 15
#define MAX_ID_SEED 10000

void swap(struct door* xp, struct door* yp) {
    struct door temp = *xp;
    *xp = *yp;
    *yp = temp;
}

void sort(struct door* data, int n) {
    int i, j;
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (data[j].id > data[j + 1].id) {
                swap(&data[j], &data[j + 1]);
            }
        }
    }
}

void output(const struct door* data, int n) {
    for (int k = 0; k < n; k++) {
        printf("%d, %d", data[k].id, data[k].status);
        printf("\n");
    }
}

void initialize_doors(struct door* doors);

int main() {
    struct door* doors = (struct door*)malloc(DOORS_COUNT * sizeof(double));

    initialize_doors(doors);
    for (int i = 0; i < DOORS_COUNT; i++) {
        doors[i].status = 0;
        doors[i].id = i;
    }
    sort(doors, DOORS_COUNT);
    output(doors, DOORS_COUNT);

    free(doors);
    return 0;
}

// Doors initialization function
// ATTENTION!!!
// DO NOT CHANGE!
void initialize_doors(struct door* doors) {
    srand(time(0));

    int seed = rand() % MAX_ID_SEED;
    for (int i = 0; i < DOORS_COUNT; i++) {
        doors[i].id = (i + seed) % DOORS_COUNT;
        doors[i].status = rand() % 2;
    }
}
