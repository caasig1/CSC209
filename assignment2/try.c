#include <stdio.h>
#include <stdlib.h>  /* for atoi() */
#include <unistd.h>  /* for getopt() */

static char *progname;
static int xflag = 0, count = 12;  /* i.e. default is no x, and -c 12 */


int main(int argc, char **argv)
{
    int c, status = 0;

    progname = argv[0];

    while ((c = getopt(argc, argv, "c:x:")) != EOF) {
	switch (c) {
	case 'c':
	    count = atoi(optarg);
	    break;
	case 'x':
	    xflag = atoi(optarg);
	    break;
	case '?':
	default:
	    status = 1;
	    break;
	}
    }

    if (status) {
	fprintf(stderr, "usage: %s [-c count] [-x] [name ...]\n", progname);
	return(status);
    }

    printf("Command-line options:\n");
    printf("    count is %d.\n", count);
    printf("    'x' flag is %d.\n", xflag);

    if (optind == argc) {
	printf("and there are no further arguments.\n");
    } else {
	for (; optind < argc; optind++) {
	    printf("arg %s\n", argv[optind]);
	}
    }
    return(status);
}
