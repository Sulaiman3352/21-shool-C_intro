#include "stack.h"

// Initialize a new empty stack
struct stack* init() {
    struct stack* s = (struct stack*)malloc(sizeof(struct stack));
    if (!s) return NULL;
    s->top = NULL;
    return s;
}

// Push a value onto the stack
int push(struct stack* s, int value) {
    if (!s) return FAIL;

    struct node* new_node = (struct node*)malloc(sizeof(struct node));
    if (!new_node) return FAIL;

    new_node->value = value;
    new_node->next = s->top;
    s->top = new_node;

    return SUCCESS;
}

// Pop a value from the stack
int pop(struct stack* s, int* value) {
    if (!s || !s->top) return FAIL;

    struct node* temp = s->top;
    *value = temp->value;
    s->top = temp->next;

    free(temp);
    return SUCCESS;
}

// Destroy the stack and free memory
void destroy(struct stack* s) {
    if (!s) return;

    while (s->top) {
        struct node* temp = s->top;
        s->top = s->top->next;
        free(temp);
    }

    free(s);
}
