#include <stdio.h>

int main()
{
    int a[10];
    int size;
    extern int fillarray(int *a, int maxsize);
    extern void sortarray(int *a, int size);
    extern void printarray(int *a, int size);

    size = fillarray(a, 10);
    sortarray(a, size);
    printarray(a, size);
    return(0);
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

void sortarray(int *a, int size){
    int indicator = 0;
    //OR USE 2 FOR LOOPS!!!
    while (indicator == 0) {
	indicator = 1;
	int pointer = 0;
	while (pointer < size){
		if (a[pointer] > a[pointer + 1]){
			int temp = a[pointer];
			a[pointer] = a[pointer + 1];
		       a[pointer + 1] = temp;	
			indicator = 0;
		}
		pointer++;
	}
    }
}

void printarray(int *a, int size)
{
    int i;
    for (i = 0; i < size; i++)
	printf("%d\n", a[i]);
}
