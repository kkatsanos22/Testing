/*
 * The program reads from stdin and writes into stdout 
 * via the read/write syscalls and the default file descriptors.
*/ 

#include <unistd.h>
#include <stdio.h>

#define STRLEN 32

int main(int argc , char *argv[]) {
	int n; 
	char str[STRLEN];
	
	printf("Enter input (Crtl-D to exit)\n");	
	
	do {
		printf("waiting to read ...\n");
		n = read(STDIN_FILENO, str, STRLEN);
		if (n < 0) { perror("read"); return(1); }
		printf("--read %d bytes from stdin (fd %d), writing back to stdout (fd %d)--\n",n, STDIN_FILENO, STDOUT_FILENO); 
		// echo whatever was read
		n = write(STDOUT_FILENO, str, n);
		if (n < 0) { perror("write"); return(1); }
	} while (n > 0);
	
	printf("end of input\n"); 
				
	return(0);
}
 
