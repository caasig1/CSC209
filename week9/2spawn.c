#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

void docommand();

int main(){
	int x = fork();
	if (x == -1){
		perror("fork");
		return 1;
	} else if (x == 0){
		/*child*/
		docommand();
	} else {
		/*parent*/
		int status, pid;
		pid = wait(&status);
		printf("pid %d exit status %d\n", pid, WEXITSTATUS(status));
		return 0;
	}
}

void docommand() /*does not return, under any circumstances */ {
	int pipefd[2]; // array of 2 ints, one to first one to second
	if (pipe(pipefd)) {
		perror("pipe");
		exit(1);// to know where error is
	}

	switch (fork()) {
	case -1:
		perror("fork");
		exit(1);
	case 0:
		/*child */
		close(pipefd[0]);
		dup2(pipefd[1], 1);
		close(pipefd[1]);
		execl("/bin/ls", "ls", (char *)NULL);
		perror("/bin/ls");
		exit(1);
	default:
		/* parent */
		close(pipefd[1]);
		dup2(pipefd[0], 0);
		close(pipefd[0]);
		execl("/usr/bin/tr", "tr", "e", "f", (char *)NULL);
		perror("/usr/bin/tr");
		exit(1);
	}
}
