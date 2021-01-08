#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <stdlib.h>

extern char **environ;

int main(int argc, char **argv){
	int ops = (argc - 1)* 2;
	for (int i = 0; i < ops; i++){
		int current = i + 1;
		if (i > argc - 2) {
			current = i - argc + 2;
		}
		char *location = NULL;
		int argvLen = strlen( argv[current] );
		location = malloc(2 + argvLen);
		if (argv[current][0] != '/'){
			strcpy(location, "./");
			strcat(location, argv[current]);
		} else {
			strcat(location, argv[current]);
		}
		char **newarg = NULL;
		int argLen = strlen( location ) + 1;
		newarg = malloc(argLen);
		newarg[0] = argv[current];
		int x = fork();
        	if (x == -1){
                	perror("fork");
                	return 1;
        	} else if (x == 0){
                	/*child*/
			execve(location, newarg, environ);
                	perror(location);
                	return 1;
		} else {
			int status;
			if (wait(&status) < 0){
                                perror("wait");
                                exit(1);
                        }
		}
		/*parent continues*/
		free(location);
	}
	return 0;
}
