#include <stdio.h>

// function for counting the number of 'q's
int count(char letter);

int main() {
    char letter = 'q';
    count(letter);
    return 0;
}

int count(char letter) {
    char i;
    int counter = 0;
    // while we have not reached the end of the file...
    while ( ( i = getchar()) != EOF) {
        // if the character is the one we are looking for, 'q', then increase the counter
        if (letter == i){
            counter++;
        }
    }
    printf("%d\n", counter);
    return 0;
}
