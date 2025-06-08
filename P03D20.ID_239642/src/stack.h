#ifndef STACK_H_
#define STACK_H_

#include <stdio.h>
#include <stdlib.h>

struct stack {
    char operand;
    double value;
    struct stack* next;
};

struct stack* push(char operand, double value, struct stack* top);
void destroy(struct stack* top);
struct stack* pop(struct stack* top);
int stackCount(struct stack* top);
struct stack* getTopValue(struct stack* top, double* last);

#endif