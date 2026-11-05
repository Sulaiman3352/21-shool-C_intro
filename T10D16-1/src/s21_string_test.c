#include <stdio.h>
#include <stdlib.h>
#include "./21_string.h"

int main() {
    double *data;
    int n;
    scanf("%d", &n);
    data = (double *)malloc(n * sizeof(double));

    s21_strlen();

    void s21_strlen_test() {}

    free(data);
    return 0;
}