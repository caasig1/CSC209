#include <stdio.h>

int main(int argc, char **argv)
{
    int c;
    if (argc > 2){
	perror("too mayn arguments error");
	return 1;
    }
    if (argc = 2) {
	    FILE *file;
	    file = fopen(argv[1], "r");
	    if (file == NULL) {
		perror(argv[1]);
		return 1;
	    }
	process(file);
    } else {
	process(stdin);
    }
    return 0;
}
   // can set file = stdin 
void process(FILE file){
    while ((c = getc(file)) != EOF) {
	if ((c >= 'a' && c <= 'm') || (c >= 'A' && c <= 'M'))
	    putchar(c + 13);
	else if ((c >= 'n' && c <= 'z') || (c >= 'N' && c <= 'Z'))
	    putchar(c - 13);
	else
	    putchar(c);
    }
}
