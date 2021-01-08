#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
	fork();// one calls fork (now theres 2)
	fork();//both call fork (now theres 4)
	printf("%d\n", getpid());
	return 0;
}
