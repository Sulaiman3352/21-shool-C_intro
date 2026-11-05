#include <stdio.h>
#include <stdlib.h>

#define NMAX 10

void swap(int *xp, int *yp) {
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}

int input(int *a, int *n);
void bubbleSort(int *arr, int n);
int output(int *a, int *n);

int main() {
    int *arr = malloc(sizeof *arr * NMAX);
    int n = NMAX;
    if ((input(arr, &n)) == 1) {
        bubbleSort(arr, n);
        output(arr, &n);
    }
    free(arr);
    return 0;
}

int input(int *arr, int *n) {
    int flag = 1;
    if ((scanf("%d", n)) != 1) {
        printf("n/a");
        flag = 0;
    }
    for (int i = 0; i < *n; i++) {
        if (scanf("%d", &arr[i]) != 1) {
            printf("n/a");
            flag = 0;
        }
    }
    return flag;
}

void bubbleSort(int *arr, int n) {
    int i, j;
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(&arr[j], &arr[j + 1]);
            }
        }
    }
}

int output(int *a, int *n) {
    for (int i = 0; i < *n; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");
    return 0;
}