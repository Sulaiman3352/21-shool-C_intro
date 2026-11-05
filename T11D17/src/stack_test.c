#include "stack.h"

#include <stdio.h>

void test_push() {
    struct stack* s = init();
    if (!s) {
        printf("FAIL\n");
        return;
    }

    if (push(s, 10) == SUCCESS && push(s, 20) == SUCCESS) {
        printf("SUCCESS\n");
    } else {
        printf("FAIL\n");
    }

    destroy(s);
}

void test_pop() {
    struct stack* s = init();
    if (!s) {
        printf("FAIL\n");
        return;
    }

    push(s, 10);
    push(s, 20);

    int value;
    if (pop(s, &value) == SUCCESS && value == 20 && pop(s, &value) == SUCCESS && value == 10) {
        printf("SUCCESS\n");
    } else {
        printf("FAIL\n");
    }

    destroy(s);
}

int main() {
    test_push();
    test_pop();
    return 0;
}
