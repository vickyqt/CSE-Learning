#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "../utils/utilio.c" 

char *calculateString(char str[])
{
    char *ptr = str;
    char opts[50];
    int numbers[50];
    int index = 0;
    int index2 = 0;

    // Separate numbers and operations
    while (*ptr != '\0')
    {
        if (isdigit(*ptr) || 
            (*ptr == '-' && (ptr == str || !isdigit(*(ptr - 1)) && *(ptr - 1) != ')') && isdigit(*(ptr + 1))))
        {
            numbers[index] = strtol(ptr, &ptr, 10);
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
    sprintf(result, "%d", numbers[0]);

    return result;
}

void calculator()
{
    const int MAX_BUFFER = 300;
    char inp[MAX_BUFFER];
    char calc[MAX_BUFFER];

    printf("Enter a Math Problem: ");
    if (scanf("%299s", inp) != 1)
    {
        printf("Invalid input.\n");
        return;
    }

    if (strcmp(inp, "exit") == 0)
    {
        exit(0);
    }

    strncpy(calc, inp, MAX_BUFFER);

    int latest_bkt = -1;
    int bktArray[10];

    for (int z = 0; z < 10; z++)
    {
        int bkt_index = -1;

        // Search for closing brackets and match with opening brackets
        for (int i = strlen(inp) - 1; i >= 0; i--)
        {
            char c = inp[i];

            if (c == ')')
            {
                bkt_index = i;
            }
            else if (c == '(' && bkt_index != -1)
            {
                char *subExpr = charcopy(inp, i + 1, bkt_index - 1);

                char *result = calculateString(subExpr);
                free(subExpr);

                char temp[MAX_BUFFER];
                strncpy(temp, inp, i);
                temp[i] = '\0';
                strcat(temp, result);
                strcat(temp, inp + bkt_index + 1);
                free(result);

                strncpy(calc, temp, MAX_BUFFER);
                break;
            }
        }

        strncpy(inp, calc, MAX_BUFFER);

        if (bkt_index == -1)
        {
            char *finalResult = calculateString(inp);
            printf("Result: %s\n", finalResult);
            free(finalResult);
            break;
        }
    }
}

int main()
{
    printf("=========================================\n");
    printf("       WELCOME TO THE CALCULATOR!\n");
    printf("=========================================\n");
    printf("  Enter your expression and get results!\n");
    printf("       Supports +, -, *, /, ^, ( )\n");
    printf("  Type 'exit' to terminate the program.\n");
    printf("=========================================\n");

    while (1)
    {
        calculator();
    }

    return 0;
}
