/*
 * Implementation of basic operations for a binary search tree.
 * New nodes are added as leaves.
 * Removal is supported only for leaf nodes.
 */

#include <stdio.h>
#include <stdlib.h>
#include "btree.h"

void btree_new(btree **root) {
	*root = NULL;
}

void btree_clear(btree *root) {
	if (root != NULL) {
		btree_clear(root->left);
		btree_clear(root->right);
		free(root);
	}
}

btree *btree_find(btree *root, int key) {
	if (root == NULL) {
		return(NULL);
	}
	else if (root->key == key) {
		return(root);
	}
	else if (root->key > key) {
		return(btree_find(root->left,key));
	}
	else {
		return(btree_find(root->right,key));
	}
}

void btree_find0(btree *root, int key, btree **node, btree **parent) {
	btree *curr, *curr_parent; 
	
	curr = root; 
	curr_parent = NULL;
	
	while ((curr != NULL) && (curr->key != key)) {
		curr_parent = curr;
		 if (curr->key > key) {
			 curr = curr->left; 
		}
		 else { 
			 curr = curr->right; 
		}
	}
	
	if ((curr != NULL) && (curr->key == key)) {
		*node = curr;
	}
	else {
		*node = NULL;
	}
	*parent = curr_parent;
	
}

int btree_insert(btree **root, btree *node) {
	btree *curr,*curr_parent;
	
	btree_find0(*root,node->key,&curr,&curr_parent); 
	
	if ((curr != NULL) && (curr->key == node->key)) {
		return(0); // no dublicates allowed
	}
	
	node->left = NULL;
	node->right = NULL;
	
	if (curr_parent == NULL) {
		*root = node;
	}
	else if (curr_parent->key > node->key) {
		curr_parent->left = node;
	}
	else {
		curr_parent->right = node;
	}
	
	return(1);
}

btree *btree_remove(struct btree **root, int key) {
	struct btree *curr,*curr_parent;
	
	btree_find0(*root,key,&curr,&curr_parent); 
	
	if (curr == NULL) {
		return(NULL); /* not found */
	}
	
	if ((curr->left != NULL) || (curr->right != NULL)) {
		return(NULL); /* not a leaf node */
	}
	
	if (curr_parent == NULL) {
		*root = NULL;
	} 
	else if (curr_parent->left == curr) {
		curr_parent->left = NULL;
	}
	else {
		curr_parent->right = NULL;
	}
	
	return(curr);
}

static void btree_traverse_inc0(btree *root) {
	if (root != NULL) {
		btree_traverse_inc0(root->left);
		printf("%d ",root->key);
		btree_traverse_inc0(root->right);
	}
}

void btree_traverse_inc(btree *root) {
	btree_traverse_inc0(root);
	printf("\n");
}

static void btree_print0(btree *root, int level) {
	int i;
	
	if (root == NULL) {
		return;
	}
	
	btree_print0(root->right, level+1);
	
	for (i=0; i < level*level; i++) {
		printf(" ");
	}
	for (i=0; i < level; i++) {
		printf("--");
	}
	printf("%d\n",root->key);
	
	btree_print0(root->left, level+1);
}

extern void btree_print(btree *root) {
	btree_print0(root,0);
}