#include "gcd.h"
#include <stdio.h>

int main()
{
    int i;
    extern int gcd(int x, int y);

    for (i = 0; i < 20; i++)
        printf("gcd of 12 and %d is %d\n", i, gcd(12, i));
    return(0);
}
//gcc -Wall testgcd.c gcd.c
