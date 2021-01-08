#include <stdio.h>

int main(int argc, char **argv)
{
    FILE *fp;
    char c;

    if (argc < 2){
        fprintf(stderr, "missing file name\n");
	return (1);
    }

    for (int i = 1; i < argc; i++){
	    if ((fp = fopen(argv[i], "r")) == NULL){
		perror(argv[i]);
		return (1);
    	}

   	while ((c = getc(fp)) > 0)
    	    putchar(c);

    	fclose(fp);
    }

    return (0);
}
/* Errors:
 * 1) incorrect error message/location and no return upon error for argc checking
 * 2) does not handle cases of multiple files like cat
 * 3) incorrect return at the end status
 * 4) file open not error checked
 * 5) file would work if it can be read, does not need to be written to
 * */
