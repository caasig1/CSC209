#include <stdio.h>
#include <stdlib.h> //malloc, man malloc shows this
#include <string.h>

int main(){
	extern void mytest(char *s);
	mytest("Monday");
	mytest("M");
	mytest("Mon");
	mytest("something long");
	return 0;
}

void mytest(char *s){
	extern char *shorten(char *s);
	char *t = shorten(s);
	if (s == t)
		printf("shortening %s yields itself\n", s);
	else
		printf("shortening %s yields %s\n", s, t);
	//free malloc
}

char *shorten (char *s){
	if (strlen(s) <= 3){
		return (s);
	}
	char *p;
	if ((p = malloc(4)) == NULL)
		return (NULL);
	strncpy(p, s, 3);
	p[3] = '\0';
	return(p);
}
