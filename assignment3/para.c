#include <stdio.h>
#include <string.h> 
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define USAGE "usage: ./para cmd <parameters\n"
struct item {
    int fd;
    char *data;
    char *command;
    struct item *next;
};

struct item *head = NULL;

void insert(char *command);
void printall();

int main(int argc, char **argv){
	if (argc < 2){
		fprintf(stderr, USAGE);
		exit(1);
	}
	
	char *string = argv[1];
        int loc = sizeof(string + 1);
        for (int i = 0; i < sizeof(string); i++){
                if (string[i] == '%'){
                        loc = i;
			break;
                }
        }
	char *string_one = malloc(sizeof(argv[1]));
        char *string_two = malloc(sizeof(argv[1]));
        if (loc < sizeof(argv[1])){
                strncpy(string_one, argv[1], loc);
                strcpy(string_two, argv[1] + loc + 1);
        }
        
	char line[1000];
	char *command = malloc(sizeof(argv[1]));
        while (fgets(line, 500, stdin) != NULL){
		if (loc < sizeof(argv[1])){
			if ((realloc(command, sizeof(command) + strlen(line))) == NULL){
				perror("realloc");
				exit(1);
			}
			strcpy(command, string_one);
			strcpy(command + loc, line);
			strcpy(command + loc + strlen(line) - 1, string_two);
		} else {
			command = string;
		}
        	insert(command);
	}
	int fd[2], r;
	struct item *p;
	for(p = head; p; p = p->next){	
		if ((pipe(fd)) == -1){
                	perror("pipe");
                	exit(1);
        	}
		if((r = fork()) == 0) {
			//child
			int devnull = open("/dev/null", O_RDONLY);
			// stdout into corresponding pipe
			if (dup2(fd[1], fileno(stdout)) == -1) {
				perror("dup2");
				exit(1);
			}
			// stderr into pipe
			if (dup2(fd[1], fileno(stderr)) == -1) {
                                perror("dup2");
                                exit(1);
                        } 
			// stdin to devnull
			if (dup2(devnull, fileno(stdin)) == -1) {
				perror("dup2");
                                exit(1);
			}
			// Does not read from pipe
                	if ((close(fd[0])) == -1){
				perror("close");
                	}

                	// Do not need fd[1] because we use stdout
                	if ((close(fd[1])) == -1){
                        	perror("close");
                	}
			
			// Remove devnull
			if ((close(devnull)) == -1){
                                perror("close");
                        } 

			execl("/bin/sh", "sh", "-c", p->command, (char *)NULL);
			perror("execl");
			exit(1);
		} else if (r > 0) {
			//parent
			// redirect input to linked list's file descriptor
			if ((dup2(fd[0], p->fd)) == -1) {
				perror("dup2");
				exit(1);
			}
			// does not write to pipe so close fd[1]
                	if ((close(fd[1])) == -1){
                	        perror("close");
                	}

                	// close fd[0] now that we are using stdin
                	if ((close(fd[0])) == -1){
                	        perror("close");
                	}
		} else {
			perror("fork");
			exit(1);
		}
	}
	printall();
	return 0;
}

void insert(char *command)
{
        struct item *new = malloc(sizeof(struct item));
        if (new == NULL){
                fprintf(stderr, "out of memory\n");
                exit(1);
        }

    new->command = malloc(sizeof(command));
    strcpy((*new).command, command);
    new->next = NULL;
    new->fd = 100;
    if (head != NULL){	
	new->fd = head->fd + 1;
    }
    /* find the node it goes after; NULL if it goes at the front */
    new->next = head;
    head = new;
}
void printall()
{
    struct item *p;
    for (p = head; p; p = p->next){
        printf("---- %s ----\n", p->command);
	char *buffer = malloc(1000);
	char buf[1];
	ssize_t bytes_read = 1;
        while ((bytes_read = read(p->fd, buf, 1)) > 0){
		strcat(buffer, buf);
	}
	printf("%s", buffer);
    }
}
