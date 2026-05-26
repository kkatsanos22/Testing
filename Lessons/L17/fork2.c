/* 
 * Creates a child process.
 * The child executes a different part of the code (if-part) than the parent (else-part).
 * Both processes have the same variables at the same addresses of the virtual memory,
 * which is mapped by the OS to different addresses in physical memory.
 */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
	int count, pid, mypid; 
	
	count = atoi(argv[1]);
	
	printf("%d: creating new process\n", getpid());
	
	pid = fork();
	
	mypid = getpid();
	printf("%d: fork returned %d\n", mypid, pid);
	printf("%d: address of count is: %p\n", mypid, &count);
	
	if (pid == 0) {
		for (; count > 0; count--) {
			printf("%d: ping from child %d\n", mypid, count);
			sleep(3);
		}
		return(0);
	}
	else {
		for (; count > 0; count--) {
			printf("%d: ping from parent %d\n", mypid, count);
			sleep(3);
		}
		return(0);
	}
	
}


 
