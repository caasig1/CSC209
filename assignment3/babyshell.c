#include <stdio.h>
#include "parse.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include<sys/wait.h>

int laststatus = 0;
extern char **environ;
int main()
{
    char buf[1000], **p;
    extern void execute(char **argv);

    while (printf("$ "), fgets(buf, sizeof buf, stdin))
        if ((p = parse(buf)))
            execute(p);

    return(laststatus);
}

void execute(char **argv){
        char *path = argv[0];
        struct stat file;

	int indicate = 1;
	for (int i = 0; i < sizeof(path); i++) {
		if (path[i] == '/'){
			indicate = 0;
		}
	}

        if (indicate){
                char bin[1000] = "/bin/";
                char usr[1000] = "/usr/bin/";
                char cd[1000] = "./";
                strcat(bin, path);
                strcat(usr, path);
                strcat(cd, path);
                if (!(lstat(bin, &file))) {
                        path = bin;
                } else if (!(lstat(usr, &file))) {
                        path = usr;
		} else if (!(lstat(cd, &file))) {        
			path = cd;
                } else {
                       fprintf(stderr, "%s: Command not found\n", path);
                	return;
		}
        }

        argv[0] = path;
        int status;
        switch (fork()) {
                case -1:
                        perror("fork");
                        exit(1);
                case 0:
                        /* child */
                        execve(path, argv, environ);
                        perror(path);
			exit(127);
                default:
			/* parent */
                        if (wait(&status) < 0){
                                perror("wait");
                                exit(1);
                        }
                        
        		if (WIFEXITED(status)){
				int exitstat = WEXITSTATUS(status);
				laststatus = exitstat;
				
				if (exitstat) {
                                	fprintf(stderr, "exit status %d\n", exitstat);
                        	}
			}
		}
}
