#include <stdio.h>

#include "min.c"
#include "max.c"

int main(int argc, char *argv[]) {
  int a,b;

  printf("Enter two integer values: "); 
  scanf("%d %d", &a, &b);
  printf("min = %d, max = %d\n", min(a,b), max(a,b));
  return(0);
}
