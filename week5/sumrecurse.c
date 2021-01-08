#include <stdio.h>

int main()
{
    int a[10];
    int size;
    extern int fillarray(int *a, int maxsize);
    extern int sumarray(int *a, int size);

    size = fillarray(a, 10);
    printf("%d\n", sumarray(a, size));
    return(0);
}


int sumarray(int *a, int size){
	if (size == 0) {
		return 0;
	} else if (size == 1) {
		return a[0];
	} else {
		int sum = a[0];
		sum += sumarray(a + 1, size - 1);
		return sum;
	}
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
