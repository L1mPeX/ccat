#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct {
    char** data;
    int size;
    int capacity;
} StringArray;

void initStringArray(StringArray* arr, int initialCapacity) {
    arr->data = malloc(initialCapacity * sizeof(char*));
    arr->size = 0;
    arr->capacity = initialCapacity;
}

void addString(StringArray* arr, const char* str) {
    if (arr->size == arr->capacity) {
        arr->capacity *= 2;
        arr->data = realloc(arr->data, arr->capacity * sizeof(char*));
    }
    arr->data[arr->size++] = strdup(str);
}

void freeStringArray(StringArray* arr) {
    for (int i = 0; i < arr->size; i++) {
        free(arr->data[i]);
    }
    free(arr->data);
    arr->size = 0;
    arr->capacity = 0;
}

int readFileToStringArray(const char* filename, StringArray* arr) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        perror("Error opening file");
        return -1;
    }

    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), file)) {
        buffer[strcspn(buffer, "\n")] = '\0';
        addString(arr, buffer);
    }

    fclose(file);
    return 0;
}

int countCharacters(const StringArray* arr) {
    int count = 0;
    for (int i = 0; i < arr->size; i++) {
        for (int j = 0; arr->data[i][j] != '\0'; j++) {
            if (!isspace(arr->data[i][j])) {
                count++;
            }
        }
    }
    return count;
}

int countWords(const StringArray* arr) {
    int count = 0;
    for (int i = 0; i < arr->size; i++) {
        int inWord = 0;
        for (int j = 0; arr->data[i][j] != '\0'; j++) {
            if (isspace(arr->data[i][j])) {
                inWord = 0;
            } else if (!inWord) {
                inWord = 1;
                count++;
            }
        }
    }
    return count;
}

int countLines(const StringArray* arr) {
    return arr->size;
}

void printStringArrayWithNumbers(const StringArray* arr, const char* filename) {
    printf("=== %s ===\n", filename);
    for (int i = 0; i < arr->size; i++) {
        printf("%4d | %s\n", i + 1, arr->data[i]);
    }
    printf("\n");
}

void printHelp(const char* programName) {
    printf("Usage: %s [OPTIONS] <filename1> [filename2 ...]\n", programName);
    printf("\nOPTIONS:\n");
    printf("  --help         Show this help message and exit\n");
    printf("  --ca           Count and display the number of characters in the file\n");
    printf("  --cw           Count and display the number of words in the file\n");
    printf("  --cl           Count and display the number of lines in the file\n");
    printf("\nDESCRIPTION:\n");
    printf("This program reads text files and displays their content in a formatted way.\n");
    printf("It can also count the number of characters, words, and lines in the files.\n");
    printf("\nEXAMPLES:\n");
    printf("  %s --ca --cw file1.txt file2.txt\n", programName);
    printf("  %s --help\n", programName);
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Usage: %s [OPTIONS] <filename1> [filename2 ...]\n", argv[0]);
        printf("Use '%s --help' to see the list of options.\n", argv[0]);
        return 1;
    }

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--help") == 0) {
            printHelp(argv[0]);
            return 0;
        }
    }

    int caFlag = 0, cwFlag = 0, clFlag = 0;
    int fileArgStart = 1;

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--ca") == 0) {
            caFlag = 1;
        } else if (strcmp(argv[i], "--cw") == 0) {
            cwFlag = 1;
        } else if (strcmp(argv[i], "--cl") == 0) {
            clFlag = 1;
        } else {
            fileArgStart = i;
            break;
        }
    }

    if (fileArgStart == argc) {
        printf("Error: No files provided.\n");
        return 1;
    }

    StringArray strings;
    initStringArray(&strings, 10);

    for (int i = fileArgStart; i < argc; i++) {
        if (readFileToStringArray(argv[i], &strings) == 0) {
            printStringArrayWithNumbers(&strings, argv[i]);

            if (caFlag) {
                printf("Characters: %d\n", countCharacters(&strings));
            }
            if (cwFlag) {
                printf("Words: %d\n", countWords(&strings));
            }
            if (clFlag) {
                printf("Lines: %d\n", countLines(&strings));
            }
            printf("\n");
        } else {
            printf("Failed to read file: %s\n", argv[i]);
        }

        freeStringArray(&strings);
        initStringArray(&strings, 10);
    }

    freeStringArray(&strings);
    return 0;
}
