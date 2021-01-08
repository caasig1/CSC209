#include <stdio.h>

struct asdf {
	int x;
	struct asdf *other;
};

int main() {
	struct asdf a, b;
	extern void sillyfunction(struct asdf *p);

	a.x = 123;
	b.x = 234;
	a.other = &b;
	b.other = &a;

	sillyfunction(&a);
	return 0;
}

void sillyfunction(struct asdf *p){
	if (p->x < p->other->x) {
		printf("you've passed inthe lesser-x one\n");
	} else {
		printf("you've passed in the greater or equal x one\n");
	}
}
