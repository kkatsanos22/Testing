/* 
 * This program creates a named pipe and then repeatedly opens it for reading.
 * The open call will return when another process opens the pipe for writing.
 * In a loop, the process reads int values from the pipe 
 * until there is no more data to read in which case the process re-opens the pipe.
 * The process exits and removes the pipe after reading 0.  
 */

#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
	int fd, val, n; 
	
	n=mkfifo(argv[1],S_IRWXU);
	if (n < 0) { perror("server: mkfifo"); }
	
	while (1) {
		printf("server: opening read end of pipe\n");
		fd = open(argv[1],O_RDONLY); /* open pipe read end */
		if (fd < 0) { perror("server: open"); return(1); } 
		
		printf("server: reading from pipe ...\n");
		do {
			n = read(fd, &val, sizeof(int)); 
			printf("server read %d bytes: %d\n", n, val);    
		} while ((n > 0) && (val > 0));
		
		if (n > 0) {
			break; // read value <=0; stop receiving
		}
		else if (n < 0) { 
			perror("server: read"); 
			return(1); 
		}
		else { 
			printf("server: end of input\n");  
			close(fd);
		}
	}
	
	close(fd);
	unlink(argv[1]);
	return(0);
}

