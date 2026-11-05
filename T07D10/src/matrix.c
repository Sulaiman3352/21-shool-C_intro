#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

int readInput(int *mode, int *rows, int *cols);
int allocateMethod2(int ***matrix, int rows, int cols);
int allocateMethod3(int ***matrix, int rows, int cols);
int allocateMethod4(int ***matrix, int rows, int cols);

void freeMethod2(int **matrix, int rows);
void freeMethod3(int **matrix);
void freeMethod4(int **matrix);
void displayMatrix(int **matrix, int rows, int cols);

int main() {
    int mode = 0, rows = 0, cols = 0;
    int **matrix = NULL, staticMatrix[MAX_SIZE][MAX_SIZE];
    int shouldFree = 1;

    if (readInput(&mode, &rows, &cols)) {
        if (mode == 1) {
            int validInput = 1;
            for (int i = 0; i < rows; i++) {
                for (int j = 0; j < cols; j++) {
                    if (validInput && (scanf("%d", &staticMatrix[i][j])) != 1) {
                        printf("n/a");
                        validInput = 0;
                    }
                }
            }
            if (validInput) {
                for (int i = 0; i < rows; i++) {
                    for (int j = 0; j < cols; j++) {
                        if (j != cols - 1)
                            printf("%d ", staticMatrix[i][j]);
                        else if (i == rows - 1)
                            printf("%d", staticMatrix[i][j]);
                        else
                            printf("%d\n", staticMatrix[i][j]);
                    }
                }
            }
            shouldFree = 0;
        }
        if (mode == 2) {
            if (allocateMethod2(&matrix, rows, cols)) {
                displayMatrix(matrix, rows, cols);
            } else {
                freeMethod2(matrix, rows);
                shouldFree = 0;
            }
        }
        if (mode == 3) {
            if (allocateMethod3(&matrix, rows, cols)) {
                displayMatrix(matrix, rows, cols);
            } else {
                freeMethod3(matrix);
                shouldFree = 0;
            }
        }
        if (mode == 4) {
            if (allocateMethod4(&matrix, rows, cols)) {
                displayMatrix(matrix, rows, cols);
            } else {
                freeMethod4(matrix);
                shouldFree = 0;
            }
        }
    } else {
        shouldFree = 0;
    }
    if (shouldFree) {
        if (mode == 2) freeMethod2(matrix, rows);
        if (mode == 3) freeMethod3(matrix);
        if (mode == 4) freeMethod4(matrix);
    }
    return 0;
}

int readInput(int *mode, int *rows, int *cols) {
    int valid = 1;
    if (scanf("%d %d %d", mode, rows, cols) != 3 || *mode < 1 || *mode > 4 || *rows <= 0 || *cols <= 0) {
        printf("n/a");
        valid = 0;
    }
    return valid;
}

int allocateMethod2(int ***matrix, int rows, int cols) {
    int valid = 1;
    *matrix = malloc(rows * sizeof(int *));
    for (int i = 0; i < rows; i++) {
        (*matrix)[i] = malloc(cols * sizeof(int));
    }
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (valid && scanf("%d", &((*matrix)[i][j])) != 1) {
                printf("n/a");
                valid = 0;
            }
        }
    }
    return valid;
}

int allocateMethod3(int ***matrix, int rows, int cols) {
    int valid = 1;
    *matrix = malloc(rows * cols * sizeof(int) + rows * sizeof(int *));
    int *ptr = (int *)(*matrix + rows);
    for (int i = 0; i < rows; i++) {
        (*matrix)[i] = ptr + cols * i;
    }
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (valid && scanf("%d", &((*matrix)[i][j])) != 1) {
                printf("n/a");
                valid = 0;
            }
        }
    }
    return valid;
}

int allocateMethod4(int ***matrix, int rows, int cols) {
    int valid = 1;
    *matrix = malloc(rows * sizeof(int *));
    int *valuesArray = malloc(rows * cols * sizeof(int));
    for (int i = 0; i < rows; i++) {
        (*matrix)[i] = (valuesArray + cols * i);
    }
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (valid && scanf("%d", &((*matrix)[i][j])) != 1) {
                printf("n/a");
                valid = 0;
            }
        }
    }
    return valid;
}

void freeMethod2(int **matrix, int rows) {
    for (int i = 0; i < rows; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

void freeMethod3(int **matrix) { free(matrix); }

void freeMethod4(int **matrix) {
    free(matrix[0]);
    free(matrix);
}

void displayMatrix(int **matrix, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (j != cols - 1)
                printf("%d ", matrix[i][j]);
            else if (i == rows - 1)
                printf("%d", matrix[i][j]);
            else
                printf("%d\n", matrix[i][j]);
        }
    }
}
