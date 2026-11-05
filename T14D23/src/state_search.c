#include "state_search.h"

#include <stdio.h>
#include <string.h>

int main() {
    char a[250];
    fgets(a, sizeof(a), stdin);
    int len1 = strlen(a);
    if (len1 > 0 && a[len1 - 1] == '\n') {
        a[len1 - 1] = '\0';
    }
    int day1 = 0, month1 = 0, year1 = 0;
    if (scanf("%d.%d.%d", &day1, &month1, &year1) != 3) {
        printf("n/a");
        return 0;
    }

    FILE *f = fopen(a, "rb+");
    if (is_file_empty(f)) {
        printf("n/a");
        return 0;
    }
    int size = get_records_count_in_file(f);
    for (int i = 0; i < size; i++) {
        my_struct mys = read_record_from_file(f, i);
        if (mys.day == day1 && mys.month == month1 && mys.year == year1) {
            printf("%d", mys.kod);
            return 0;
        }
    }
    printf("n/a");
    fclose(f);

    return 0;
}

int is_file_empty(FILE *file) {
    fseek(file, 0, SEEK_END);  // Перемещаем указатель в конец файла
    long size = ftell(file);   // Получаем размер файла
    rewind(file);              // Возвращаем указатель в начало

    return size == 0;  // Возвращаем 1 если файл пуст, 0 если нет
}

int cmpb(my_struct a, my_struct b) {
    if (a.year > b.year) {
        return 1;
    } else if (a.year == b.year && a.month > b.month) {
        return 1;
    } else if (a.year == b.year && a.month == b.month && a.day > b.day) {
        return 1;
    } else if (a.year == b.year && a.month == b.month && a.day == b.day && a.min > b.min) {
        return 1;
    } else if (a.year == b.year && a.month == b.month && a.day == b.day && a.min == b.min && a.sec > b.sec) {
        return 1;
    }
    return 0;
}

void sort(FILE *pfile) {
    int size = get_records_count_in_file(pfile);
    if (size == 0) {
        printf("n/a\n");
        return;
    }
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            my_struct r1 = read_record_from_file(pfile, j);
            my_struct r2 = read_record_from_file(pfile, j + 1);
            if (cmpb(r1, r2)) {
                swap_records_in_file(pfile, j, j + 1);
            }
        }
    }
}

int input(int *n) {
    int flag = 1;
    if (scanf("%d", n) != 1) {
        flag = 0;
    }
    return flag;
}

void print_file(FILE *pfile) {
    int count = get_records_count_in_file(pfile);
    if (count == 0) {
        printf("n/a\n");
        return;
    }

    for (int i = 0; i < count; i++) {
        my_struct r = read_record_from_file(pfile, i);
        printf("%d %d %d %d %d %d %d %d\n", r.year, r.month, r.day, r.hour, r.min, r.sec, r.status, r.kod);
    }
}

// Function of reading a record of a given type from a file by its serial number.
struct my_struct read_record_from_file(FILE *pfile, int index) {
    // Calculation of the offset at which desired entry should be located from the beginning of the file.
    int offset = index * sizeof(struct my_struct);
    // Move the position pointer to the calculated offset from the beginning of the file.
    fseek(pfile, offset, SEEK_SET);

    // Reading a record of the specified type from a file.
    struct my_struct record;
    fread(&record, sizeof(struct my_struct), 1, pfile);

    // For safety reasons, we return the file position pointer to the beginning of the file.
    rewind(pfile);

    // Return read record
    return record;
}

// Function of writing a record of the specified type to the file at the specified serial number.
void write_record_in_file(FILE *pfile, const struct my_struct *record_to_write, int index) {
    // Calculation of the offset at which the required record should be located from the beginning of the
    // file.
    int offset = index * sizeof(struct my_struct);
    // Move the position pointer to the calculated offset from the beginning of the file.
    fseek(pfile, offset, SEEK_SET);

    // Write a record of the specified type to a file.
    fwrite(record_to_write, sizeof(struct my_struct), 1, pfile);

    // Just in case, force the I/O subsystem to write the contents of its buffer to a file right now.
    fflush(pfile);

    // For safety reasons, return the file position pointer to the beginning of the file.
    rewind(pfile);
}

// Function of mutual transfer of two records in the file by their indexes.
void swap_records_in_file(FILE *pfile, int record_index1, int record_index2) {
    // Read both records from file to variables
    struct my_struct record1 = read_record_from_file(pfile, record_index1);
    struct my_struct record2 = read_record_from_file(pfile, record_index2);

    // Rewrite records in file
    write_record_in_file(pfile, &record1, record_index2);
    write_record_in_file(pfile, &record2, record_index1);
}

// Function to get file size in bytes.
int get_file_size_in_bytes(FILE *pfile) {
    int size = 0;
    fseek(pfile, 0, SEEK_END);  // Move the position pointer to the end of the file.
    size = ftell(
        pfile);  // Read the number of bytes from the beginning of the file to the current position pointer.
    rewind(pfile);  // For safety reasons, move the position pointer back to the beginning of the file.
    return size;
}

// Function to get count of records in file
int get_records_count_in_file(FILE *pfile) {
    return get_file_size_in_bytes(pfile) / sizeof(struct my_struct);
}
