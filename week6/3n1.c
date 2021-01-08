#include <stdio.h>

struct retval {
	int count;
	int max;
}

struct retval my3n1(int n){
    int count = 0;
    int max = n;
    while (n > 1) {
        count += 1;
        if (n % 2 == 0){
            n /= 2;
	} else {
            n = n * 3 + 1
            if n > max:
                max = n
   	}
      	return count, max


maxcount = maxmax = 0
for i in range(1,20):
    count1,max1 = my3n1(i)
    if count1 > maxcount:
        maxcountloc = i
        maxcount = count1
    if max1 > maxmax:
        maxmaxloc = i
        maxmax = max1

print('The longest sequence was length', str(maxcount) + ', starting with', maxcountloc)
print('The highest value reached was', str(maxmax) + ', starting with', maxmaxloc)
