#include "data_stat.h"

double max(double *data, int n) {
    double maxi = data[0];
    for (int i = 0; i < n; i++) {
        if (data[i] > maxi) {
            maxi = data[i];
        }
    }
    return maxi;
}

double min(double *data, int n) {
    double mini = data[0];
    for (int i = 0; i < n; i++) {
        if (data[i] < mini) {
            mini = data[i];
        }
    }
    return mini;
}

double mean(double *data, int n) {
    double sum = 0;
    for (int i = 0; i < n; i++) {
        sum += data[i];
    }
    return sum / n;
}

double mean2(double *a, int *n) {
    double sum = 0;
    for (int i = 0; i < *n; i++) {
        sum += (a[i] * a[i]);
    }
    return sum / *n;
}

double variance(double *data, int n) { return mean2(data, &n) - mean(data, n) * mean(data, n); }