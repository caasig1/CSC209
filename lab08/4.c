#include <stdio.h>
#include <stdlib.h>

struct item {
    int key;
    int data;
    struct item *next;
};

struct item *head = NULL;

int main()
{
    extern void insert(int key, int data), delete(int key), printall();
    extern int search(int key);

    insert(38, 3);
    insert(20, 2);
    insert(5, 0);
    insert(22, 6);
    insert(46, 18);

    printf("With all five items:\n");
    printall();

/*

    printf("After delete(22):\n");
    delete(22);
    printall();
    printf("After delete(5):\n");
    delete(5);
    printall();
    printf("delete(30) shouldn't do anything:\n");
    delete(30);
    printall();

*/

    return(0);
}


void insert(int key, int data)
{
	struct item *prev;
	struct item *new_node = malloc(sizeof(struct item));
	if (new_node == NULL){
		fprintf(stderr, "out of memory\n");
		exit(1);
	}
	(*new_node).key = key;
	(*new_node).data = data;
	(*new_node).next = NULL;

	prev = head;
	if (head == NULL || head->key >= key){
		prev = NULL;
	} else {
		while (prev -> next != NULL && prev -> next -> key < key){
			prev = prev->next;
		}
	}

	if (prev == NULL){
		new_node->next = head;
		head = new_node;
	} else {
		new_node -> next = prev -> next;
		prev -> next = new_node;
	}
}


void delete(int key)
{
}


int search(int key) /* returns -1 if not found */
{
    struct item *p;

    for (p = head; p && p->key < key; p = p->next)
        ;
    if (p && p->key == key)
        return(p->data);
    else
        return(-1);
}


void printall()
{
    struct item *p;
    for (p = head; p; p = p->next)
        printf("%d: %d\n", p->key, p->data);
    printf("[end]\n");
}
