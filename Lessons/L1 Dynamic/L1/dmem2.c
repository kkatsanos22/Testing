/* Uses initially malloc and the realloc to incrementally increase the size of an array
 * that is used to store int values read from input. Reading and memory increase stops
 * when the program detects the end of input, and the allocated memory is freed. 
 * Try to replace malloc with realloc to confirm equivalent behavior. */ 

#include <stdio.h>
#include <stdlib.h>

void printTable(int a[], int n) {
	int i;
	
	printf("[ ");
	for (i=0; i < n; i++) {
		printf("%d ", a[i]);
	}
	printf("]\n");
}

int main(int argc, char *argv[]) {
	int *table, *new_table, size;
	
	size = 1;
	table = (int *) malloc(sizeof(int));
	//table = (int *) realloc(NULL, sizeof(int)*size);
	if (table == NULL) {
		printf("Out of memory\n");
		return(1);
	}
	
	while (scanf("%d", &table[size-1]) == 1) {
		size++;
		new_table = (int *) realloc(table, sizeof(int)*size);
		if (new_table == NULL) {
			printf("Out of memory\n");
			return(1);
		}
		else {
			table = new_table;
			printTable(table, size-1);
		} 
	}
	
	printf("The final contents are: ");
	printTable(table, size-1);
	
	free(table);
	
	return(0);
}
