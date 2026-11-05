#include <stdio.h>
#define NMAX 10

int input(int *a, int *n);
int output(int *a, int *n);
int squaring(int *a, int *n);

int main() {
    int n, data[NMAX];
    if (input(data, &n)) {
        squaring(data, &n);
        output(data, &n);
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

int output(int *a, int *n) {
    int k;
    for (k = 0; k < *n; k++) {
        printf("%d ", a[k]);
    }
    return k;
}

int squaring(int *a, int *n) {
    for (int j = 0; j < *n; j++) {
        a[j] *= a[j];
    }
    return 0;
}