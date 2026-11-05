#ifndef GRAPH_H_
#define GRAPH_H_

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "stack.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#define WIDTH 80
#define HEIGHT 25
#define MID 13
#define MAX_DEFINITION_X M_PI * 4
#define X_STEP ((MAX_DEFINITION_X - MIN_DEFINITION_X) / (SIZE_X - 1))
#define Y_STEP 0.1
#define MIN_DEFINITION_X 0
#define MAX_DEFINITION_Y 1
#define MIN_DEFINITION_Y -1
#define SPACE '.'
#define GRAPH '*'
#define SIZE_Y 25
#define SIZE_X 80

int getPriority(char op);
int isDigit(char sym);
void checkOperand(const char* expression, int* i, char* op, int* no_error);
void ifCosOrCtg(const char* expression, int* i, char* op, int* no_error);
void ifSinOrSqrt(const char* expression, int* i, char* op, int* no_error);
void calcFunc(const char* post_expr, const double x_arr[SIZE_X], int i_arr[SIZE_X], int j_arr[SIZE_X]);
double calcY(const char* post_expr, double x);
void drawFunc(const int i_arr[SIZE_X], const int j_arr[SIZE_X]);
void fillX(double x_arr[SIZE_X]);
char* getString(int* length);
char* toPostfix(const char* expression, char* post_expr, int* no_error);
double getBinResult(char operand, double a, double b);
double getResult(char operand, double a);
char* getNumber(const char* expression, char* num, int* i);

#endif  // GRAPH_H_
