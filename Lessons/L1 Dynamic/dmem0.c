#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
	char *p1, *p2;
	
	p1 = (char *) malloc(4);
	if (p1 == NULL) {
		printf("Out of memory\n");
		return(1);
	}
	
	*p1 = 'a';
	*(p1+1) = 'b';
	*(p1+2) = 'c';
	*(p1+3) = '\0';

	printf("%s\n", p1);
	
	p2 = realloc(p1, 8);
	if (p2 == NULL) {
		printf("Out of memory\n");
		return(1);
	}
	
	*(p2+4) = 'A';
	*(p2+5) = 'B';
	*(p2+6) = 'C';
	*(p2+7) = '\0';
	
	printf("%s\n",p2+4);
	
	free(p2);
		
	return(0);
}