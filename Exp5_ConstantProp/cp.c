#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>

struct Expression {
    char operator[2];
    char operand1[5];
    char operand2[5];
    char result[5];
    int isEvaluated;
};
int count;
void inputExpressions(struct Expression arr[], int count);
void constantFolding(struct Expression arr[], int count);
void optimizeOutput(struct Expression arr[], int count);
void updateOperands(struct Expression arr[], int index, char *resultValue);

int main() {

    printf("\nEnter the maximum number of expressions: ");
    scanf("%d", &count);

    struct Expression expressions[count];
    inputExpressions(expressions, count);

    constantFolding(expressions, count);
    
    optimizeOutput(expressions, count);

    return 0;
}

void inputExpressions(struct Expression arr[], int count) {
    printf("\nEnter the expressions (operator operand1 operand2 result):\n");
    for (int i = 0; i < count; i++) {
        scanf("%s %s %s %s", arr[i].operator, arr[i].operand1, arr[i].operand2, arr[i].result);
        arr[i].isEvaluated = 0;
    }
}

void constantFolding(struct Expression arr[], int count) {
    int operand1, operand2, result;
    char operator;
    char resultStr[5];

    for (int i = 0; i < count; i++) {
        if (isdigit(arr[i].operand1[0]) && isdigit(arr[i].operand2[0]) || strcmp(arr[i].operator, "=") == 0) {
            operand1 = atoi(arr[i].operand1);
            operand2 = atoi(arr[i].operand2);
            operator = arr[i].operator[0];

            switch (operator) {
                case '+':
                    result = operand1 + operand2;
                    break;
                case '-':
                    result = operand1 - operand2;
                    break;
                case '*':
                    result = operand1 * operand2;
                    break;
                case '/':
                    result = operand1 / operand2;
                    break;
                case '=':
                    result = operand1;
                    break;
            }
            
            sprintf(resultStr, "%d", result);
            arr[i].isEvaluated = 1;
            updateOperands(arr, i, resultStr);
        }
    }
}

void updateOperands(struct Expression arr[], int index, char *resultValue) {
    for (int i = index + 1; i < count; i++) {
        if (strcmp(arr[index].result, arr[i].operand1) == 0)
            strcpy(arr[i].operand1, resultValue);
        else if (strcmp(arr[index].result, arr[i].operand2) == 0)
            strcpy(arr[i].operand2, resultValue);
    }
}

void optimizeOutput(struct Expression arr[], int count) {
    printf("\nOptimized code is:\n");
    for (int i = 0; i < count; i++) {
        if (!arr[i].isEvaluated || arr[i].isEvaluated) {
            printf("%s %s %s %s\n", arr[i].operator, arr[i].operand1, arr[i].operand2, arr[i].result);
        }
    }
}


// = 3 - z
// * z 4 a
// = 12 - b
// + a b c