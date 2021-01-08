#include <stdio.h>
#include <string.h>
int main(){
	FILE *fp;
	fp = fopen("foo", "r");
	if (fp == NULL) {
		perror("foo");
		return(1);	
	}
	FILE *fp2;
	fp2 = fopen("bar", "w");
	if (fp2 == NULL) {
                perror("bar");
                return(1);
        }
	char line[100];

	while (fgets (line, sizeof line, fp) != NULL){
		fprintf(fp2, "%s", line);
	}
	return 0;

}
