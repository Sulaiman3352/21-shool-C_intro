#include <stdio.h>
#include <math.h>

// Function to simulate division using subtraction
int divide(int a, int b) {
    int quotient = 0;
    while (a >= b) {
        a = a - b;
        quotient++;
    }
    return quotient;
}

// Function to find the largest prime divisor without using division or remainder operations
int largestPrimeDivisor(int a) {
    int largestPrime = -1;
    // Handle negative input by taking its absolute value
    if (a < 0) {
        a = -a;
    }
    // Check divisibility by 2
    while (a >= 2) {
        int quotient = divide(a, 2);
        if (a - (quotient * 2) == 0) { // Simulate remainder check
            largestPrime = 2;
            a = quotient;
        } else {
            break;
        }
    }
    // Check divisibility by odd numbers starting from 3
    for (int i = 3; i <= sqrt(a); i += 2) {
        while (a >= i) {
            int quotient = divide(a, i);
            if (a - (quotient * i) == 0) { // Simulate remainder check
                largestPrime = i;
                a = quotient;
            } else {
                break;
            }
        }
    }
    // If 'a' is still greater than 2, then 'a' itself is prime
    if (a > 2) {
        largestPrime = a;
    }

    return largestPrime;
}

int main() {
    int a;
    printf("Enter an integer: ");

    if (scanf("%d", &a) == 1){
        if (a == 0 || a == 1 || a == -1) {
            printf("No prime divisors for 0, 1, or -1.\n");
        } else {
            int result = largestPrimeDivisor(a);
            printf("The largest prime divisor of %d is %d\n", a, result);
        }
    }else{
        printf ("n/a");
    }
    return 0;
}