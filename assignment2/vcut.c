#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char **argv){
	if(argc < 2){
		perror("usage: vcut spec [file ...]");
		return 1;
	}
	char *nums = argv[1];
	int checker_size = 100;
	int *checker = malloc(sizeof(int) * checker_size);
	memset(checker, 0, checker_size);
	char *pointer = nums;

	// Check that the first item is a digit
	if (!isdigit(*pointer)){
		fprintf(stderr, "vcut: unexpected character '%c' in spec \"%s\"\n", *pointer, argv[1]);
                return 1;
	}
	// Loop through argv[1] string
	while(*pointer) {
		int index = atoi(pointer);
                checker[index] = 1;
                pointer++;
		// Increment pointer to next non-digit
		while (isdigit(*pointer)){
			pointer ++;
		}
		// Single numbers
		if (*pointer == ','){
			pointer++;
			checker[index] = 1;
		// Hyphened numbers
		} else if(*pointer == '-'){
			pointer++;
			int second = atoi(pointer);
			if (index < second){
				while (index < second){
					checker[index] = 1;
					index++;
				}
			} else {
				while (index > second){
					checker[index] = 1;
					index--;
				}
			}
		// Check that everything is either a digit or ',' or '-'
		// Error message output is same as compiled code given
		} else if(*pointer != '\0' && *pointer != '\n') {
			fprintf(stderr, "vcut: unexpected character '%c' in spec \"%s\"\n", *pointer, argv[1]);
			return 1;
		}
	}
	// Standard input
	if (argc == 2) {
		int line_number = 1;
		char c;
		while ((c = fgetc(stdin)) != EOF){
			// If we want to keep
			if (checker[line_number]){
				printf("%c", c);
			}
			// Method for line counting
			if (c == '\n') {
				line_number++;
			}
		}
	// Files (1 or many)
	} else {
		FILE *files;
		for (int args = 2; args < argc; args++){
			files = fopen(argv[args], "r");
			// Error checking
			if (files == NULL) {
				perror(argv[args]);
				return 1;
			}
			int line_number = 1;
        	        char c;
                	while ((c = fgetc(files)) != EOF && line_number < 100){
                        	// If we want to keep
				if (checker[line_number]){
					printf("%c", c);
                        	}
				// Method for line counting
                        	if (c == '\n') {
                                	line_number++;
                        	}
                	}
		}
	}
	free(checker);
	return 0;
}
