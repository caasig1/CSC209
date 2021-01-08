#include <stdio.h>
int main()
{
	int c;
	while ((c = getchar()) != EOF)
	if ((c <=109 && c > 96) || (c <= 77 && c > 64))
		putchar(c + 13);
	else if ((c>109 && c < 123) || (c > 77 && c < 91))
		putchar(c-13);
	else
		putchar(c);
	return(0);
}
