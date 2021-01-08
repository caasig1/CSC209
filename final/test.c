#include <stdio.h>
#include <unistd.h>
void mycopy(char *targ, char *src);

int main()
{
	char line[5], copy_of_line[5];
	while (fgets(line, sizeof line, stdin)) {
		mycopy(copy_of_line, line);
		printf("%s", copy_of_line);
	}
	return(0);
}

void mycopy(char *targ, char *src)
{
	for (; *src; src++)
		if (*src < 'a' || *src > 'e')
			*targ++ = *src;
	*targ = '\0';
}
