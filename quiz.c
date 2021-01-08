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
		// read from stdin = read from pipe
		// redirect whatever is being read from pipe[0] to stdin -- now can read from both
		if ((dup2(fd[0], fileno(stdin))) == -1) {
                        perror("dup2");
                        exit(1);
                }

		// does not write to pipe so close fd[1]
		if ((close(fd[1])) == -1){
                        perror("close");
                }
/*
		// close fd[0] now that we are using stdin
		if ((close(fd[0])) == -1){
                        perror("close");
                }
*/
		//execl("/usr/bin/tr", "tr", "e", "f", (char *)NULL);
		fprintf(stderr, "Error: exec does not return"); 

	} else if (r == 0) { // child will run uniq
		// writing to stdout = writing to pipe 
		// redirect whatever is printed (in stdout) to pipe fd[1] -- now it is writing to both
		if ((dup2(fd[1], fileno(stdout))) == -1) {
			perror("dup2");
			exit(1);
		}
		
		// Does not read from pipe
		if ((close(fd[0])) == -1){
			perror("close");
		}

		// Do not need fd[1] because we use stdout
		if ((close(fd[1])) == -1){
                        perror("close");
                }
		printf("hello\n");
	} else {
		perror("fork");
		exit(1);
	}
	unsigned char c[10];
        read(fd[0], c, 10);
		for (int i = 0; i < 10; i++){
			printf("%cj", c[i]);
		}
	
        
	return 0;
}
