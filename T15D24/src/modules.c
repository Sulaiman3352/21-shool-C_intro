#include "modules.h"

#include "shared.h"
// Работа с базой modules

int get_last_id() {
    int id = -1;
    FILE* index_ptr = fopen(modules_idx, "rb");  // Open the index file
    if (index_ptr != NULL) {
        // Index entries are sorted by ID, so the last entry has the highest ID
        fseek(index_ptr, -sizeof(modules_index), SEEK_END);
        modules_index entry;
        if (fread(&entry, sizeof(modules_index), 1, index_ptr) == 1) {
            id = entry.id;  // Extract the ID from the last index entry
        }
        fclose(index_ptr);  // Close the index file
    }
    return id;
}

// Функция печатает все записи базы, считанные из файла
int print_modules(FILE* ptr) {
    int is_error = 0;
    modules rec;
    if (ptr == NULL) {
        is_error = 1;
    } else {
        fseek(ptr, 0, SEEK_SET);
        fread(&rec, sizeof(modules), 1, ptr);
        while (!feof(ptr)) {
            printf("%d %s %d %d %d\n", rec.id, rec.name, rec.level, rec.cell, rec.flag);
            fread(&rec, sizeof(modules), 1, ptr);
        }
    }
    return is_error;
}

// Функция считывает имя модуля и сохраняет его в строку
void get_name(char* name) {
    int size = 0;
    char c = ' ';
    scanf("%c", &c);
    if (c == '\n') scanf("%c", &c);
    while ((c != '\n') && (size != 30)) {
        name[size++] = c;
        scanf("%c", &c);
    }
    if (size > 30)
        printf("n/a\n");
    else
        name[size] = '\0';
}

// Функция получает данные о новой записи от пользователя
modules get_modules_record(int id) {
    printf("Enter record\n");
    modules rec;
    rec.id = id;
    printf("name:\n");
    get_name(rec.name);
    printf("level:\n");
    while (1) {
        if (scanf("%d", &(rec.level)) != 1)
            printf("n/a\n");
        else
            break;
    }
    printf("cell:\n");
    while (1) {
        if (scanf("%d", &(rec.cell)) != 1)
            printf("n/a\n");
        else
            break;
    }
    printf("flag:\n");
    while (1) {
        if (scanf("%d", &(rec.flag)) != 1)
            printf("n/a\n");
        else
            break;
    }
    return rec;
}

int add_modules_record(FILE* ptr, modules rec) {
    int is_error = 0;
    if (ptr == NULL) {
        is_error = 1;
    } else {
        fseek(ptr, 0, SEEK_END);
        fwrite(&rec, sizeof(modules), 1, ptr);
        fseek(ptr, 0, SEEK_SET);
        // rebuild_modules_index(ptr);  // Update index after adding
    }
    rebuild_modules_index(ptr);  // Add this line
    return is_error;
}

// Функция удаляет запись с определенным id
int delete_modules_record(FILE* ptr, int id) {
    int is_error = 0;
    if (ptr == NULL) {
        is_error = 1;
    } else {
        modules rec;
        int i = id;
        fseek(ptr, (i + 1) * sizeof(modules),
              SEEK_SET);  // устанавливаем указатель на следующую после удаляемой записи
        while (!feof(ptr)) {  // пока не достигнут конец файла сдвигаем все файлы на 1 назад
            fseek(ptr, (i + 1) * sizeof(modules), SEEK_SET);
            if (fread(&rec, sizeof(modules), 1, ptr) != 1) break;
            fseek(ptr, i * sizeof(modules), SEEK_SET);
            rec.id--;
            fwrite(&rec, sizeof(modules), 1, ptr);
            i++;
        }
        fseek(ptr, 0, SEEK_SET);
        truncate(modules_fpath, i * sizeof(modules));  // обрезаем файл для уменьшения его размера
    }
    rebuild_modules_index(ptr);  // Update index after deletion
    return is_error;
}

// Функция изменяет запись с определенным id
int change_modules_record(FILE* ptr, int id, modules rec) {
    int is_error = 0;
    if (ptr == NULL) {
        is_error = 1;
    } else {
        fseek(ptr, id * sizeof(modules), SEEK_SET);
        //        printf("%d \"%s\" %d %d %d\n", rec.id, rec.name, rec.level, rec.cell, rec.flag);
        fwrite(&rec, sizeof(modules), 1, ptr);
        fseek(ptr, 0, SEEK_SET);
    }
    return is_error;
}

// Вставка записи в определенное место в файле
int insert_modules_record(FILE* ptr, int id, modules new_rec) {
    int is_error = 0;
    if (ptr == NULL) {
        is_error = 1;
    } else {
        modules rec;
        int i;
        fseek(ptr, -sizeof(modules), SEEK_END);  // устанавливаем указатель на последнюю запись в файле
        fread(&i, sizeof(int), 1, ptr);  // считываем значение последнего id
        while (i >= id) {  // двигаем все данные до того места куда будем вставлять
            fseek(ptr, i * sizeof(modules), SEEK_SET);
            fread(&rec, sizeof(modules), 1, ptr);
            fseek(ptr, (i + 1) * sizeof(modules), SEEK_SET);
            rec.id++;
            fwrite(&rec, sizeof(modules), 1, ptr);
            i--;
        }
        fseek(ptr, (i + 1) * sizeof(modules), SEEK_SET);
        fwrite(&new_rec, sizeof(modules), 1, ptr);  // вставляем запись
        fseek(ptr, 0, SEEK_SET);
    }
    return is_error;
}

// Функция выводит на экран определенное количество записей из базы
int select_modules(FILE* ptr, int count) {
    int is_error = 0;
    modules rec;
    int done = 0;
    int i = 0;
    if (count == 0) {
        print_modules(ptr);
        done = 1;
    }
    if (ptr == NULL) {
        is_error = 1;
    } else if (!done) {
        fseek(ptr, 0, SEEK_SET);
        fread(&rec, sizeof(modules), 1, ptr);
        while (!feof(ptr)) {
            if (i < count) {
                printf("%d %s %d %d %d\n", rec.id, rec.name, rec.level, rec.cell, rec.flag);
                fread(&rec, sizeof(modules), 1, ptr);
                i++;
            } else {
                break;
            }
        }
    }
    return is_error;
}

// ------------------- 2nd Quest

int check_modules_id(int id) {
    FILE* index_ptr = fopen(modules_idx, "rb");
    if (!index_ptr) return 0;

    // Binary search in the index file
    fseek(index_ptr, 0, SEEK_END);
    long file_size = ftell(index_ptr);
    int num_entries = file_size / sizeof(modules_index);
    int low = 0, high = num_entries - 1;
    int found = 0;

    while (low <= high) {
        int mid = (low + high) / 2;
        fseek(index_ptr, mid * sizeof(modules_index), SEEK_SET);
        modules_index entry;
        fread(&entry, sizeof(modules_index), 1, index_ptr);
        if (entry.id == id) {
            found = 1;
            break;
        } else if (entry.id < id) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    fclose(index_ptr);
    return found;
}