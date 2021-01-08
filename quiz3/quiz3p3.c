#include <stdio.h>

int countq();

int main() {
    countq();
    return 0;
}

int countq() {
    char c = 'q';
    char i;
    int counter = 0;
    while ( ( i = getchar()) != EOF) {
        if (c == i){
            counter++;
        }
    }
    printf("%d\n", counter);
    return 0;
}
