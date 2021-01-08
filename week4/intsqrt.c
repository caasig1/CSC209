#include <stdio.h>
int main()
{
	int i, high, low, guess;
	scanf("%d",&i);
	high = i+1;
	low = 0;
	while (high > low + 1) {
		guess = (low + high) / 2;
		if (guess * guess > i)
			high = guess;
		else
			low = guess;
	}
	printf("%d\n", low);
	return (0);
}
