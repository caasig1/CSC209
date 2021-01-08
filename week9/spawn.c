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
		execl("/bin/ls", "ls", (char *)NULL);
		//execl(path, argv[0], argv[1], ..., null character);
		// -> needs cast because NULL is int usually but we need character NULL = NEED (char *)NULL
		// execl fails when the args arent correct, like bad pathname or bad argv[0] (no such directory)
		// or maybe permission denied, or out of space
		// can see in man page
		perror("/bin/ls");
		return 1;
	} else {
		/*parent*/
		int status, pid;
		pid = wait(&status);
		printf("pid %d exit status %d\n", pid, WEXITSTATUS(status));
		return 0;
	}
}
