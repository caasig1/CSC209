#include <unistd.h>

int main()
{
    int i;
    for (i = 1; i < 10; i++)
	write(i, "hello", 5);
    return(0);
}
