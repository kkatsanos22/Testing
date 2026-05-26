/*
 * This program creates a pipe and a child process. 
 * The parent writes into the pipe two int values (received as program arguments),
 * waits for the child to terminate, and then reads an int value from the pipe.
 * The child reads two int values from the pipe, caclulates the sum and writes it into the pipe. 
 */ 

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
	int fd[2], pid, v1, v2, sum;
	
	pipe(fd);
	
	if (!(pid=fork())) {
		read(fd[0], &v1, sizeof(int));
		printf("child: read %d\n",v1);
		
		read(fd[0], &v2, sizeof(int));
		printf("child: read %d\n",v2);
		
		sum = v1+v2;
		write(fd[1], &sum, sizeof(int));
		printf("child: wrote %d\n",sum);
		return(0);
	}
	
	// see what happens if parent dies before/while executing one of the two instructions below
	v1 = atoi(argv[1]); 
	v2 = atoi(argv[2]); 

	printf("parent: writing %d\n",v1);
	write(fd[1], &v1, sizeof(int));
	
	printf("parent: writing %d\n",v2);
	write(fd[1], &v2, sizeof(int));
	
	waitpid(pid,NULL,0); // see what happens if you put this in comments
	
	read(fd[0], &sum, sizeof(int));  
	
	printf("parent: sum is %d\n",sum);
	return(0);
}