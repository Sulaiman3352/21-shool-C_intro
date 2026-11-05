#include <stdio.h>
#include <stdlib.h>

#define N 100

int input(int *v, int *stroki, int *st);
// int input1(int ***pa, int s, int st);
int input_2(int ***pa, int s, int st);
int input_3(int ***pa, int s, int st);
int input_4(int ***pa, int s, int st);

void free2(int **pa, int s);
void free3(int **pa);
void free4(int **pa);
void output(int **pa, int s, int st);

void min(int **pa, int s, int st);
void max(int **pa, int s, int st);
void minS(int pa[N][N], int s, int st);
void maxS(int pa[N][N], int s, int st);

int main() {
    int v = 0, stroki = 0, st = 0;
    int **arr = NULL, arrS[N][N];
    int free = 1;

    if (input(&v, &stroki, &st)) {
        // printf("%d %d\n", stroki, st);
        if (v == 1) {
            int flag = 1;
            for (int i = 0; i < stroki; i++) {
                for (int j = 0; j < st; j++) {
                    if (flag && (scanf("%d", &arrS[i][j])) != 1) {
                        printf("n/a");
                        flag = 0;
                    }
                }
            }
            if (flag) {
                for (int i = 0; i < stroki; i++) {
                    for (int j = 0; j < st; j++) {
                        if (j != st - 1)
                            printf("%d ", arrS[i][j]);
                        else if (i == stroki - 1)
                            printf("%d", arrS[i][j]);
                        else
                            printf("%d\n", arrS[i][j]);
                    }
                }
            }
            free = 0;
        }
        if (v == 2) {
            if (input_2(&arr, stroki, st)) {
                output(arr, stroki, st);
                printf("\n");
                max(arr, stroki, st);
                min(arr, stroki, st);
            } else {
                free2(arr, stroki);
                free = 0;
                // Ошибка при вводе данных
            }
        }
        if (v == 3) {
            if (input_3(&arr, stroki, st)) {
                output(arr, stroki, st);
                printf("\n");
                max(arr, stroki, st);
                min(arr, stroki, st);
            } else {
                free3(arr);
                free = 0;
                // Ошибка при вводе данных
            }
        }
        if (v == 4) {
            if (input_4(&arr, stroki, st)) {
                output(arr, stroki, st);
                printf("\n");
                max(arr, stroki, st);
                min(arr, stroki, st);
            } else {
                free4(arr);
                free = 0;
                // Ошибка при вводе данных
            }
        }

    } else {
        free = 0;
    }
    if (free) {
        if (v == 2) free2(arr, stroki);
        if (v == 3) free3(arr);
        if (v == 4) free4(arr);
    }
    return 0;
}

int input(int *v, int *stroki, int *st) {
    int flag = 1;
    if (scanf("%d %d %d", v, stroki, st) != 3 || *v < 1 || *v > 4 || *stroki <= 0 || *st <= 0) {
        printf("n/a");
        flag = 0;
    }
    return flag;
}
// int input1(int ***pa, int s, int st){

//     return flag;
// }

int input_2(int ***pa, int s, int st) {
    int flag = 1;
    *pa = malloc(s * sizeof(int *));
    for (int i = 0; i < s; i++) {
        (*pa)[i] = malloc(st * sizeof(int));
    }
    for (int i = 0; i < s; i++) {
        for (int j = 0; j < st; j++) {
            if (flag && scanf("%d", &((*pa)[i][j])) != 1) {
                printf("n/a");
                flag = 0;
            }
        }
    }
    return flag;
}
int input_3(int ***pa, int s, int st) {
    int flag = 1;
    *pa = malloc(s * st * sizeof(int) + s * sizeof(int *));
    int *ptr = (int *)(*pa + s);
    for (int i = 0; i < s; i++) {
        (*pa)[i] = ptr + st * i;
    }
    for (int i = 0; i < s; i++) {
        for (int j = 0; j < st; j++) {
            if (flag && scanf("%d", &((*pa)[i][j])) != 1) {
                printf("n/a");
                flag = 0;
            }
        }
    }
    return flag;
}

int input_4(int ***pa, int s, int st) {
    int flag = 1;
    *pa = malloc(s * sizeof(int *));
    int *values_array = malloc(s * st * sizeof(int));
    for (int i = 0; i < s; i++) {
        (*pa)[i] = (values_array + st * i);
    }
    for (int i = 0; i < s; i++) {
        for (int j = 0; j < st; j++) {
            if (flag && scanf("%d", &((*pa)[i][j])) != 1) {
                printf("n/a");
                flag = 0;
            }
        }
    }
    return flag;
}

void free2(int **pa, int s) {
    for (int i = 0; i < s; i++) {
        free(pa[i]);
    }
    free(pa);
}

void free3(int **pa) { free(pa); }

void free4(int **pa) {
    free(pa[0]);
    free(pa);
}

void output(int **pa, int s, int st) {
    for (int i = 0; i < s; i++) {
        for (int j = 0; j < st; j++) {
            if (j != st - 1)
                printf("%d ", pa[i][j]);
            else if (i == s - 1)
                printf("%d", pa[i][j]);
            else
                printf("%d\n", pa[i][j]);
        }
    }
}

void max(int **pa, int s, int st) {
    for (int i = 0; i < s; i++) {
        int max = pa[i][0];
        for (int j = 0; j < st; j++) {
            if (pa[i][j] > max) max = pa[i][j];
        }
        if (i != s - 1)
            printf("%d ", max);
        else
            printf("%d\n", max);
    }
}

void min(int **pa, int s, int st) {
    for (int i = 0; i < s; i++) {
        int min = pa[0][i];
        for (int j = 0; j < st; j++) {
            if (pa[j][i] < min) min = pa[j][i];
        }
        if (i != s - 1)
            printf("%d ", min);
        else
            printf("%d", min);
    }
}

void minS(int pa[N][N], int s, int st) {
    for (int i = 0; i < s; i++) {
        int min = pa[0][i];
        for (int j = 0; j < st; j++) {
            if (pa[j][i] < min) min = pa[j][i];
        }
        if (i != s - 1)
            printf("%d ", min);
        else
            printf("%d", min);
    }
}
void maxS(int pa[N][N], int s, int st) {
    for (int i = 0; i < s; i++) {
        int min = pa[0][i];
        for (int j = 0; j < st; j++) {
            if (pa[j][i] < min) min = pa[j][i];
        }
        if (i != s - 1)
            printf("%d ", min);
        else
            printf("%d", min);
    }
}