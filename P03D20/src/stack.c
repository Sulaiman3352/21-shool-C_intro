#include "stack.h"

struct stack* push(char operand, double value, struct stack* top) {
    struct stack* new_node = (struct stack*)malloc(sizeof(struct stack));
    new_node->operand = operand;
    new_node->value = value;
    new_node->next = top;
    return new_node;
}

void destroy(struct stack* top) {
    while (top != NULL) {
        struct stack* tmp = top;
        top = top->next;
        free(tmp);
    }
}

struct stack* pop(struct stack* top) {
    if (top != NULL) {
        struct stack* tmp = top;
        top = top->next;
        free(tmp);
    }
    return top;
}

int stackCount(struct stack* top) {
    int count = 0;
    while (top != NULL) {
        count++;
        top = top->next;
    }
    return count;
}

struct stack* getTopValue(struct stack* top, double* last) {
    if (top != NULL) {
        *last = top->value;
        struct stack* tmp = top;
        top = top->next;
        free(tmp);
    }
    return top;
}