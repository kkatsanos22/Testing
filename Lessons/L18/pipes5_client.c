/* 
 * This program opens a named pipe for writing.
 * The open call will return when another process opens the pipe for reading.
 * The process writes into the pipe a series of int values and then exits. 
 * Note that by passing 0 as argument, the program will only send this value and exit. 
 */

#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
	int fd, count, n;
	
	printf("client: opening write end of pipe\n");
	fd = open(argv[1], O_WRONLY);  /* open pipe write end */
	if (fd < 0) { perror("client: open"); return(1); }
	
	count = atoi(argv[2]);
	printf("client: start writing\n");
	
	do {
		sleep(3);
		printf("client write: %d\n", count);
		n = write(fd, &count, sizeof(int));
		if (n < 0) { perror("write"); }
	} while (--count > 0);
	
	return(0);
}



 
