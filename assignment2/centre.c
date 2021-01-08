#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

// Great listen while you grade! Have a nice day :)
// https://www.youtube.com/watch?v=Sq76DhIjtWQ
static char *progname;
static int width = 80;
static char *chr = " ";
static int indicator = 0;
void set(char *line);

int main(int argc, char **argv)
{
    int c, status = 0;

    progname = argv[0];

    // Getopt while loop
    while ((c = getopt(argc, argv, "c:w:")) != EOF) {
	switch (c) {
	case 'c':
	    chr = optarg;
	    chr[1] = '\0';
	    indicator = 1;
	    break;
	case 'w':    
	    width = atoi(optarg);
	    if (width > 500){
		perror("maximum exceeded");
	    }
	    break;
	case '?':
	default:
	    status = 1;
	    break;
	}
    }

    if (status) {
	fprintf(stderr, "usage: %s [-c] [character] [-w] [width maximum 500]\n", progname);
	return(status);
    }

    // Checks for the correct input (stdin or files) 
    int max = 500;
    char *line = malloc(max + 1); // The maximum count is 500, so 501 would be '\0'	
    memset(line, 0, max);
    if (optind == argc) {
         while (fgets(line, max, stdin) != NULL){
		if (line[width] == '\0' || line[width] == '\n'){
			set(line);
		}
                printf("%s", line);
	 	memset(line, 0, max);
	 }
    } else {
	FILE *files;    
	// Each file gets checked
	for (; optind < argc; optind++) {
	    	files = fopen(argv[optind], "r");
		if (files == NULL){
			perror(argv[optind]);
			return 1;
		}
		while (fgets(line, max, files) != NULL){
			if (line[width] == '\0' || line[width] == '\n') {
				set(line);
			}
			printf("%s", line);
			memset(line, 0, max);
		}	
	}
    }
    return(status);
}    

// Set the characters in the array correctly
void set(char *line){
	int counter = 0;
	char *end = "\n";
	while (line[counter] != '\0' && line[counter] != '\n'){
		counter++;
	}
	int right = width - counter - (width - counter) / 2;
	int i = 0;

	// values to the right of string/line
	if (indicator) {
		line[width] = *end;
		while (i < right){
			line[width - i - 1] = chr[0];
			i++;
		}
	} else {
		line[width - right] = *end;
		i = right;
	}

	// values of the string/line
	while (counter > 0){
		line[width - i - 1] = line[counter - 1];
		i++;
		counter--;
	}

	// values to the left of the string/line
	while (i <= width){
		line[width - i - 1] = chr[0];
		i++;
	}
}
