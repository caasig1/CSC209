#include <stdio.h>
#include <ctype.h>
void mycopy(char *copyto, char*copyfrom);
int main() {
        char string[252] = "hello";
        char string2[252] = "hello world";
        mycopy(string, string2);
        printf("%s\n", string);
}

void mycopy(char *copyto, char *copyfrom){
    while (*copyfrom != '\0') {
        if (*copyfrom >= 'a' && *copyfrom <= 'e') {
            copyfrom++;
        } else {
            *copyto = *copyfrom;
            copyto++;
            copyfrom++;
        }
    }
}
