#include <stdio.h>
#include <unistd.h>

int main()
{
    int pipefd[2];

    if (pipe(pipefd)) {
        perror("pipe");
        return(1);
    }
    switch (fork()) {
    case -1:
        perror("fork");
        return(1);
    case 0:
        /* child */
        printf("I am the child.  FEED ME\n");
        char buf[20];
	int len;
	if ((len = read(pipefd[0], buf, sizeof buf - 1)) > 0) {
		perror("read");
		return 1;
	}
        buf[len] = '\0';
	printf("Parent says '%s'\n", buf);
        return(0);
    default:
        /* parent */
        printf("I am the parent.  Have some data.\n");
	if (write(pipefd[1], "something", 9) != 9){
		perror("write");
		return 1;
	}
        return(0);
    }
}
