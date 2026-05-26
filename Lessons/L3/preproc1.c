#include <stdio.h>

#define LOWERCASE(a) ((a>='A') && (a<='Z') ? a-'A'+'a' : a)

int main(int argc , char *argv[]) {
  char c;
  
  do {
    c = getchar();
    c = LOWERCASE(c);
    putchar(c);
  } while (c != '\n');
  
  return(0);
}
 
