#include <stdio.h>

int main()
{
	int sum = 0, x, status;
	while ((status = scanf("%d", &x)) == 1)
		sum += x;
	if (status == EOF) {
		printf("%d\n", sum);
		return (0);
	} else {
		fprintf(stderr, "add: non-numeric input\n");
		return (1);
	}
}
