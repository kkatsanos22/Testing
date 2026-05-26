/* max.c */
#include "min.c"

int max(int a, int b) {
	if (min(a,b) == a) 
		return(b);
	else 
		return(a);
}
