#include <stdio.h>
#include "parse.h"

int laststatus = 0;

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
        // find the path to program, if first char in argv[0] is / then use it, other wise look in /bin then /usr/bin then in the cd (in that order) -- check "./" and stuff like that
                // check if it exists with stat and not opendir
                // error msg  "%s: Command not found\n"
                // if / then just use that as pathname
        // argv has no argc and ends with NULL pointer
        char *path = argv[0];
        struct stat file;
        if (path[0] != "/"){
                // if lstat("path", &file); checks if it exists
                char bin[1000] = "/bin/";
                char usr[1000] = "/usr/bin/";
                char cd[1000] = "./";
                strcat(bin, path);
                strcat(usr, path);
                strcat(cd, path);
                if (!(lstat(bin, &file))) { //check bin
                        path = bin;
                        //set pathname to with /bin/...
                } else if (!(lstat(usr, &file))) {
                        path = usr; 
                        //set pathname to with /usr/bin/...
                } else if (!(lstat(cd, &file))) { //check current dir
                        path = cd;
                        //set pathname to ./...
                } else {// error
                        perror(path);
                        exit(1);
                }
        }       
        printf("%
        // execve 
                // third arg is environ: use "extern char **environ;"
                // int execve(const char *pathname, char *const argv[], char *const envp[]);
        // if the exit status is non-zero, output "exit status %d" -- nothing if it is 0 -- assign it to global variable laststatus
        // 
}

