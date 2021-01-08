/*
 * This "fails" when it successfully creates the lock file, so that you
 * can do "while makelockfile".
 */

#include <stdio.h>
#include <fcntl.h>
#include <errno.h>

int main()
{
    if (open("lockfile", O_CREAT|O_EXCL, 0600) >= 0)
	return(1);
    if (errno != EEXIST)
	perror("lockfile");
    return(0);
}
