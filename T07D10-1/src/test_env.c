#include <stdio.h>
#include <stdlib.h>

int main() {
    const int M = 4, N = 4;
    int count = 0;
    int** pointer_array = malloc(M * sizeof(int*));
    for (int i = 0; i < M; i++) pointer_array[i] = malloc(N * sizeof(int));

    for (int i = 0; i < M; i++)
        for (int j = 0; j < N; j++) pointer_array[i][j] = ++count;

    for (int i = 0; i < M; i++)
        for (int j = 0; j < N; j++) printf("%d", pointer_array[i][j]);

    for (int i = 0; i < M; i++) free(pointer_array[i]);

    free(pointer_array);
    return 0;
}