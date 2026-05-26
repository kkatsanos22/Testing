#ifndef __BTREE_H
#define __BTREE_H

typedef struct btree {
	int key; 
	/* more data here */
	struct btree *left, *right; /* pointer to left and right subtrees */
} btree;

extern void btree_new(btree **root);
extern void btree_clear(btree *root);
extern btree *btree_find(btree *root, int key);
extern int btree_insert(btree **root, btree *node);
extern btree *btree_remove(btree **root, int key);
extern void btree_traverse_inc(btree *root);
extern void btree_print(btree *root);

#endif