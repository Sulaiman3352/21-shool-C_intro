#include "graph.h"
#include "stack.h"

void process();

int main() {
    process();
    return 0;
}

void process() {
    int length = 0;
    char* expression = getString(&length);
    // Выделяем память с запасом
    char* post_expr = malloc((2 * length + 1) * sizeof(char));
    if (!post_expr) {
        printf("n/a");
        free(expression);
        return;
    }
    int no_error = 1;
    post_expr = toPostfix(expression, post_expr, &no_error);

    if (strstr(expression, "x(")) {
        no_error = 0;
    }

    if (no_error) {
        double x_arr[SIZE_X];
        int i_arr[SIZE_X], j_arr[SIZE_X];
        fillX(x_arr);
        calcFunc(post_expr, x_arr, i_arr, j_arr);
        drawFunc(i_arr, j_arr);
    } else {
        printf("n/a");
    }
    free(expression);
    free(post_expr);
}