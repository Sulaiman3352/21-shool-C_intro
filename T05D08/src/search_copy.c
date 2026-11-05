#include <stdio.h>

#define MAX_SIZE 30

int input(int *a, int *n);
int findValues(int *arr, int size);
double mean(int *a, int *n);
double mean2(int *a, int *n);
double variance(int *a, int *n);
double sqrtApprox(double num);

int main() {
    int count, numbers[MAX_SIZE];

    if (input(numbers, &count)) {
        findValues(numbers, count);
    }

    return 0;
}

int input(int *a, int *n) {
    if ((scanf("%d", n)) != 1) {
        printf("n/a");
        return 0;
    }
    for (int i = 0; i < *n; i++) {
        int u;
        if (scanf("%d", &u) != 1) {
            printf("n/a");
            return 0;
        }
        a[i] = u;
    }
    return 1;
}

int findValues(int *arr, int size) {
    int found = 0;
    double meanValue = mean(arr, &size);
    double varianceValue = variance(arr, &size);
    double threshold = meanValue + 3 * sqrtApprox(varianceValue);

    for (int *ptr = arr; ptr < arr + size; ptr++) {
        if (*ptr >= meanValue && *ptr <= threshold && (*ptr % 2) == 0 && *ptr >= meanValue && *ptr <= (meanValue + 3) * sqrtApprox(varianceValue) ) {
            printf("%d ", *ptr);
            found = 1;
        }
    }
    if (!found) {
        printf("No matching values\n");
    }
    return found;
}


double mean(int *a, int *n) {
    double sum = 0;
    for (int i = 0; i < *n; i++) {
        sum += (double)a[i] / *n;
    }
    return sum;
}

double mean2(int *a, int *n) {
    double sum = 0;
    for (int i = 0; i < *n; i++) {
        sum += (double)(a[i] * a[i]) / *n;
    }
    return sum;
}

double variance(int *a, int *n) { return mean2(a, n) - mean(a, n) * mean(a, n); }

double sqrtApprox(double num) {
    double x = num, y = 1.0;
    double accuracy = 0.00001;

    while (x - y > accuracy) {
        x = (x + y) / 2;
        y = num / x;
    }

    return x;
}