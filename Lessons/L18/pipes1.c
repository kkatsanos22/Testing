/*
 * This program creates a pipe and a child process. 
 * The child writes into the pipe the value of an increasing counter, 
 * while the parent reads these values from the pipe. 
 */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
	int fd[2], count, i, delay, res;
	
	count = atoi(argv[1]);
	delay = atoi(argv[2]);
	
	res = pipe(fd);
	if (res < 0) {
		perror("pipe");
		return(1);
	}

	if (!fork()) {
		close(fd[0]);
		for (i=0; i<count; i++) {
			if (delay > 0) {
				sleep(delay);
			}
			printf("child writing value %d\n", i);
			res = write(fd[1], &i, sizeof(int));
			if (res < 0) { perror("write"); return(1); } 
		}
		printf("child: bye\n");
		return(0);
	}
	
	close(fd[1]); // put this in comments and see what happens
	while ((res = read(fd[0], &i, sizeof(int))) > 0) {
		printf("parent: read value %d (%d bytes)\n", i, res);
	}
	
	if (res == 0) {
		printf("parent: end of input, bye\n");
	}
	else {
		perror("read");
	}
	return(0);
}


 
