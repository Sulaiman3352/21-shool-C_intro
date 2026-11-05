#include <stdio.h>
#include <stdlib.h>

#define MAX 100

void input_static(int arr[MAX][MAX], int r, int c);
void output(int arr[MAX][MAX], int r, int c);
int menu();
void input_dynamic(int** matrix, int r, int c);
void output_dynamic(int** matrix, int r, int c);
void freeMatrix(int** matrix, int rows, int method);

int main() {
    int r, c;
    int option = menu();
    scanf("%d %d", &r, &c);
    int arr[MAX][MAX];

    if (option == 1) {
        if (r <= MAX || c <= MAX) {
            input_static(arr, r, c);
            output(arr, r, c);
        } else {
            printf("n/a");
        }
    } else {
        printf("to be continued... ");
    }
    return 0;
}

int menu() {
    int flag = 0;
    int option;
    scanf("%d", &option);
    if (option == 1) {
        flag = 1;
    } else if (option == 2) {
        flag = 2;
    } else if (option == 3) {
        flag = 3;
    } else if (option == 4) {
        flag = 4;
    }
    return flag;
}

void input_static(int arr[MAX][MAX], int r, int c) {
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            scanf("%d", &arr[i][j]);
        }
    }
}

void output(int arr[MAX][MAX], int r, int c) {
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            if (!(j == c)) {
                printf("%d ", arr[i][j]);
            } else {
                printf("%d", arr[i][j]);
            }
        }
        printf("\n");
    }
}

// Free Allocated Memory
void freeMatrix(int** matrix, int rows, int method) {
    if (matrix) {
        if (method == 3) {
            for (int i = 0; i < rows; i++) {
                free(matrix[i]);
            }
        } else {
            free(matrix[0]);
        }
        free(matrix);
    }
}