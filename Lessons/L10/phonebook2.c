#include <string.h>
#include <stdlib.h>
#include "phonebook2.h"

void phonebook_init(phonebook_t *pb) {
	pb->size = 0;
}

void phonebook_clear(phonebook_t *pb) {
	if (pb->size>0) {
		free(pb->entries);
	}
}

int find0(const phonebook_t *pb, const char name[]) {
	int i;
	
	for (i=0; (i < pb->size) && (strcmp(pb->entries[i].name,name)); i++);
	
	return(i);
}

int phonebook_find(const phonebook_t *pb, const char *name, entry_t *e) {
	int pos;
	
	pos = find0(pb,name);
	
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
	
	pos = find0(pb,e->name);
	
	if (pos < pb->size) {
		pb->entries[pos] = *e;
		return(-1);  /* replaced */
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
	
	pos = find0(pb,name);
	
	if (pos == pb->size) {
		return(0);
	}
	
	//memcopy(&pb->entries[pos],&pb->entries[pb->size-1],sizeof(entry));
	pb->size--;
	pb->entries[pos] = pb->entries[pb->size];
	pb->entries = (entry_t *) realloc(pb->entries,pb->size*sizeof(entry_t));
	return(1);
}

void phonebook_traverse(phonebook_t *pb, void(*handle)(entry_t *e)) {
	int i;
	
	for (i=0; (i < pb->size); i++) {
		handle(&pb->entries[i]);
	}
}

