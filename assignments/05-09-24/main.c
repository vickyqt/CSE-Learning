#include "../../utils/utilio.c"
#include <stdio.h>
int main()
{
    // maxBetweenTwoNum()
    // checkEvenOrOdd()
    // leapYear()
    // maxBetweenThreeNum()
    // divisibleBy5and11()
    // checkEvenOrOdd()
}
void maxBetweenTwoNum()
{
    int a, b;
    iinput(&a, "A");
    iinput(&b, "B");
    if (a > b)
        printf("A is Max");
    else
        printf("B is Max");
}
void checkEvenOrOdd()
{
    int a;
    iinput(&a, "A");
    if (a % 2 == 0)
        printf("A is Even");
    else
        printf("A is Odd");
}
void maxBetweenThreeNum()
{
    int a, b, c;
    iinput(&a, "A");
    iinput(&b, "B");
    iinput(&c, "C");
    if (a >= b && a >= c)
        printf("A is Max");
    if (b >= a && b >= a)
        printf("B is Max");
    else
        printf("C is Max");
}
void divisibleBy5and11()
{
    int a;
    iinput(&a, "A");

    if (a % 5 == 0 && a % 11 == 0)
        printf("A is Divisible by 5 and 11");
    printf("A is not Divisible by 5 and/or 11");
}
void leapYear()
{
    int a;
    iinput(&a, "a Year");

    if (a % 4 == 0 && a % 400 == 0)
        printf("%d is a Leap Year", a);
    else
        printf("%d is not a Leap Year", a);
}