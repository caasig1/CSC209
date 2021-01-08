#include "gcd.h"
// Should do this!!
// Forces its .h and its other uses to be compatible

int gcd(int x, int y)
{
    int t;

    while (y) {
        t = x;
        x = y;
        y = t % y;
    }
    return(x);
}

// together with gcd.h, gcd.h is just the function call thing and uses this onee
// when usedd elsewhere it uses gcd.h and that calls gcd.c, this is a package together (gcd.c and gcd.h)
