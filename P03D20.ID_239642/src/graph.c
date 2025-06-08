#include "./graph.h"

#include "stack.h"

char* getString(int* length) {
    *length = 0;
    int capacity = 2;  // Начальная ёмкость с учётом '\0'
    char* str = malloc(capacity * sizeof(char));
    if (!str) return NULL;

    char c = getchar();
    while (c != '\n') {
        if (c != ' ') {
            // Проверяем, нужно ли увеличить ёмкость (оставляем место для '\0')
            if (*length >= capacity - 1) {
                capacity *= 2;
                char* tmp = realloc(str, capacity);
                if (!tmp) {
                    free(str);
                    return NULL;
                }
                str = tmp;
            }
            str[(*length)++] = c;
            str[*length] = '\0';  // Явное добавление терминатора
        }
        c = getchar();
    }
    return str;
}

int isDigit(char sym) { return ('0' <= sym && sym <= '9') ? 1 : 0; }

int getPriority(char op) {
    int priority = -1;
    switch (op) {
        case '(':
            priority = 0;
            break;
        case '+':
        case '-':
            priority = 1;
            break;
        case '*':
        case '/':
            priority = 2;
            break;
        case '^':
            priority = 3;
            break;
        case 's':
        case 'c':
        case 't':
        case 'g':
        case 'q':
        case 'l':
        case '~':
            priority = 4;
            break;
        default:
            break;
    }
    return priority;
}

void ifSinOrSqrt(const char* expression, int* i, char* op, int* no_error) {
    int size = strlen(expression);
    if (*i + 2 < size && expression[*i + 1] == 'i' && expression[*i + 2] == 'n') {
        *op = 's';
        *i += 2;
    } else if (*i + 3 < size && expression[*i + 1] == 'q' && expression[*i + 2] == 'r' &&
               expression[*i + 3] == 't') {
        *op = 'q';
        *i += 3;
    } else if (*i + 1 < size && expression[*i + 1] == 'q') {
        *no_error = 0;
    } else {
        *no_error = 0;
    }
}

void ifCosOrCtg(const char* expression, int* i, char* op, int* no_error) {
    int size = strlen(expression);
    if (*i + 2 < size) {
        if (expression[*i + 1] == 'o' && expression[*i + 2] == 's') {
            *op = 'c';
            *i += 2;
        } else if (expression[*i + 1] == 't' && expression[*i + 2] == 'g') {
            *op = 'g';
            *i += 2;
        } else {
            *no_error = 0;
        }
    } else {
        *no_error = 0;
    }
}

char* getNumber(const char* expression, char* num, int* i) {
    int j, k = 0;
    memset(num, 0, 20);  // Инициализация нулями
    for (j = *i; j < (int)strlen(expression) && k < 19; j++) {
        if (isDigit(expression[j]) || expression[j] == '.') {
            num[k++] = expression[j];
        } else {
            break;
        }
    }
    num[k] = '\0';  // Явный терминатор
    *i = j - 1;     // Корректное обновление индекса
    return num;
}
char* toPostfix(const char* expression, char* post_expr, int* no_error) {
    struct stack* top = NULL;
    int k = 0;
    int size = strlen(expression);
    // Увеличиваем размер буфера с запасом
    post_expr = realloc(post_expr, (2 * size + 1) * sizeof(char));
    if (!post_expr) {
        *no_error = 0;
        return NULL;
    }
    memset(post_expr, 0, (2 * size + 1) * sizeof(char));

    for (int i = 0; i < size; i++) {
        if (k >= 2 * size) {  // Проверка на переполнение
            *no_error = 0;
            break;
        }

        char sym = expression[i];
        if (sym == 'x') {
            post_expr[k++] = sym;
        } else if (isDigit(sym)) {
            char num[20];
            getNumber(expression, num, &i);
            for (int j = 0; j < (int)strlen(num); j++) {
                post_expr[k++] = num[j];
            }
            post_expr[k++] = ' ';
        } else if (sym == '(') {
            top = push(sym, 0, top);
        } else if (sym == ')') {
            while (stackCount(top) > 0 && top->operand != '(') {
                post_expr[k++] = top->operand;
                top = pop(top);
            }
            if (stackCount(top) == 0) {
                *no_error = 0;
                break;
            }
            top = pop(top);
        } else {
            checkOperand(expression, &i, &sym, no_error);
            if (!*no_error) break;

            while (stackCount(top) > 0 && getPriority(top->operand) >= getPriority(sym)) {
                post_expr[k++] = top->operand;
                top = pop(top);
            }
            top = push(sym, 0, top);
        }
    }

    while (top != NULL) {
        if (top->operand == '(') {
            *no_error = 0;
        }
        post_expr[k++] = top->operand;
        top = pop(top);
    }
    post_expr[k] = '\0';
    return post_expr;
}
void checkOperand(const char* expression, int* i, char* op, int* no_error) {
    if (*op == '-' && (*i == 0 || expression[*i - 1] == '(')) {
        *op = '~';  // Унарный минус
    } else if (*op == 's') {
        ifSinOrSqrt(expression, i, op, no_error);
    } else if (*op == 'c') {
        ifCosOrCtg(expression, i, op, no_error);
    } else if (*op == 'l') {  // Обработка ln
        int size = strlen(expression);
        if (*i + 1 < size && expression[*i + 1] == 'n') {
            *op = 'l';  // Символ для натурального логарифма
            *i += 1;
        } else {
            *no_error = 0;
        }
    } else if (*op == 't') {  // Обработка tan
        int size = strlen(expression);
        if (*i + 2 < size && expression[*i + 1] == 'a' && expression[*i + 2] == 'n') {
            *op = 't';
            *i += 2;
        } else {
            *no_error = 0;
        }
    }
}

double calcY(const char* post_expr, double x) {
    double y = NAN;
    struct stack* top = NULL;
    int error = 0;

    for (int i = 0; !error && i < (int)strlen(post_expr); i++) {
        char sym = post_expr[i];
        if (isDigit(sym)) {
            char num[20];
            getNumber(post_expr, num, &i);
            if (strlen(num) == 0) {
                error = 1;
                continue;
            }
            top = push(' ', atof(num), top);
        } else if (sym == 'x') {
            top = push(' ', x, top);
        } else if (getPriority(sym) != -1) {
            if (getPriority(sym) == 4) {
                double operand;
                if (top == NULL) {
                    error = 1;
                    continue;
                }
                top = getTopValue(top, &operand);
                double result = getResult(sym, operand);
                if (isnan(result)) {
                    error = 1;
                    continue;
                }
                top = push(' ', result, top);
            } else {
                double a, b;
                if (top == NULL || top->next == NULL) {
                    error = 1;
                    continue;
                }
                top = getTopValue(top, &b);
                top = getTopValue(top, &a);
                double result = getBinResult(sym, a, b);
                if (isnan(result)) {
                    error = 1;
                    continue;
                }
                top = push(' ', result, top);
            }
        } else if (sym != ' ') {
            error = 1;
        }
    }

    if (!error && top != NULL && top->next == NULL) {
        y = top->value;
    }
    destroy(top);
    return y;
}
double getBinResult(char operand, double a, double b) {
    double res = 0;
    switch (operand) {
        case '+':
            res = a + b;
            break;
        case '-':
            res = a - b;
            break;
        case '*':
            res = a * b;
            break;
        case '/':
            if (fabs(b) < 1e-10) {
                return NAN;
            }
            res = a / b;
            break;
        case '^':
            res = pow(a, b);
            break;
        default:
            break;
    }
    return res;
}

double getResult(char operand, double a) {
    double res = 0;
    switch (operand) {
        case 's':
            res = sin(a);
            break;
        case 'c':
            res = cos(a);
            break;
        case 't':
            if (fabs(cos(a)) < 1e-10) return NAN;
            res = tan(a);
            break;
        case 'g':
            res = cos(a) / sin(a);
            break;
        case 'q':
            if (a < 0) return NAN;
            res = sqrt(a);
            break;
        case 'l':
            if (a <= 0) return NAN;
            res = log(a);
            break;
        case '~':
            res = -1 * a;
            break;
        default:
            break;
    }
    return res;
}

void fillX(double x_arr[SIZE_X]) {
    double value = 0;
    for (int i = 0; i < SIZE_X; i++) {
        x_arr[i] = value;
        value += X_STEP;
    }
}

void calcFunc(const char* post_expr, const double x_arr[SIZE_X], int i_arr[SIZE_X], int j_arr[SIZE_X]) {
    for (int j = 0; j < SIZE_X; j++) {
        double y = calcY(post_expr, x_arr[j]);
        if (isnan(y) || y > MAX_DEFINITION_Y || y < MIN_DEFINITION_Y) {
            i_arr[j] = -1;
            j_arr[j] = -1;
        } else {
            int i_ =
                (int)round((MAX_DEFINITION_Y - y) * (HEIGHT - 1) / (MAX_DEFINITION_Y - MIN_DEFINITION_Y));
            i_ = (i_ < 0) ? 0 : (i_ >= HEIGHT) ? HEIGHT - 1 : i_;
            i_arr[j] = i_;
            j_arr[j] = j;
        }
    }
}

void drawFunc(const int i_arr[SIZE_X], const int j_arr[SIZE_X]) {
    for (int i = HEIGHT - 1; i >= 0; i--) {
        for (int j = 0; j < WIDTH; j++) {
            if (i_arr[j] == i && j_arr[j] == j) {
                printf("%c", GRAPH);
            } else {
                printf("%c", SPACE);
            }
        }
        printf("\n");
    }
    printf("\n");
}