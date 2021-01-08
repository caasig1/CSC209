#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(){
	int x = fork();
	if (x == -1){
		perror("fork");
		return 1;
	} else if (x == 0){
		/*child*/
		close (1);
		if (open("file", O_RDONGLY) < 0){
			// Read only
			perror("file");
			return 1;
		}
		execl("/bin/tr", "tr", "e", "f", (char *)NULL);
		perror("/bin/tr");
		return 1;
	} else {
		/*parent*/
		int status, pid;
		pid = wait(&status);
		printf("pid %d exit status %d\n", pid, WEXITSTATUS(status));
		return 0;
	}
}
