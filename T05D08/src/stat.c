#include <stdio.h>
#define NMAX 10

int input(int *a, int *n);
int output(int *a, int *n);
int max(int *a, int *n);
int min(int *a, int *n);
double mean(int *a, int *n);
double mean2(int *a, int *n);
double variance(int *a, int *n);

void output_result(int max_v, int min_v, double mean_v, double variance_v);

int main() {
    int n, data[NMAX];
    if (input(data, &n)) {
        output(data, &n);
        max(data, &n);
        min(data, &n);
        mean(data, &n);

        output_result(max(data, &n), min(data, &n), mean(data, &n), variance(data, &n));
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

int max(int *a, int *n) {
    int maxi = a[0];
    for (int i = 0; i < *n; i++) {
        if (a[i] > maxi) {
            maxi = a[i];
        }
    }
    return maxi;
}

int min(int *a, int *n) {
    int mini = a[0];
    for (int i = 0; i < *n; i++) {
        if (a[i] < mini) {
            mini = a[i];
        }
    }
    return mini;
}

int output(int *a, int *n) {
    int k;
    for (k = 0; k < *n; k++) {
        printf("%d ", a[k]);
    }
    return k;
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

void output_result(int max_v, int min_v, double mean_v, double variance_v) {
    printf("\n%d %d %.6lf %.6lf", max_v, min_v, mean_v, variance_v);
}
