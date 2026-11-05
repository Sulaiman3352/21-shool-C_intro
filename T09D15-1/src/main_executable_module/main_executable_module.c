#include <stdio.h>
#include <stdlib.h>

#ifdef USE_MACRO_IO
#include "../data_libs/data_io_macro.h"
#else
#include "../data_libs/data_io.h"
#endif

#include "../data_libs/data_stat.h"
#include "../data_module/data_process.h"
#include "../yet_another_decision_module/decision.h"

void swap(double *xp, double *yp) {
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}

void sort(double *data, int n) {
    int i, j;
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (data[j] > data[j + 1]) {
                swap(&data[j], &data[j + 1]);
            }
        }
    }
}

int main() {
    double *data;
    int n;

    printf("LOAD DATA...\n");
    scanf("%d", &n);
    data = (double *)malloc(n * sizeof(double));

// for Quest 4
#ifdef USE_MACRO_IO
    READ_ARRAY(int, arr, n);
    PRINT_ARRAY(int, arr, n);
#else
    input(data, n);
    output(data, n);
#endif

    printf("RAW DATA:\n\t");
    output(data, n);

    printf("\nNORMALIZED DATA:\n\t");
    normalization(data, n);
    output(data, n);

    printf("\nSORTED NORMALIZED DATA:\n\t");
    sort(data, n);
    output(data, n);

    printf("\nFINAL DECISION:\n\t");
    // make_decision(data, n);
    //...
    if (make_decision(data, n)) {
        printf("YES");
    } else {
        printf("NO");
    }
    for (int i = 0; i < n; i++) {
        printf(" %f", data[i]);
    }
    printf("\n");

    free(data);
    return 0;
}
