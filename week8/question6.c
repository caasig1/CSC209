#include <stdio.h>
#include <unistd.h>

int main(){
	execl("/bin/ls", " ls","-l", "question6.c", (char *) NULL);
	perror("/bin/ls"); // this is fine because if execl succeeds, then this program becomes ls
	return 1; // therefore, since if it reaches here, there must be an error
	// first is the pathname, second is the argv[0] to the program, then args in ls or whatever it is
	// end with a nullpointer to indicate end of args, we need to cast it to char, NULL
}
