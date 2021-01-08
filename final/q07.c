#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>

struct file {
	char *name;
	struct file *next;
};
struct file *head = NULL;

int main(int argc, char **argv){
	if (argc < 2){
                fprintf(stderr, "usage: ./q07 directory\n");
                return 1;
        }

	DIR *folder;
	folder = opendir(argv[1]);
	if (folder == NULL){
		fprintf(stderr, "usage: ./q07 directory\n");
                return 1;
	}

	struct dirent *pdir;
	while ((pdir = readdir(folder))){
		if ((strcmp(pdir->d_name, ".")) && (strcmp(pdir->d_name, ".."))){
			struct file *new_node;
			if ((new_node = malloc(sizeof(struct file))) == NULL) {
        			fprintf(stderr, "out of memory!\n");  /* unlikely */
        			return 1;
    			}
			new_node->name = pdir->d_name;
			new_node->next = head;
			head = new_node;
		}
	}
	int error = closedir(folder);
	if (error != 0){
		perror("close");
		return 1;
	}
	return 0;
}
