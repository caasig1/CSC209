#include <stdio.h>
#include <dirent.h>

int main()
{
    DIR *dp;
    struct dirent *r;

    if ((dp = opendir(".")) == NULL) {
        perror(".");
        return(1);
    }

    char *name;
    int c;
    while ((r = readdir(dp))){
        name = r->d_name;
        c = name[0];
        if (c != '.') {
	    DIR *check;
	    if ((check = opendir(name)) == NULL) {	
                printf("%s\n", name);
            }
        }  
    }
    return(0);
}
