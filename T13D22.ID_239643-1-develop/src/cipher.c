#include <ctype.h>
#include <dirent.h>       // to deal with directories
#include <limits.h>       // for PATH_MAX
#include <openssl/evp.h>  // for encryption functions
#include <openssl/provider.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define MAX_PATH 256

#include "./logger.h"  // 5th Quest

bool file_exists(const char *filename) { return access(filename, F_OK) == 0; }

void get_the_file(char *filename);
void encrypt_caesar(char *text, int shift);
void encrypt_des_file(const char *filepath);
void process_directory(const char *directory, int shift, int mode);
void clear_h_files(const char *directory);

int main() {
    char filename[100] = {0};
    int menu;
    FILE *file = NULL;

    // Initialize logger
    FILE *log_file = log_init("program.log");
    if (!log_file) {
        fprintf(stderr, "Failed to initialize log file\n");
    } else {
        logcat(log_file, "Logger initialized", INFO);
    }

    OSSL_PROVIDER *legacy = OSSL_PROVIDER_load(NULL, "legacy");
    if (legacy == NULL) {
        logcat(log_file, "Failed to load legacy provider", ERROR);
    } else {
        logcat(log_file, "Legacy provider loaded", INFO);
    }

    while (true) {
        scanf("%d", &menu);
        getchar();  // Clear newline left by scanf
        if (menu == 1) {
            if (file) {
                fclose(file);
                file = NULL;
            }
            get_the_file(filename);
            if (file_exists(filename)) {
                file = fopen(filename, "r");
                if (file) {
                    char s;
                    logcat(log_file, "Opened file for reading", DEBUG);
                    while ((s = fgetc(file)) != EOF) {
                        printf("%c", s);
                    }
                    long lSize = ftell(file);
                    if (lSize == 0) {
                        printf("n/a");
                    }
                    printf("\n");
                    fclose(file);
                } else {
                    logcat(log_file, "Failed to open file for reading", ERROR);
                    printf("n/a\n");
                }
            } else {
                logcat(log_file, "File does not exist", WARNING);
                printf("n/a\n");
            }
        } else if (menu == 2) {
            char text[100];
            fgets(text, sizeof(text), stdin);
            text[strcspn(text, "\n")] = 0;
            if (filename[0] != '\0' && file_exists(filename)) {
                FILE *tmp = fopen(filename, "a");
                if (tmp) {
                    fputs("\n", tmp);
                    fputs(text, tmp);
                    fclose(tmp);
                    logcat(log_file, "Appended text to file", INFO);
                }
                tmp = fopen(filename, "r");
                if (tmp) {
                    char ch;
                    while ((ch = fgetc(tmp)) != EOF) {
                        putchar(ch);
                    }
                    printf("\n");
                    fclose(tmp);
                }
            } else {
                logcat(log_file, "File not set or doesn't exist", WARNING);
                printf("n/a\n");
            }
        } else if (menu == 3) {
            char dir[256] = "./ai_modules";
            int shift;
            scanf("%d", &shift);
            getchar();
            process_directory(dir, shift, menu);
            clear_h_files(dir);
            logcat(log_file, "Processed directory with Caesar encryption", INFO);
        } else if (menu == 4) {
            char dir[32] = "./ai_modules";
            process_directory(dir, 0, menu);
            clear_h_files(dir);
            logcat(log_file, "Processed directory with DES encryption", INFO);
        } else if (menu == -1) {
            if (file_exists(filename) && file) {
                fclose(file);
                file = NULL;
            }
            logcat(log_file, "Program exiting", INFO);
            break;
        } else {
            logcat(log_file, "Invalid menu option selected", WARNING);
            printf("n/a\n");
        }
    }

    if (legacy) {
        OSSL_PROVIDER_unload(legacy);
    }
    if (log_file) {
        log_close(log_file);
    }
    return 0;
}

void get_the_file(char *filename) {
    fgets(filename, 100, stdin);
    filename[strcspn(filename, "\n")] = 0;
}

void encrypt_caesar(char *text, int shift) {
    size_t len = strlen(text);
    for (size_t i = 0; i < len; i++) {
        if (isupper(text[i])) {
            text[i] = (char)(((text[i] - 'A' + shift) % 26) + 'A');
        } else if (islower(text[i])) {
            text[i] = (char)(((text[i] - 'a' + shift) % 26) + 'a');
        }
    }
}

void encrypt_des_file(const char *filepath) {
    FILE *file = fopen(filepath, "rb");
    if (!file) {
        printf("n/a");
        return;
    }
    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    rewind(file);
    if (size <= 0) {
        fclose(file);
        printf("n/a");
        return;
    }
    unsigned char *data = malloc(size);
    if (!data) {
        fclose(file);
        printf("n/a");
        return;
    }
    if (fread(data, 1, size, file) != (size_t)size) {
        fclose(file);
        free(data);
        printf("n/a");
        return;
    }
    fclose(file);

    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    if (!ctx) {
        free(data);
        printf("n/a");
        return;
    }
    unsigned char key[8] = "mykey123";  // exactly 8 bytes
    unsigned char iv[8] = "iv123456";   // exactly 8 bytes
    if (EVP_EncryptInit_ex(ctx, EVP_des_cbc(), NULL, key, iv) != 1) {
        EVP_CIPHER_CTX_free(ctx);
        free(data);
        printf("n/a");
        return;
    }
    int block_size = EVP_CIPHER_CTX_block_size(ctx);
    unsigned char *output = malloc(size + block_size);
    if (!output) {
        EVP_CIPHER_CTX_free(ctx);
        free(data);
        printf("n/a");
        return;
    }
    int outlen1 = 0, outlen2 = 0;
    if (EVP_EncryptUpdate(ctx, output, &outlen1, data, size) != 1) {
        EVP_CIPHER_CTX_free(ctx);
        free(data);
        free(output);
        printf("n/a");
        return;
    }
    if (EVP_EncryptFinal_ex(ctx, output + outlen1, &outlen2) != 1) {
        EVP_CIPHER_CTX_free(ctx);
        free(data);
        free(output);
        printf("n/a");
        return;
    }
    int total = outlen1 + outlen2;
    file = fopen(filepath, "wb");
    if (!file) {
        EVP_CIPHER_CTX_free(ctx);
        free(data);
        free(output);
        printf("n/a");
        return;
    }
    fwrite(output, 1, total, file);
    fclose(file);
    EVP_CIPHER_CTX_free(ctx);
    free(data);
    free(output);
}

void process_directory(const char *directory, int shift, int mode) {
    DIR *dir = opendir(directory);
    if (!dir) return;
    struct dirent *entry;
    char filepath[MAX_PATH];
    while ((entry = readdir(dir)) != NULL) {
        if (snprintf(filepath, MAX_PATH, "%s/%s", directory, entry->d_name) >= MAX_PATH) {
            continue;
        }
        if (strstr(entry->d_name, ".c")) {
            if (mode == 3) {
                FILE *file = fopen(filepath, "r+");
                if (!file) continue;
                fseek(file, 0, SEEK_END);
                long size = ftell(file);
                rewind(file);
                char *content = malloc(size + 1);
                if (!content) {
                    fclose(file);
                    continue;
                }
                fread(content, 1, size, file);
                content[size] = '\0';
                encrypt_caesar(content, shift);
                rewind(file);
                fwrite(content, 1, size, file);
                fclose(file);
                free(content);
            } else if (mode == 4) {
                encrypt_des_file(filepath);
            }
        }
    }
    closedir(dir);
}

void clear_h_files(const char *directory) {
    DIR *dir = opendir(directory);
    if (!dir) return;
    struct dirent *entry;
    char filepath[MAX_PATH];
    while ((entry = readdir(dir)) != NULL) {
        if (snprintf(filepath, MAX_PATH, "%s/%s", directory, entry->d_name) >= MAX_PATH) {
            continue;
        }
        if (strstr(entry->d_name, ".h")) {
            FILE *file = fopen(filepath, "w");
            if (file) fclose(file);
        }
    }
    closedir(dir);
}
