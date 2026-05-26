/* Implements the phonebook functions */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "phonebook.h"

/* implementation */

void phonebook_init(phonebook_t *pb) {
	pb->entries = NULL;
	pb->size = 0;
}

void phonebook_clear(phonebook_t *pb) {
	if (pb->size>0) {
		free(pb->entries);
		pb->entries = NULL;
		pb->size = 0;
	}
}

int basic_find(const phonebook_t *pb, const char *name) {
	int i;
	
	for (i=0; (i < pb->size) && (strcmp(pb->entries[i].name,name)); i++);
	
	return(i);
}

int phonebook_find(const phonebook_t *pb, const char *name, entry_t *e) {
	int pos;
	
	pos = basic_find(pb,name);
	
	if (pos == pb->size) {
		return(0);
	}
	else {
		*e = pb->entries[pos];
		return(1); /* found */
	}
}

int phonebook_add(phonebook_t *pb, const entry_t *e) {
	entry_t *entries;
	int pos;
	
	pos = basic_find(pb,e->name);
	
	if (pos < pb->size) {
		pb->entries[pos] = *e;
		return(2);  /* replaced */
	}		
	
	entries = (entry_t *) realloc(pb->entries,(pb->size+1)*sizeof(entry_t));
	
	if (entries == NULL) {
		return(0);
	}
	
	pb->entries = entries;
	pb->entries[pb->size] = *e;	
	pb->size++;
	return(1); /* added */
}

int phonebook_rmv(phonebook_t *pb, const char *name) {
	int pos;
	
	pos = basic_find(pb,name);
	
	if (pos == pb->size) {
		return(0);
	}
	
	pb->size--;
	
	if (pos != pb->size) {
		pb->entries[pos] = pb->entries[pb->size];
	}
	
	pb->entries = (entry_t *) realloc(pb->entries,pb->size*sizeof(entry_t));
	return(1);
}

void phonebook_print(const phonebook_t *pb) {
	int i;
	
	printf("[ ");
	for (i=0; i < pb->size; i++) {
		printf("(name=%s, phone=%s) ", pb->entries[i].name, pb->entries[i].phone);
	}
	printf("]\n");
}
