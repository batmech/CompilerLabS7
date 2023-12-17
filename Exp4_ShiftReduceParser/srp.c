#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Production {
    char left[10];
    char right[10];
};

int main() {
    char inputString[20], modifiedInputString[20], stack[50], tempString[50], currentChar[2], *token1, *token2, *substring;
    int i, j, stackLength, substringLength, diff, count = 0;
    struct Production productions[10];
    FILE *filePointer;

    filePointer = fopen("input.txt", "r");
    stack[0] = '\0';

    printf("\nEnter the input string: ");
    scanf("%s", inputString);
    strcpy(modifiedInputString, inputString);

    while (!feof(filePointer)) {
        fscanf(filePointer, "%s\n", tempString);
        token1 = strtok(tempString, "=");
        token2 = strtok(NULL, "=");
        strcpy(productions[count].left, token1);
        strcpy(productions[count].right, token2);
        count++;
    }

    i = 0;
    printf("\n\n| STACK |\t| INPUT |\t| ACTION |\n\n");
    printf("$\t%s$\t\n", modifiedInputString);

    while (1) {
        if (i < strlen(inputString)) {
            currentChar[0] = inputString[i];
            currentChar[1] = '\0';
            modifiedInputString[i] = ' ';
            i++;
            strcat(stack, currentChar);
            printf("$%s\t%s$\t Shift\n", stack, modifiedInputString);
        }

        for (j = 0; j < count; j++) {
            substring = strstr(stack, productions[j].right);
            if (substring != NULL) {
                stackLength = strlen(stack);
                substringLength = strlen(substring);
                diff = stackLength - substringLength;
                stack[diff] = '\0';
                strcat(stack, productions[j].left);
                printf("$%s\t%s$\t Reduce : %s -> %s\n", stack, modifiedInputString, productions[j].left, productions[j].right);
                j = -1;
            }
        }

        if (strcmp(stack, "S") == 0 && i == strlen(inputString)) {
            printf("\n%s is accepted\n", inputString);
            break;
        }

        if (i == strlen(inputString)) {
            printf("\n%s is not accepted\n", inputString);
            break;
        }
    }

    fclose(filePointer);
    return 0;
}
