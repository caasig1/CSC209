#include <stdio.h>

int main() {
        FILE *file;
        file = fopen("count", "r");
        if (file == NULL) {
                fprintf(stderr, "Error opening input file\n");
                return 1;
        }
	
	int n;
	if (fscanf(file, "%d", &n) == 1){
		n++;
	}

	fclose(file);
	file = fopen("count", "w");
	fprintf(file, "%d\n", n);



        return 0;
}
