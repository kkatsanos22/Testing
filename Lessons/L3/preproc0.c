//#include <stdio.h>

#define A 10
#define B 20
#define C (A+B)
#define D (C*B)


int main(int argc , char *argv[]) {
  int i;
  
  for (i=0; i<D; i++) {
    printf("%d\n",i);
  }
  
  return(0);
}
 
