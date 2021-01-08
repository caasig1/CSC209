#include <stdio.h>

int main(int argc, char **argv){
	FILE *ifp, *ofp;
	int c;

	if ((ifp = fopen("foo", "r")) == NULL) {
		perror("foo");
		return 1;
	}
	if ((ofp = fopen("bar", "w")) == NULL) {
        	perror("bar");
        	return 1;
	}

	while ((c = getc(ifp)) != EOF) {
		putc(c, ofp);
	}
	return 0;
}

