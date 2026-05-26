/* 
 * Creates a child process, which executes a loop and then exits.
 * The parent process waits for the child to terminate, retrieves the respective status
 * and checks/prints information regarding normal vs forced termination.
 */

#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
  int pid, status, count; 
  
  count = atoi(argv[1]);
  
  printf("parent: forking new process\n");
  pid = fork();

  if (pid == 0) { 
    for ( ; count > 0; count--) {
		printf("child: ping\n");
		sleep(3);
	}
	printf("child: bye\n");
    exit(42); 
  }
  
  printf("parent: waiting for child to terminate\n");
  waitpid(pid,&status,0);
  
  if (WIFEXITED(status)) {
    printf("parent: child returned %d\n", WEXITSTATUS(status));
  }
  else if (WIFSIGNALED(status)) {
    printf("parent: child terminated with %d\n", WTERMSIG(status));
  }
  
  printf("parent bye\n");

  return(0);
}
 
