/* 
 * Opens a file and creates a child, which inherits the file descriptor.
 * The child writes into the file. 
 * The parent waits for the child to terminate, and then writes into the file too.
 * The bytes written by the parent will appear after the bytes written by the child.
 * This is because inherited file descriptors are copies in the spirit of dup.
 */

#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
	int fd, pid;
	
	fd = open(argv[1], O_RDWR|O_CREAT|O_TRUNC, S_IRWXU);
		
	pid = fork();
	
	if (!pid) {
		printf("hi from child\n");
		write(fd, "hello from child\n", 17);
		printf("child wrote into file\n");
		sleep(3);
		close(fd);
		printf("bye from child\n");
		return(0);
	}
	
	waitpid(pid,NULL,0); /* wait for child termination; what will happen if you remove this? */
	write(fd, "and hello from parent\n", 22);
	printf("parent wrote into file\n");
	close(fd);
	printf("bye from parent\n");
	return(0);
}

 
