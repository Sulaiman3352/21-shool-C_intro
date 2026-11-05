#include <stdbool.h>
#include <stdio.h>

#define NMAX 10

void swap(int *xp, int *yp) {
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}

void quickSort(int *arr, int low, int high);
int partition(int *arr, int low, int high);
int input(int *a, int *b, int n);
void bubbleSort(int *arr, int n);
int output(int *a, int n);

int main() {
    int arr[NMAX];
    int arr2[NMAX];
    int n = NMAX;
    if ((input(arr, arr2, n)) == 1) {
        bubbleSort(arr, n);
        output(arr, n);
        quickSort(arr2, 0, n - 1);
        output(arr2, n);
    }
    return 0;
}

int input(int *a, int *b, int n) {
    int flag = 1;
    for (int i = 0; i < n; i++) {
        if (flag && (scanf("%d", &a[i])) != 1) {
            printf("n/a");
            flag = 0;
        }
        b[i] = a[i];
    }
    return flag;
}

void bubbleSort(int arr[], int n) {
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
    for (int k = 0; k < n; k++) {
        printf("%d ", a[k]);
    }
    printf("\n");
    return n;
}

int partition(int *arr, int low, int high) {
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return i + 1;
}

void quickSort(int *arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}