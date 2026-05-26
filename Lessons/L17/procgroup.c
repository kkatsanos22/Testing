/* 
 * Creates a child process.
 * Depending on the argument (SAME or DIFF), the child 
 * (a) remains in the same process group, or (b) creates its own process group.
 * In the latter case, pressing Ctrl-C will only kill the parent, not the child.
 */

#include <unistd.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
	int pid, diffgrp, i=0;
	
	if (!strcmp(argv[1],"SAME")) {
		diffgrp = 0;
	}
	else if (!strcmp(argv[1],"DIFF")) {
		diffgrp = 1;
	}
	else {
		printf("Expected argument SAME or DIFF\n");
		return(1);
	}
	
	pid = fork();
	
	if (!pid) {
		printf("child: PID=%d, PPID=%d, PGID=%d\n", getpid(), getppid(), getpgrp());
		if (diffgrp) {
			setpgid(0, getpid()); /* create my own group */
			printf("child: PID=%d, PPID=%d, PGID=%d\n", getpid(), getppid(), getpgrp());
		}
		while (1) {
			printf("child: ping %d\n", i++);
			sleep(3);
			printf("child: PID=%d, PPID=%d, PGID=%d\n", getpid(), getppid(), getpgrp());
		}
		return(0);
	}
	
	printf("parent: PID=%d, PPID=%d, PGID=%d\n", getpid(), getppid(), getpgrp());
	while (1) {
		printf("parent: ping %d\n", i++);
		sleep(3);
	}
	return(0);
}

 
