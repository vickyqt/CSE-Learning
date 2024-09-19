#include <stdio.h>

void iinput(int *a, char *str)
{
    printf("Enter %s: ", str);
    scanf("%d", a);
}
char *charcopy(const char *src, int start, int end)
{
    int length = end - start + 1;
    char *subStr = (char *)malloc(length + 1);
    strncpy(subStr, src + start, length);
    subStr[length] = '\0';
    return subStr;
}