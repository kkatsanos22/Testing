/* Implements a (simple) phonebook using a dynamic table. 
 * The size of the table is adjusted to host only the valid entries,
 * extending the amount of used memory when adding a new entry 
 * and decreasing it when removing an entry.
 * 
 * The main function implements a simple hardcoded test sequence. 
 * Feel free to make it interactive by adding a suitable input dialog 
 * so that the user can add, remove, search in an open-ended way.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* basic definitions */

typedef struct {
	char name[64];
	char phone[64]; /* phone as string for convenience */
} entry_t;

typedef struct {
	entry_t *entries; /* dynamic table holding the entries */
	int size;         /* current size of the table */
} phonebook_t;

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

void phonebook_print(phonebook_t *pb) {
	int i;
	
	printf("[ ");
	for (i=0; i < pb->size; i++) {
		printf("(name=%s, phone=%s) ", pb->entries[i].name, pb->entries[i].phone);
	}
	printf("]\n");
}

/* test program */

int main(int argc, char *argv[]) {
	int res; 
	entry_t e;
	phonebook_t pb;
	
	/* start of test sequence */
	
	phonebook_init(&pb);
	phonebook_print(&pb);
	
	/* add some enties */
	
	strcpy(e.name,"Spyros"); 
	strcpy(e.phone,"111111");
	res = phonebook_add(&pb, &e);
	printf("Add for %s:%s returned result %d\n", e.name, e.phone, res);
	phonebook_print(&pb);
	
	strcpy(e.name,"Vana"); 
	strcpy(e.phone,"222222");
	res = phonebook_add(&pb, &e);
	printf("Add for %s:%s returned result %d\n", e.name, e.phone, res);
	phonebook_print(&pb);
	
	strcpy(e.name,"Giorgos"); 
	strcpy(e.phone,"333333");
	res = phonebook_add(&pb, &e);
	printf("Add for %s:%s returned result %d\n", e.name, e.phone, res);
	phonebook_print(&pb);
	
	strcpy(e.name,"Spyros"); 
	strcpy(e.phone,"555555");
	res = phonebook_add(&pb, &e);
	printf("Add for %s:%s returned result %d\n", e.name, e.phone, res);
	phonebook_print(&pb);
	
	/* search for some entries */
	
	strcpy(e.name,"Spyros");
	res = phonebook_find(&pb, e.name, &e);
	printf("Search for %s returned result %d\n", e.name, res);
	if (res) {
		printf("%s's number is %s\n", e.name, e.phone);
	}
	
	strcpy(e.name,"Nikos");
	res = phonebook_find(&pb, e.name, &e);
	printf("Search for %s returned result %d\n", e.name, res);
	if (res) {
		printf("%s's number is %s\n", e.name, e.phone);
	}
	
	strcpy(e.name,"Giorgos");
	res = phonebook_find(&pb, e.name, &e);
	printf("Search for %s returned result %d\n", e.name, res);
	if (res) {
		printf("%s's number is %s\n", e.name, e.phone);
	}
	
	/* remove some entries */
	
	strcpy(e.name,"Spyros");
	res = phonebook_rmv(&pb, e.name);
	printf("Remove for %s returned result %d\n", e.name, res);
	phonebook_print(&pb);
	
	strcpy(e.name,"Nikos");
	res = phonebook_rmv(&pb, e.name);
	printf("Remove for %s returned result %d\n", e.name, res);
	phonebook_print(&pb);
	
	strcpy(e.name,"Giorgos");
	res = phonebook_rmv(&pb, e.name);
	printf("Remove for %s returned result %d\n", e.name, res);
	phonebook_print(&pb);
	
	/* search for some entries */
	
	strcpy(e.name, "Spyros");
	res = phonebook_find(&pb, e.name, &e);
	printf("Search for %s returned result %d\n", e.name, res);
	if (res) {
		printf("%s's number is %s\n", e.name, e.phone);
	}
	
	strcpy(e.name,"Vana");
	res = phonebook_find(&pb, e.name, &e);
	printf("Search for %s returned result %d\n", e.name, res);
	if (res) {
		printf("%s's number is %s\n", e.name, e.phone);
	}
	
	/* end of test sequence */
	
	phonebook_clear(&pb);
	phonebook_print(&pb);
	
	return(0);
}

