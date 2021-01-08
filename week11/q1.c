#include <stdio.h>

int main(int argc, char **argv){
	FILE *fp = fopen("output",  "w");
	int i;
	for (i = 0; i<10000; i++)
		fprintf(fp, "%s\n", argv[1]);
	return 0;

}
