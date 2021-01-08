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
				// close 1 and then open it , it will choose the smallest, which is 1 (standard input)
				// open the filename and then do the other things below
				// This way anything usually going to stout goes to this now
				// open(filename, O_WRONLY|_CREAT|O_TRUNC, 0666) < 0 (negative is error)
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
