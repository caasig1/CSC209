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
		int fd;
		// can assume everything opens with 0 1 2 files (stdin stdout stderr) -- also assume it opens to lowest number
		// when 1 is closed, open will give us file descriptor 1 if it works
		if (fd = open("file", O_WRONGLY|O_CREAT|O_TRUNC, 0666) < 0){
			// -1 if error
			// write only, create if not exists, truncate it to size 0
			perror("file");
			return 1;
		}
		dup2(fd, 1); // set fd to 1, kind of like an alias -- dont wanna duplicate here, want to renumber!!!
		// like cp, then rm instead of jsut mv
		close(fd);
		// close 3, now that it is duped into 1
		execl("/bin/ls", "ls", (char *)NULL);
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
