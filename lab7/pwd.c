#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <dirent.h>

int main()
{
	struct stat curr;
	if  (lstat(".", &curr)){
		perror(".");
		return 1; 
	}	
	int prev = curr.st_ino; // the leaf's inode
	chdir(".."); // into parent
	while (curr.st_ino != 2){
		if (lstat(".", &curr)){
			perror(".");
		 	return 1;	
		}	// parent node
		DIR *folder;
	    	folder = opendir(".");
    		if(folder == NULL)
    		{
        		perror(".");
        		return(1);
    		}
		struct dirent *pdir;
		while ((pdir = readdir(folder))){
			if ((*pdir).d_ino == prev){
				printf("%d\n", (*pdir).d_type);
			}
		}
		closedir(folder);
		prev = curr.st_ino;
		chdir("..");
	}
	printf("and then we're at the root directory.\n");
	return 0;
}
