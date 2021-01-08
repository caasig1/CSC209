#include <stdio.h>
#include <sys/stat.h>                                       
#include <sys/types.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>

int search(char *dir, char *name);

int main(int argc, char **argv){
	// Check for correct arguments
	if (argc < 3) {
		fprintf(stderr, "usage: findname name dir ...\n");
		return 2;
	}

	// Search each directory in order
	char *filename = argv[1];
	for(int i = 2; i < argc; i++){
		int val = search(argv[i], filename);
		if (val == 0) {
			return 0;
		} else if (val == 2) {
			return 2;
		}
	}
	return 1;
}	

int search(char *dir, char *name){
	// Open the directory
	DIR *directory;
	directory = opendir(dir);
	if (directory == NULL){
		perror(dir);
		return 2;
	}

	// Read the directory and store pathname
	struct dirent *pdir;
	char location[2001];
	while( (pdir = readdir(directory)) ){
		// Print pathname if found (passed through search's dir)
		if(strcmp(pdir->d_name, name) == 0){
			strcat(dir, name);
			printf("%s\n", dir);
			return 0;
		// The fild is not same name
		} else {
			// Check if it is a directory
			if (pdir->d_type == 4){
				// New pathname for subfolder and recurse
				if (strcmp(pdir->d_name, ".") != 0 && strcmp(pdir->d_name, "..") != 0){
					memset(location, 0, 2001);
					strcat(location, dir);
					strcat(location, "/");
					strcat(location, pdir->d_name);
					int retval = search(location, name);
					if (retval == 0){
						return 0; 
					}
				}
			}
		}
	}	
	closedir(directory);
	return 1;
}
