#ifndef __PHONEBOOK_H
#define __PHONEBOOK_H

typedef struct {
	char name[64];
	char phone[64];
} entry_t;

typedef struct {
	entry_t *entries; /* dynamic table holding the entries */
	int size;         /* current size of the table */
} phonebook_t;


extern void phonebook_init(phonebook_t *pb);
extern void phonebook_clear(phonebook_t *pb);
extern int phonebook_find(const phonebook_t *pb, const char *name, entry_t *e);
extern int phonebook_add(phonebook_t *pb, const entry_t *e);
extern int phonebook_rmv(phonebook_t *pb, const char *name);

extern void phonebook_traverse(phonebook_t *pd, void(*handle)(entry_t *e));

#endif