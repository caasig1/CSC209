#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main()
{
    char filename[20];
    int i, fd;

    for (i = 11; i > 2; i--) {
	snprintf(filename, sizeof filename, "file%02d", i);
	if ((fd = open(filename, O_WRONLY|O_CREAT|O_TRUNC, 0666)) < 0) {
	    perror(filename);
	    return(1);
	}
	dup2(fd, i);
	close(fd);
    }
    printf("%d\n", fileno(stdin));
    execl("helloer", "helloer", (char *)NULL);
    perror("helloer");
    return(1);
}
