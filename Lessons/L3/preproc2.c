//#include <stdio.h>

#define PUTLOWERCASE(a) { \
  if ((a < 'A') || (a > 'Z')) { putchar(a); } \
  else { putchar(a-'A'+'a'); } \
} 

int main(int argc , char *argv[]) {
  char c;
  
  do {
    c = getchar();
    PUTLOWERCASE(c)
  } while (c != '\n');
  
  return(0);
}
 
