/* Allocates sizeof(int) bytes, uses the memory to store the result of an addition,
 * prints the results, and frees the memory. You can test how the program behaves 
 * if it uses the memoery after this is freed, and also if the memory is never freed */ 

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
	int a,b,*sumPtr;
	
	sumPtr = (int *) malloc( sizeof(int) );
	if (sumPtr == NULL) {
		printf("no memory\n");
		return(1);
	}

	scanf("%d %d",&a,&b);	
	
	*sumPtr = a+b;
	
	printf("%d\n",*sumPtr);
	
	free(sumPtr);
		
	return(0);
}

