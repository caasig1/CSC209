#include <stdio.h>

int main() {
	FILE *sum;
	sum = fopen("/u/csc209h/summer/pub/ex/05/t3", "r");
	if (sum == NULL) {
		//fprintf(stderr, "Error opening input file\n");
		perror("/u/csc209h/summer/pub/ex/05/t3");
		return 1;
	}
	
	int total = 0;
	int number;
	while (fscanf(sum, "%d", &number) == 1){
		total += number;
	}
	printf("%d\n", total);

	return 0;
}
