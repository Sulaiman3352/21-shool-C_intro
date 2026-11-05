#ifndef DATA_IO_MACRO_H
#define DATA_IO_MACRO_H

#include <stdio.h>

/* Define a macro to read an array of any type */
#define READ_ARRAY(TYPE, ARRAY, SIZE)                                              \
    do {                                                                           \
        for (size_t i = 0; i < (SIZE); i++) {                                      \
            printf("Enter element %zu: ", i + 1);                                  \
            scanf(TYPE == int ? "%d" : TYPE == float ? "%f" : "%lf", &(ARRAY)[i]); \
        }                                                                          \
    } while (0)

/* Define a macro to print an array of any type */
#define PRINT_ARRAY(TYPE, ARRAY, SIZE)                                                \
    do {                                                                              \
        printf("[ ");                                                                 \
        for (size_t i = 0; i < (SIZE); i++) {                                         \
            printf(TYPE == int ? "%d " : TYPE == float ? "%f " : "%lf ", (ARRAY)[i]); \
        }                                                                             \
        printf("]\n");                                                                \
    } while (0)

#endif /* DATA_IO_MACRO_H */