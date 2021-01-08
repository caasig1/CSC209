#include <stdio.h>

int main()
{
	char r;
	while ((r = getc(stdin)) > 0){
		if (r < 'a' || r > 'e'){
			printf("%c", r);
		}
	}
}
