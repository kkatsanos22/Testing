/* This program writes to stdout (the terminal) in three different ways:
 * (1) via the stdio library and the prtinf function; (2) via the wrapper 
 * function for the write system call; (3) via the syscall function.
 * The "debugging" messages are printed in stderr (also appear in the terminnal).
 * 
 * In all three cases, the message appears in the terminal as expected.
 *
 * However, if you remove the \n from the string, you will observe
 * a different outcome: the output of the printf will appear last! 
 * This is because stdio buffers the output internally 
 * and pushes it towards the standard output only when a \n is printed.
 */

#include <stdio.h>
#include <sys/syscall.h>
#include <unistd.h>

int main(int argc, char *argv[]){
  char str[] = "Hello World!\n"; // bytes to write
  int res; 

  // indirect write system via user lib function
  fprintf(stderr, "Writing via printf\n");
  printf("%s",str);
  
  // system call via glibc wrapper function
  fprintf(stderr, "Writing via wrapper function\n");
  res = write(STDOUT_FILENO,str, 13);
  fprintf(stderr,"Return value is: %d\n", res);
  
  // system call via generic syscall function
  fprintf(stderr, "Writing via syscall\n");
  res = syscall(SYS_write, STDOUT_FILENO, str, 13);
  fprintf(stderr,"Return value is: %d\n", res);

  return(0);
}



 
