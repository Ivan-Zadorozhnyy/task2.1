#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* data;
    size_t size;
    size_t capacity;
} DynamicArray;

DynamicArray* create_dynamic_array() {
    DynamicArray* array = (DynamicArray*)malloc(sizeof(DynamicArray));
    if (!array) {
        perror("Failed to allocate memory for DynamicArray");
        exit(EXIT_FAILURE);
    }
    array->capacity = 10;
    array->size = 0;
    array->data = (char*)malloc(array->capacity * sizeof(char));
    if (!array->data) {
        perror("Failed to allocate memory for DynamicArray data");
        free(array);
        exit(EXIT_FAILURE);
    }
    array->data[0] = '\0';
    return array;
}

void append_to_dynamic_array(DynamicArray* array, const char* text) {
    size_t len = strlen(text);
    while (array->size + len >= array->capacity) {
        array->capacity *= 2;
        char* new_data = (char*)realloc(array->data, array->capacity * sizeof(char));
        if (!new_data) {
            perror("Failed to reallocate memory for DynamicArray data");
            free(array->data);
            free(array);
            exit(EXIT_FAILURE);
        }
        array->data = new_data;
    }
    strcpy(array->data + array->size, text);
    array->size += len;
}

void insert_substring(DynamicArray* array, size_t pos, const char* substring) {
    size_t len = strlen(substring);
    while (array->size + len >= array->capacity) {
        array->capacity *= 2;
        char* new_data = (char*)realloc(array->data, array->capacity * sizeof(char));
        if (!new_data) {
            perror("Failed to reallocate memory for DynamicArray data");
            free(array->data);
            free(array);
            exit(EXIT_FAILURE);
        }
        array->data = new_data;
    }
    memmove(array->data + pos + len, array->data + pos, array->size - pos + 1);
    memcpy(array->data + pos, substring, len);
    array->size += len;
}

void free_dynamic_array(DynamicArray* array) {
    free(array->data);
    free(array);
}

int main() {
    DynamicArray* inp = create_dynamic_array();
    char str[500];
    int choice;

    while (1) {
        printf("Choose the command:\n");
        printf("1. Append text\n");
        printf("2. Start new line\n");
        printf("3. Save as file\n");
        printf("4. Load file\n");
        printf("5. Print current saved text\n");
        printf("6. Find text\n");
        printf("7. Insert text at position\n");
        printf("8. Clear console (platform dependent)\n");
        printf("0. Exit\n");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a number.\n");
            while(getchar() != '\n');  // Clear input buffer
            continue;
        }
        while(getchar() != '\n');  // Clear input buffer

        switch (choice) {
            case 1:
                printf("Enter text to append:\n");
                fgets(str, sizeof(str), stdin);
                append_to_dynamic_array(inp, str);
                break;
            case 2:
                append_to_dynamic_array(inp, "\n");
                break;
            case 3:
                printf("Enter the file name for saving: ");
                char filename[80];
                fgets(filename, sizeof(filename), stdin);
                size_t len = strlen(filename);
                if (len > 0 && filename[len - 1] == '\n') {
                    filename[len - 1] = '\0';
                }
                FILE *file = fopen(filename, "w");
                if (file != NULL) {
                    fprintf(file, "%s", inp->data);
                    fclose(file);
                    printf("Text saved to %s\n", filename);
                } else {
                    printf("Error opening the file for writing.\n");
                }
                break;
            case 4:
                printf("Enter the file name for loading: ");
                fgets(filename, sizeof(filename), stdin);
                len = strlen(filename);
                if (len > 0 && filename[len - 1] == '\n') {
                    filename[len - 1] = '\0';
                }
                file = fopen(filename, "r");
                if (file != NULL) {
                    while (fgets(str, sizeof(str), file) != NULL) {
                        append_to_dynamic_array(inp, str);
                    }
                    fclose(file);
                    printf("Text loaded from %s\n", filename);
                } else {
                    printf("Error opening the file for reading or file does not exist.\n");
                }
                break;
            case 5:
                printf("Current saved text:\n%s\n", inp->data);
                break;
            case 6:
                printf("Enter text to search:\n");
                fgets(str, sizeof(str), stdin);
                len = strlen(str);
                if (len > 0 && str[len - 1] == '\n') {
                    str[len - 1] = '\0';
                }
                char *pos = inp->data;
                int found = 0;
                while ((pos = strstr(pos, str)) != NULL) {
                    printf("Found at position: %ld\n", pos - inp->data);
                    pos += len;  // Move past the found substring
                    found = 1;
                }
                if (!found) {
                    printf("Not found.\n");
                }
                break;
            case 7:
                printf("Enter position to insert at:\n");
                size_t position;
                if (scanf("%zu", &position) != 1) {
                    printf("Invalid input. Please enter a valid position.\n");
                    while(getchar() != '\n');  // Clear input buffer
                    continue;
                }
                while(getchar() != '\n');  // Clear input buffer
                if (position > inp->size) {
                    printf("Position out of range. Current size is %zu.\n", inp->size);
                    break;
                }
                printf("Enter text to insert:\n");
                fgets(str, sizeof(str), stdin);
                insert_substring(inp, position, str);
                break;
            case 8:
                system("clear");
                break;
            case 0:
                free_dynamic_array(inp);
                return 0;
            default:
                printf("Invalid command\n");
                break;
        }
    }
}