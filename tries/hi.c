#include <stdio.h>
#include <stdlib.h>

int main(){
	char *string = "hello %s my friend\n";
	char *new = (string, "isaac");
	printf("%s\n", string);
	printf("%s\n", new);
	return 0;

}
