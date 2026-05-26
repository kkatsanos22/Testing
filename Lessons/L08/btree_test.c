/*
 * Test program for binary search tree.
 * Creates a anew tree and applies a series of operations,
 * (a)dd, (r)emove, (f)ind, (t)raverse, (p)print and (c)lear, 
 * depending on user input (use file redirection for faster testing).
 * Upon (e)xit, it clears the entire tree.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "btree.h"

int main(int argc, char *argv[]) {
	char sel;
	int key, res; 
	struct btree *root, *node;
	
	btree_new(&root);
	
	do {
		do {sel = getchar(); } while ((sel == '\n') || (sel == ' '));
		switch (sel) {
			case 'a': {
				scanf("%d", &key);
				node = (btree *)malloc(sizeof(btree));
				node->key = key;
				res = btree_insert(&root, node);
				printf("Added %d : %d\n", node->key, res);
				if (res == 0) {
					free(node);
				}
				break;
			}
			case 'r': {
				scanf("%d",&key);
				node = btree_remove(&root, key);
				printf("Remove %d: %d\n", key, node!=NULL);
				if (node != NULL) {
					free(node);
				}
				break;
			}
			case 'f': {
				scanf("%d", &key);
				node = btree_find(root, key); 
				printf("Find %d: %d\n", key, node!=NULL);
				break;
			}
			case 'c': {
				btree_clear(root);
				root = NULL;
				printf("Clear\n");
				break;
			}
			case 't': {
				btree_traverse_inc(root);
				break;
			}
			case 'p': {
				btree_print(root);
				break;
			}
		}
	} while (sel!='e');
	
	btree_clear(root);
	
	return(0);
}