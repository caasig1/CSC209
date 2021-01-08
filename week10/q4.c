#include <stdio.h>

#define i 3;
// 3; is used, not 3
int main()
{
    int j = i - 2;// j = 3; - 2;
    printf("%d\n", j);
    return(0);
}
