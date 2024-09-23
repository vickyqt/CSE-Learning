#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "../utils/utilio.c"
const int MAX_BUFFER = 400;

char *calculateExpression(char str[])
{
    char *ptr = str;
    char opts[50];
    double numbers[50];
    int index = 0;
    int index2 = 0;

    // Separate numbers and operations
    while (*ptr != '\0')
    {
        if (isdigit(*ptr) ||
            ((*ptr == '-' || *ptr == '.') && (ptr == str || !isdigit(*(ptr - 1)) && *(ptr - 1) != ')') && (isdigit(*(ptr + 1)) || *(ptr + 1) == '.')))
        {
            numbers[index] = strtod(ptr, &ptr);
            index++;
        }
        else
        {
            opts[index2] = *ptr;
            index2++;
            ptr++;
        }
    }

    opts[index2] = '\0';

    // Perform exponentiation first
    for (int i = 0; i < index2; i++)
    {
        if (opts[i] == '^')
        {
            numbers[i] = (int)pow(numbers[i], numbers[i + 1]);

            for (int j = i + 1; j < index - 1; j++)
                numbers[j] = numbers[j + 1];

            for (int j = i; j < index2 - 1; j++)
                opts[j] = opts[j + 1];

            index--;
            index2--;
            i--; // Check the same position again after shifting
        }
    }

    // Perform division and multiplication first
    for (int i = 0; i < index2; i++)
    {
        if (opts[i] == '/' || opts[i] == '*')
        {
            if (opts[i] == '/')
                numbers[i] = numbers[i] / numbers[i + 1];
            else if (opts[i] == '*')
                numbers[i] = numbers[i] * numbers[i + 1];

            for (int j = i + 1; j < index - 1; j++)
                numbers[j] = numbers[j + 1];

            for (int j = i; j < index2 - 1; j++)
                opts[j] = opts[j + 1];

            index--;
            index2--;
            i--; // Check the same position again after shifting
        }
    }

    // Then perform addition and subtraction
    for (int i = 0; i < index2; i++)
    {
        if (opts[i] == '+' || opts[i] == '-')
        {
            if (opts[i] == '+')
                numbers[i] = numbers[i] + numbers[i + 1];
            else if (opts[i] == '-')
                numbers[i] = numbers[i] - numbers[i + 1];

            for (int j = i + 1; j < index - 1; j++)
                numbers[j] = numbers[j + 1];

            for (int j = i; j < index2 - 1; j++)
                opts[j] = opts[j + 1];

            index--;
            index2--;
            i--; // Check the same position again after shifting
        }
    }

    char *result = (char *)malloc(20 * sizeof(char));
    sprintf(result, "%.3f", numbers[0]);

    return result;
}

void calculator()
{

    char inp[MAX_BUFFER];
    char calc[MAX_BUFFER];

    printf("Enter a Math Problem: ");
    if (scanf("%399s", inp) != 1)
    {
        printf("\nInvalid input.\n");
        return;
    }

    if (strcmp(inp, "exit") == 0)
    {
        exit(0);
    }

    strncpy(calc, inp, MAX_BUFFER);

    int bkt_index = -1;
    do
    {

        bkt_index = -1;
        for (int i = 0; i < strlen(inp); i++)
        {
            char c = inp[i];
            if (c == '(')
            {
                bkt_index = i;
            }
            else if (c == ')' && bkt_index != -1)
            {
                char *subExpr = charcopy(inp, bkt_index + 1, i - 1);
                char *result = calculateExpression(subExpr);
                free(subExpr);
                strncpy(calc, inp, bkt_index);
                calc[bkt_index] = '\0';
                if (bkt_index > 0 && isdigit(inp[bkt_index - 1]))
                {
                    strcat(calc, "*");
                }
                strcat(calc, result);
                if (strlen(inp) > i && isdigit(inp[i + 1]))
                {
                    strcat(calc, "*");
                }
                strcat(calc, inp + i + 1);
                free(result);
                strncpy(inp, calc, MAX_BUFFER);
                break;
            }
        }
    } while (bkt_index != -1);
    char *finalResult = calculateExpression(inp);
    printf("Result: %s\n", finalResult);
    free(finalResult);
}

int main()
{
    printf("=========================================\n");
    printf("       WELCOME TO THE CALCULATOR!\n");
    printf("=========================================\n");
    printf("  Enter your expression and get results!\n");
    printf("       Supports +, -, *, /, ^, ( )\n");
    printf("          Floating Precision: 3\n");
    printf("  Type 'exit' to terminate the program.\n");
    printf("=========================================\n");

    while (1)
    {
        calculator();
    }

    return 0;
}
