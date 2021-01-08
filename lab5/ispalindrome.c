#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char **argv){
	extern int ispalindrome(char *string);

	// Check if the usage is correct	
	if (argc == 2){
		return ispalindrome(argv[1]);
	} else{
		printf("usage: %s string\n", argv[0]);
	}	
}

//return 0 or 1 to be exit status (0 when it is a palindrome, 1 when it is not a palindrome)
int ispalindrome(char *string){

	//pointers to start and end of a string
	char *start = string;
	char *end = string + (int) strlen(string) - 1;
	
	while (end > start){
		//check if it is alpha numeric, if it is not then skip to next character 
		if (! isalnum(*start)){
			start++;
		} else if (! isalnum(*end)){
			--end;

		//check if the alpha numeric characters are equivalent, disregarding the case of the letter	
		} else if (tolower(*start) == tolower(*end)){
			start++;
			--end;
		} else {
			return 1;
		}
	}
	return 0;
}
