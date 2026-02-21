/* Function that returns a locally computed result in dynamically alocated memory. 
 * The result is picked and used in main, which then frees the memory. */ 

#include <stdio.h>
#include <stdlib.h>

int *add(int a, int b) {
	int *sumPtr;
	
	sumPtr = (int *)malloc(sizeof(int));
	*sumPtr = a + b;
	return(sumPtr);
}

int main(int argc, char *argv[]) {
	int a, b, *sumPtr;
	
	scanf("%d %d", &a, &b);
	
	sumPtr = add(a, b);
	printf("%d\n", *sumPtr);
	
	free(sumPtr);
	
	return(0);
}

