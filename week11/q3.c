#include <stdio.h>
#include <sys/file.h>

int main(int argc, char **argv){
	FILE *fp = fopen("output",  "w");
	int i;

	// if seek is first instead of lock:
	// will see that only 1 or only 2
	// why? fseek does nothing -- were at the beginning of a file of zero size
	// other case, we did lock and when had control, we seek to the end
	 
	// locking is just lock the file, can write from elsewhere?
	if (flock(fileno(fp), LOCK_EX))
		perror("output");
	// fseek is after flock returned, blocks if someone else already has the lock
	if (fseek(fp, 0, SEEK_END))
		perror("output");
	// seek to the end

	for (i = 0; i<200000; i++)
		fprintf(fp, "%s\n", argv[1]);
	return 0;

}
