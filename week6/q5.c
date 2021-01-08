#include <stdio.h>

struct help {
	int count;
	int max;
};

void my3n1( int n,struct help *result); 

int main(){
	int maxcount = 0;
	int maxmax = 0;
	int maxcountloc = 0;
	int maxmaxloc = 0;
	for (int i=1; i<20; i++){
		struct help result;
		my3n1(i, &result);
		if (result.count > maxcount){
			maxcountloc = i;
			maxcount = result.count;
		}
		if (result.max > maxmax){
			maxmaxloc = i;
			maxmax = result.max;
		}
	}
	printf("The longest sequence was length %d starting with %d\n", maxcount, maxcountloc);
	printf("The highest value reached was %d starting with %d\n", maxmax, maxmaxloc);
	return 0;
}


void my3n1( int n, struct help *result){
	int count = 0;
	int max = n;
	while (n > 1){
		count ++;
		if ((n % 2) == 0) {
			n = n/2;
		} else {
			n = n * 3 + 1;
			if (n > max) {
				max = n;
			}
		}
	}
	result->count = count;
	result->max = max;
}

