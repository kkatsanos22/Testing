/* 
 * Creates a child process, which executes program "add".
 * The parent waits for the child to terminate, retrieves the respective status
 * and checks/prints information regarding normal vs forced termination.
 */

#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
	int pid, status;
	
	pid = fork();
	if (!pid) { 
		printf("child: execute ./add 123 456\n");
		execl("./add","add", "123", "456", NULL);
		perror("child: execl");
		return(1);
	}
	
	waitpid(pid,&status,0);
	printf("parent: child terminated\n");
	if (WIFEXITED(status)) {
		printf("parent: child returned %d\n", WEXITSTATUS(status));
	}
	else if (WIFSIGNALED(status)) {
		printf("parent: child killed with %d\n", WTERMSIG(status));
	}
	
	return(0);
}


 
