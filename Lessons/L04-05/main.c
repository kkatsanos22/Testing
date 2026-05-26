/* Implements an input-based test for the phonebook component. */

#include <stdio.h>
#include <string.h>
#include "phonebook.h"

int main(int argc, char *argv[]) {
  char sel;
  int res; 
  entry_t e;
  phonebook_t pb;
  
  phonebook_init(&pb);
  
  do {
    do {sel = getchar(); } while ((sel == '\n') || (sel == ' '));
    switch (sel) {
      case 'a': {
		scanf("%63s %63s", e.name, e.phone);
        res = phonebook_add(&pb, &e); 
		printf("Add %s %s: %d\n", e.name, e.phone, res);
        break;
      }
      case 'r': {
    	scanf("%63s",e.name);
        res = phonebook_rmv(&pb, e.name);
		printf("Remove %s: %d\n", e.name, res);
        break;
      }
      case 'f': {
    	scanf("%63s", e.name);
        res = phonebook_find(&pb, e.name, &e); 
		printf("Find %s: %d ", e.name, res);
		if (res) { printf("%s ",e.phone); }
		printf("\n");
        break;
      }
	  case 'p': {
		phonebook_print(&pb);
	  }	
    }
  } while (sel!='e');
  
  phonebook_clear(&pb);
  
  return(0);
}