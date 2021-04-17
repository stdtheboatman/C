#include <stdio.h>

#include <malloc.h>

int strSize(char *str) {
    char *yk = str;
    int size = 0;

    while(*yk) {
        size++;
        yk = yk + 1;
    }

    return size;
}

void readStringIgnoreSpace(char *str) {
    int i = 0;

    char sym;
    while((sym = getchar()) != '\n') {
        if (sym != ' ') {
            str[i++] = sym;
        }
    }

    str[i] = '\0';
}

char operators[] = "-+*/\0";

int isOperator(char sym) {
    for(int i = 0; i < strSize(operators); i++) {
        if (operators[i] == sym) {
            return 1;
        }
    }

    return 0;
}

int isDigit(char sym) {
    return ('0' <= sym && sym <= '9');
}

int isCorrectExpression(char *expresion) {
    for(int i = 0; i < strSize(expresion) - 1; i++) {
        if (isOperator(expresion[i]) && isOperator(expresion[i + 1])) {
            return 0;
        }
    }

    for(int i = 0; i < strSize(expresion); i++) {
        if (!isOperator(expresion[i]) && !isDigit(expresion[i])) {
            return 0;
        }
    }

    if (strSize(expresion)) {
        if (expresion[0] == '*' || expresion[0] == '/') {
            return 0;
        }

        if (isOperator(expresion[strSize(expresion) - 1])) {
            return 0;
        }
    }

    return 1;
}

int main() {
    char *expression = malloc(1024 * sizeof(char));

    printf("Enter expression\n");
    readStringIgnoreSpace(expression);

    if (isCorrectExpression(expression)) {
        printf("Expression is correct\n");

        double valueStack[1024];
        char operatorStack[1024];

        int ykValue = 0;
        int ykOperator = 0;

        valueStack[ykValue] = 0.;
        operatorStack[ykOperator++] = '+';

        if (strSize(expression) && expression[0] == '-') {
            ykOperator = 0;
        }

        for(int i = 0; i < strSize(expression); i++) {
            if (isDigit(expression[i])) {
                int number = 0;
                while(i < strSize(expression) && isDigit(expression[i])) {
                    number = number * 10 + (expression[i] - '0');
                    i++;
                }
                i--;

                char lastOperator = operatorStack[ykOperator - 1];
                if (lastOperator == '*') {
                    valueStack[ykValue - 1] *= number;
                    ykOperator--;
                }
                else if (lastOperator == '/') {
                    valueStack[ykValue - 1] /= number;
                    ykOperator--;
                }
                else {
                    valueStack[ykValue++] = number;
                }

            }
            else {
                operatorStack[ykOperator++] = expression[i];
            }
        }

        double result = 0;
        while(--ykValue > -1) {
            char operator = operatorStack[--ykOperator];

            if (operator == '+') {
                result += valueStack[ykValue];
            }
            else {
                result -= valueStack[ykValue];
            }
        }

        printf("result of %s is %f\n", expression, result);
    }
    else {
        printf("Expression isn`t correct\n");
    }

    free(expression);
    return 0;
}
