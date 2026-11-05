#include <stdbool.h>
#include <stdio.h>

int input(int *arr, int *length);
int output(int *a, int n);
int sum_numbers(int *arr, int length);
int find_numbers(int *arr, int length, int *arr2);
void bubbleSort(int *arr, int n);

void swap(int *xp, int *yp) {
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}

int main() {
    int n;
    if (scanf("%d", &n) != 1) {
        printf("n/a");
        return 1;
    }

    int arr[n];
    int arr2[n];

    if (input(arr, &n) == 1) {
        int sum = sum_numbers(arr, n);
        printf("%d \n", sum);

        int c = find_numbers(arr, n, arr2);
        bubbleSort(arr2, c);
        output(arr2, c);
    }

    return 0;
}

int input(int *arr, int *length) {
    int flag = 1;
    for (int i = 0; i < *length; i++) {
        if (scanf("%d", &arr[i]) != 1) {
            printf("n/a");
            return 0;
        }
    }
    return flag;
}

int sum_numbers(int *arr, int length) {
    int sum = 0;
    for (int i = 0; i < length; i++) {
        if (arr[i] % 2 == 0) {
            sum += arr[i];
        }
    }
    return sum;
}

int find_numbers(int *arr, int length, int *arr2) {
    int count = 0;
    for (int i = 0; i < length; i++) {
        if (arr[i] % 2 == 0) {
            arr2[count] = arr[i];
            count++;
        }
    }
    return count;
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
    for (int k = 0; k < n; k++) {
        printf("%d ", a[k]);
    }
    return n;
}
