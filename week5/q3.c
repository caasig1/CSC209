#include <stdio.h>

int main()
{
    int a[10];
    int size;
    int *p;
    extern int fillarray(int *a, int maxsize);
    extern int * search(int *a, int size, int search);

    size = fillarray(a, 10);
    if ((p = search(a, size, 5)))
        printf("%d\n", *p);
    else
        printf("not found\n");
    return(0);
}

int * search(int *a, int size, int search) {
    int i=0;
    while (i < size) {
        if (a[i] == search) {
	    return a + i;
	}
	i++; 
    }
    return NULL;
}

int fillarray(int *a, int spaceleft)
{
    int n = 0;
    while (spaceleft > 0 && scanf("%d", a) == 1) {
        a++;
        spaceleft--;
        n++;
    }
    return(n);
}
