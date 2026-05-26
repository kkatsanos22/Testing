/*
 * The program opens a file, dups the file descriptor received via open,
 * and writes/reads some bytes into/from the file via both file descriptors,
 * illustrating the fact that they both share the same r/w position.
*/ 

#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

#define STRLEN 16

int main(int argc , char *argv[]) {
	int fd1,fd2, n;
	char str[STRLEN];

	printf("WARNING: You are about to open file \"%s\" with the O_TRUNC option; if the file exists, this will ***delete*** all its contents; to abort press ctrl-C else press any key to continue\n", argv[1]);
	getchar();
	
	fd1 = open(argv[1], O_RDWR|O_CREAT|O_TRUNC, S_IRWXU);
	if (fd1 <= 0) { perror("open"); return(1); }
	printf("fd1 = %d\n", fd1);
	getchar();

	fd2 = dup(fd1);
	if (fd2 < 0) { perror("dup"); return(1); }
	printf("fd2 = %d\n", fd2);
	getchar();

	n = write(fd1, "have a nice day", 15);
	if (n < 0) { perror("write"); return(1); }
	printf("wrote %d bytes via fd %d\n", n, fd1);
	getchar();
	
	n = write(fd2, " today", 6);
	if (n < 0) { perror("write"); return(1); }
	printf("wrote %d bytes via fd %d\n", n, fd2);
	getchar();
	
	n = lseek(fd2, 0, SEEK_SET);
	if (n < 0) { perror("lseek"); return(1); }
	printf("rest r/w position to %d via fd %d\n", n, fd2);
	getchar();
	
	n = read(fd1, str, STRLEN-1);
	if (n < 0) { perror("read"); return(1); }
	str[n] = '\0';
	printf("read %d bytes \'%s\' via fd %d\n", n, str, fd1);
	getchar();
	
	n = read(fd2, str, STRLEN-1);
	if (n < 0) { perror("read"); return(1); }
	str[n] = '\0';
	printf("read %d bytes \'%s\' via fd %d\n", n, str, fd2);
	getchar();
	
	n = close(fd1);
	if (n < 0) { perror("close"); return(1); }

	n = close(fd2);
	if (n < 0) { perror("close"); return(1); }
	
	return(0);
}