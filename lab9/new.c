#include <stdio.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

int main(){
    // open file 8.out for writing
    FILE *file;
    file = fopen("8.out", "w");
    if (file == NULL){
        perror("8.out");
        return 1;
    }
    // dup2 the 8.out fileno to 8
    int filenum = fileno(file);
    dup2(fileno(stdout), filenum);
    // close the old fileno
    close(fileno(stdout));
    // set output to 8 dup2(1, 8)
    dup2(filenum, 8);
    // close stdout
    close(filenum);
    // execute program
    execl("./hello", "hello", (char *)NULL);
    // error check
    perror("/usr/betty/boo");
    return 1;
}
