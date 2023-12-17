#include <stdio.h>
#include <string.h>

int main() {
    char operation[10];
    FILE *inputFile, *outputFile;

    inputFile = fopen("input.txt", "r");
    if (inputFile == NULL) {
        printf("Error opening input file.\n");
        return 1;
    }

    outputFile = fopen("result.txt", "w");
    if (outputFile == NULL) {
        printf("Error opening output file.\n");
        return 1;
    }

    char operator, firstOperand[10], secondOperand[10], finalResult[10];
    while (fscanf(inputFile, "%c %s %s %s\n", &operator, firstOperand, secondOperand, finalResult) != EOF) {
        printf("%c %s %s %s\n", operator, firstOperand, secondOperand, finalResult);

        switch (operator) {
            case '+':
                strcpy(operation, "ADD ");
                break;
            case '-':
                strcpy(operation, "SUB");
                break;
            case '*':
                strcpy(operation, "MUL ");
                break;
            case '/':
                strcpy(operation, "DIV");
                break;
            default:
                printf("Invalid operator\n");
                return 1;
        }

        if (strlen(firstOperand) == 2) {
            fprintf(outputFile, "MOV AX, %s\n", firstOperand);
        } else {
            fprintf(outputFile, "MOV AX, [%s]\n", firstOperand);
        }

        if (strlen(secondOperand) == 2) {
            fprintf(outputFile, "MOV BX, %s\n", secondOperand);
        } else {
            fprintf(outputFile, "MOV BX, [%s]\n", secondOperand);
        }

        if (strcmp(operation, "ADD ") == 0 || strcmp(operation, "SUB") == 0) {
            fprintf(outputFile, "%s AX, BX\n", operation);
        } else {
            fprintf(outputFile, "%s BX\n", operation);
        }

        if (strlen(finalResult) == 2) {
            fprintf(outputFile, "MOV %s, AX\n", finalResult);
        }
    }

    fclose(inputFile);
    fclose(outputFile);
    return 0;
}
