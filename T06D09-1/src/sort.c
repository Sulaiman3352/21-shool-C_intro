#include <stdio.h>

#define NMAX 10

void swap(int *xp, int *yp) {
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}

int input(int *a, int n);
void bubbleSort(int *arr, int n);
int output(int *a, int n);

int main() {
    int arr[NMAX];
    int n = NMAX;
    if ((input(arr, n)) == 1) {
        bubbleSort(arr, n);
        output(arr, n);
    }
    return 0;
}

int input(int *a, int n) {
    int flag = 1;
    for (int i = 0; i < n; i++) {
        if (flag && (scanf("%d", &a[i])) != 1) {
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

int output(int *a, int n) {
    int k;
    for (int k = 0; k < n; k++) {
        printf("%d ", a[k]);
    }
    printf("\n");
    return k;
}