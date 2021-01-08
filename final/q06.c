#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(){
	int maxsize = 500;
	char *finallines = malloc(maxsize);
	char *helperlines = malloc(maxsize);
	char *line = malloc(maxsize);
	while (fgets(line, 500, stdin) != NULL) {
		memset(helperlines, '\0', maxsize);
		strcpy(helperlines, finallines);
		memset(finallines, '\0', maxsize);
		strcat(finallines, line);
		strcat(finallines, helperlines);
	}
	printf("%s", finallines);
	free(finallines);
	free(helperlines);
	free(line);
	return 0;
}
