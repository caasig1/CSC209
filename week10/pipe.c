#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>

// equal to: sort <file1 | uniq

int main(){
	int fd[2], r;

	//create pipe
	if ((pipe(fd)) == -1){
		perror("pipe");
		exit(1);
	}

	if ((r = fork()) > 0) { //parent will run sort
		// set up the redirection from file1 to stdin
		int filedes = open("file1", O_RDONLY);

		// reset stdin so that read from stdin comes from the file
		if ((dup2(filedes, fileno(stdin))) == -1) {
			perror("dup2");
			exit(1);
		}

		// reset stdout so that when we write to stdout it goes to the pipe
		if ((dup2(fd[1], fileno(stdout))) == -1){
			perror("dup2");
			exit(1);
		}

		// parent wont be reading from pipe
		if ((close(fd[0])) == -1){
			perror("close");
		}

		// because writes go to stdout, no one should write to f[1]
		if ((close(fd[1])) == -1){
			perror("close");
		}

		// we wont be using filedes directly, so close it
		if ((close(filedes)) == -1){
			perror("close");
		}

		execl("/usr/bin/sort", "sort", (char *)NULL);
		fprintf(stderr, "Error: exec should not return \n");
	} else if (r == 0) { // child will run uniq
		// reset stdin so that it reads from the pipe
		if ((dup2(fd[0], fileno(stdin))) == -1){
			perror("dup2");
			exit(1);
		}
		// this process will never write to the pipe
		if  ((close(fd[1])) == -1){
			perror("close");
		}
		// since we reset stdin to read from the pipe, we dont need fd[0]
		if ((close(fd[0])) == -1) {
			perror("close");
		}
		execl("/usr/bin/uniq", "uniq", (char *)NULL);
		fprintf(stderr, "Error: exec should not return \n");
	} else {
		perror("fork");
		exit(1);
	}
	return 0;
}
