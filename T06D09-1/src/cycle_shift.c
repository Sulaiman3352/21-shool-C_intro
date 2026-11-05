#include <stdio.h>

int input(int *buffer, int *n, int *sdvg);
void sdv(int *buffer, int *new_buffer, int n, int sdvg);
void output(int *a, int n);

int main() {
    int n = 10, data[n];
    int c = 0;
    if (input(data, &n, &c)) {
        int newData[n];
        sdv(data, newData, n, c);
        output(newData, n);
    }
    return 0;
}

void sdv(int *buffer, int *new_buffer, int n, int sdvg) {
    for (int i = 0; i < n; i++) {
        new_buffer[i] = buffer[(i + 10000000 * n + sdvg) % n];
    }
}

int input(int *buffer, int *size, int *sdvg) {
    int flag = 1;
    if (scanf("%d", size) != 1 || *size < 0 || *size > 10) {
        flag = 0;
        printf("n/a");
    }
    if (flag) {
        for (int i = 0; i < *size; i++) {
            if (flag && scanf("%d", buffer + i) != 1) {
                flag = 0;
                printf("n/a");
            }
        }
    }
    if (flag) {
        if (scanf("%d", sdvg) != 1) {
            flag = 0;
            printf("n/a");
        }
    }
    return flag;
}

void output(int *a, int n) {
    for (int *p = a; p < n + a; p++) {
        if (p + 1 == n + a)
            printf("%d", *p);
        else
            printf("%d ", *p);
    }
}
