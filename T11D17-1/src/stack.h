#ifndef STACK_H
#define STACK_H

#include <stdlib.h>

#define SUCCESS 0
#define FAIL -1

struct node {
    int value;
    struct node* next;
};

struct stack {
    struct node* top;
};

// Function declarations
struct stack* init();
int push(struct stack* s, int value);
int pop(struct stack* s, int* value);
void destroy(struct stack* s);

#endif  // STACK_H
