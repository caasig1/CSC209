#include <stdio.h>

void counter(FILE *file, char *name);

int main(int argc, char **argv){
	int status;
	status = 0;
	if (argc >= 2){
		for (int i = 1; i < argc; i++){
			FILE *file;
			if ((file = fopen(argv[i], "r")) == NULL) {
				perror(argv[i]);
				status = 1;
			}
			counter(file, argv[i]);
			fclose(file);
		}
	} else {
		//use std in
		counter(stdin, NULL);
	}
	return status;
}

void counter(FILE *file, char *name){
    int c, counter;
    counter = 0;
    while ((c = getc(file)) != EOF){
        if (c == '\n') {
            counter++;
        }
    }
    if (name == NULL) {
// do something else
    } else {
	    printf("%d %s\n", counter, name);

    }
}
