#include <stdio.h>
#include <sys/file.h>

int main(int argc, char **argv){
	FILE *fp = fopen("output",  "w");
	int i;

	if (flock(fileno(fp), LOCK_EX))
		perror("output");

	for (i = 0; i<200000; i++)
		fprintf(fp, "%s\n", argv[1]);
	return 0;

}
