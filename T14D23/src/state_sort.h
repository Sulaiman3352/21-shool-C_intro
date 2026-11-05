#ifndef STATE_SORT_H
#define STATE_SORT_H
#include <stdio.h>
#include <stdlib.h>

typedef struct my_struct {
    int year;
    int month;
    int day;
    int hour;
    int min;
    int sec;
    int status;
    int kod;
} my_struct;

int is_file_empty(FILE *file);
int input_my_struct(my_struct *m);
void sort(FILE *pfile);
void print_file(FILE *pfile);
struct my_struct read_record_from_file(FILE *pfile, int index);
void write_record_in_file(FILE *pfile, const struct my_struct *record_to_write, int index);
void swap_records_in_file(FILE *pfile, int record_index1, int record_index2);
int get_file_size_in_bytes(FILE *pfile);
int get_records_count_in_file(FILE *pfile);
int input(int *n);

#endif