#include <stdio.h>

#define LEN 100

void sum(int *buff1, int len1, int *buff2, int len2, int *result, int *result_length);
void sub(int *buff1, int len1, int *buff2, int len2, int *result, int *result_length);

void sum(int *buff1, int len1, int *buff2, int len2, int *result, int *result_length) {
    int carry = 0, i;
    *result_length = (len1 > len2 ? len1 : len2) + 1;

    for (i = 0; i < *result_length; i++) {
        int digit1 = (len1 - 1 - i >= 0) ? buff1[len1 - 1 - i] : 0;
        int digit2 = (len2 - 1 - i >= 0) ? buff2[len2 - 1 - i] : 0;
        int sum = digit1 + digit2 + carry;
        result[*result_length - 1 - i] = sum % 10;
        carry = sum / 10;
    }
    if (result[0] == 0) {
        for (i = 0; i < *result_length - 1; i++) {
            result[i] = result[i + 1];
        }
        (*result_length)--;
    }
}

void sub(int *buff1, int len1, int *buff2, int len2, int *result, int *result_length) {
    int borrow = 0, i;

    if (len1 < len2 || (len1 == len2 && buff1[0] < buff2[0])) {
        printf("n/a\n");
        return;
    }

    *result_length = len1;
    for (i = 0; i < len1; i++) {
        int digit1 = buff1[len1 - 1 - i];
        int digit2 = (len2 - 1 - i >= 0) ? buff2[len2 - 1 - i] : 0;
        int diff = digit1 - digit2 - borrow;
        if (diff < 0) {
            diff += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }
        result[len1 - 1 - i] = diff;
    }

    while (*result_length > 1 && result[0] == 0) {
        for (i = 0; i < *result_length - 1; i++) {
            result[i] = result[i + 1];
        }
        (*result_length)--;
    }

    for (i = 0; i < *result_length; i++) {
        printf("%d", result[i]);
    }
    printf("\n");
}

int main() {
    int buff1[LEN], buff2[LEN], result[LEN + 1];
    int len1 = 0, len2 = 0, result_length;
    char c;

    while ((c = getchar()) != ' ' && c != '\n' && len1 < LEN) {
        if (c < '0' || c > '9') {
            printf("n/a\n");
            return 1;
        }
        buff1[len1++] = c - '0';
    }

    while ((c = getchar()) != '\n' && len2 < LEN) {
        if (c < '0' || c > '9') {
            printf("n/a\n");
            return 1;
        }
        buff2[len2++] = c - '0';
    }

    sum(buff1, len1, buff2, len2, result, &result_length);
    for (int i = 0; i < result_length; i++) {
        printf("%d", result[i]);
    }
    printf("\n");

    sub(buff1, len1, buff2, len2, result, &result_length);

    return 0;
}
