#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

int main(){
	char buf[1000];
	int status;
	while (printf("$ "), fgets(buf, sizeof buf, stdin)){
		// sizeof char is 1 so no need to divide by sizeof char
		switch (fork()){
			case -1:
				perror("fork");
				return 1;
			case 0:
				/* child */
				execl("/bin/sh", "sh", "-c", buf, (char *)NULL);
				perror("/bin/sh/");
				return 127; // diff numbers can help so indicate where error is
			default:
				/* parent */
				if (wait(&status) < 0)
					perror("wait");
				else
					printf("exit status %d\n", WEXITSTATUS(status)); // in wait u can do this
		} 
	}
	return 0;
}
