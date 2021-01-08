#include <stdio.h>
#include <stdlib.h>

struct node {
	int data;
	struct node *left, *right;
}

int main(){
	struct node *root;
	extern struct node *newnode(int data);
	extern void printtree(struct node *p);

	root = newnode(1);
	root->left = newnode(2);
	root->left->right = newnode(3);
	//root->left->right->right = NULL; // do this in below
	root->right = newnode(4);

	printtree(root);

	return 0;
}

struct node *newnode(int data){
	struct node *p = malloc(sizeof( struct node));
	if (p == NULL) {
		fprintf(stderr, "out of memory!\n");
		exit(1);
	}
	p->data = data;
	p->left = NULL;
	p->right = NULL;
	return p;
}

void printtree(struct node *p){
	if (p) {
		printtree(p->left);
		printf("%d\n", p->data);
		printtree(p->right);
	}
}
