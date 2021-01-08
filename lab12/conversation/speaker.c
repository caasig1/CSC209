#include <stdio.h>
#include "wordlist.h"
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
	int fd;
	fd = open("/dev/urandom", O_RDONLY);
	if (fd < 0){
		perror("/dev/urandom");
		exit(1);
	}
	unsigned char r;
	for (int i = 0; i < 10; i++){
		if ((read(fd, &r, 1)) != 1) {
			perror("read");
			exit(1);
		}
		fflush(stdout);
		printf("%s\n", wordlist[r % wordlistsize]);
		sleep(1);
	}
}
