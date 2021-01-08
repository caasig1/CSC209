#include <stdio.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

static int number = 0;

void handler(int signum){
	number = number << 1;
	if (signum == SIGUSR2) {
		number++;
	}
}

int main(){
	printf("My pid is %d\n", getpid());
	
	struct sigaction act;
	act.sa_handler = handler;
	act.sa_flags = 0;
	sigemptyset(&act.sa_mask);
	sigaction(SIGUSR1, &act, NULL);
	sigaction(SIGUSR2, &act, NULL);

	int count = 0;
	while (count < 8){
		sleep(1000000000);
		count++;
	}

	printf("%c\n", number);
	return 0;
}
