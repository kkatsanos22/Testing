/* 
 * Creates a child process.
 * Both the parent and the child execute the same code (after the call of fork).
 * Both processes have the same variables at the same addresses of the virtual memory,
 * which is mapped by the OS to different addresses in physical memory.
 */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
	int count, pid;
	
	count = atoi(argv[1]);
	
	printf("%d: creating new process\n", getpid());
	
	pid = fork();
	
	printf("%d: fork returned %d\n", getpid(), pid);
	printf("%d: address of count is: %p\n", getpid(), &count);
	
	for (;count > 0; count--) {
		printf("%d: ping %d\n", getpid(), count);
		sleep(3);
	}
	
	printf("%d: bye\n", getpid());
	
	return(0);
}



 
