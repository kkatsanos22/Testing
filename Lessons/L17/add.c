#include <stdio.h>
#include<stdlib.h>

int main(int argc, char *argv[]) {
  int v1,v2;
  
  v1 = atoi(argv[1]);
  v2 = atoi(argv[2]);
  
  printf("%d plus %d equals %d\n", v1, v2, v1+v2);
  return(0);
}


 
