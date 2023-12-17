#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int isKeyword(const char *buffer) {
    const char *keywords[34] = {"auto", "break", "case", "char", "const", "continue", "default", "do", "double",
                                "else", "enum", "extern", "float", "for", "goto", "if", "int", "long", "register",
                                "return", "short", "signed", "sizeof", "static", "struct", "switch", "typedef",
                                "union", "unsigned", "void", "volatile", "while", "printf", "scanf"};

    for (int i = 0; i < 34; ++i) {
        if (strcmp(keywords[i], buffer) == 0) {
            return 1; // Keyword found
        }
    }
    return 0; // Not a keyword
}

int main() {
    FILE *inputFile = fopen("inp.txt", "r");
    FILE *outputFile = fopen("output.txt", "w+");
    if (inputFile == NULL || outputFile == NULL) {
        printf("Error opening files.\n");
        exit(EXIT_FAILURE);
    }

    int lineNo = 1;
    char buffer[50];

    printf("Lexeme: \t L.no:\t Token:\n");
    fprintf(outputFile, "Lexeme: \t L.no:\t Token:\n");

    int ch;
    while ((ch = fgetc(inputFile)) != EOF) {
        // Check for arithmetic operators
        if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '%') {
            printf("%c \t\t %d\t Arithmetic Operator\n", ch, lineNo);
            fprintf(outputFile, "%c \t\t %d\t Arithmetic Operator\n", ch, lineNo);
        }
        //Check for special symbols
        else if (ch == '(' || ch == ')' || ch == '{' || ch == '}') {
            printf("%c \t\t %d\t Special Symbol\n", ch, lineNo);
            fprintf(outputFile, "%c \t\t %d\t Special Symbol\n", ch, lineNo);
        }
        // Check for relational operators
        else if (ch == '<' || ch == '>' || ch == '=') {
            int nextChar = fgetc(inputFile);
            if (nextChar == '=') {
                printf("%c%c \t\t %d\t Relational Operator (LE or GE or EQ)\n", ch, nextChar, lineNo);
                fprintf(outputFile, "%c%c \t\t %d\t Relational Operator (LE or GE or EQ)\n", ch, nextChar, lineNo);
            } else {
                printf("%c \t\t %d\t Relational Operator (LT or GT or Assign)\n", ch, lineNo);
                fprintf(outputFile, "%c \t\t %d\t Relational Operator (LT or GT or Assign)\n", ch, lineNo);
                fseek(inputFile, -1, SEEK_CUR);
            }
        }
        // Check for identifiers or keywords
        else if (isalnum(ch)) {
            int index = 0;
            buffer[index++] = ch;

            while ((ch = fgetc(inputFile)) != EOF && isalnum(ch)) {
                buffer[index++] = ch;
            }
            buffer[index] = '\0';

            if (isKeyword(buffer)) {
                printf("%s \t\t %d\t Keyword\n", buffer, lineNo);
                fprintf(outputFile, "%s \t\t %d\t Keyword\n", buffer, lineNo);
            } else {
                printf("%s \t\t %d\t Identifier\n", buffer, lineNo);
                fprintf(outputFile, "%s \t\t %d\t Identifier\n", buffer, lineNo);
            }
            fseek(inputFile, -1, SEEK_CUR); // Move file pointer back by one character
        }
        // Check for newline
        else if (ch == '\n') {
            lineNo++;
        }
    }
    fclose(inputFile);
    fclose(outputFile);
    return 0;
}
