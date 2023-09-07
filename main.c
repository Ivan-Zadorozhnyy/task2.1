#include <stdio.h>
#include <string.h>

int main() {
    char str[80];
    char inp[1000] = "";
    int i;
    int t = 1;
    while (t == 1) {
        printf("Choose the command:\n");
        printf("1. Append text\n");
        printf("2. Start new line\n");
        printf("3. save as file\n");
        printf("4. load file\n");
        printf("0. Exit\n");
        scanf("%d", &i);
        while(getchar() != '\n');

        switch(i) {
            case 1:
                printf("Enter text to append:\n");
                fgets(str, sizeof(str), stdin);
                strcat(inp, str);
                break;
            case 2:
                printf("New line is started\n");
                strcat(inp, "\n");
                break;
            case 3:
            {
                printf("Enter the file name for saving: ");
                char filename[80];
                fgets(filename, sizeof(filename), stdin);

                FILE *file = fopen(filename, "w");
                if (file != NULL) {
                    fprintf(file, "%s", inp);
                    fclose(file);
                    printf("Text saved to %s\n", filename);
                } else {
                    printf("Error opening the file for writing.\n");
                }
            }
                break;

            case 4:
                printf("Enter the file name for loading:");
                break;
            case 0:
                t = 0;
                break;
            default:
                printf("Invalid command\n");
                break;
        }
    }
    return 0;
}

