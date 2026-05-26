/*
 * The program expects as an argument the name of a file that is created or opened/truncated.
 * It illustrates how to write in the same file through two different file descriptors,
 * in combination with a possible truncation of the file using one of the descriptors.
*/ 

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc , char *argv[]) {
	int fd1, fd2, res;
	
	printf("WARNING: You are about to open file \"%s\" with the O_TRUNC option; if the file exists, this will ***delete*** all its contents; to abort press ctrl-C else press any key to continue\n", argv[1]);
	getchar();
	
	fd1 = open(argv[1], O_RDWR|O_CREAT|O_TRUNC, S_IRWXU);
	if (fd1 < 0) { perror("open"); return(1); }
	printf("opened/reset file, got fd1 with value %d", fd1); 
	printf("; current r/w pos is %ld", lseek(fd1,0,SEEK_CUR));
	getchar();
	
	fd2 = open(argv[1], O_RDWR,0);
	if (fd2 < 0) { perror("open"); return(1); }
	printf("opened file for a second time, got fd2 with value %d", fd2); 
	printf("; current r/w pos is %ld", lseek(fd2,0,SEEK_CUR));
	getchar();
	
	res = write(fd1, "a boring lecture", 16);
	if (res < 0) { perror("write"); return(1); }
	printf("wrote %d bytes via fd1", res);
	printf("; current r/w pos is %ld", lseek(fd1,0,SEEK_CUR));
	getchar();
	
	res = write(fd2, "a superb", 8);
	if (res < 0) { perror("write"); return(1); }
	printf("wrote %d bytes via fd2", res);
	printf("; current r/w pos is %ld", lseek(fd2,0,SEEK_CUR));
	getchar();
	
	res = ftruncate(fd1, 2);
	if (res < 0) { perror("ftruncate"); return(1); }
	printf("truncated file to 2 bytes via fd1");
	printf("; current r/w pos is %ld", lseek(fd1,0,SEEK_CUR));
	getchar();
	
	res = close(fd1);
	if (res < 0) { perror("close"); return(1); }
	printf("closed fd1"); 
	getchar();
	
	res = write(fd2, "lecture", 7);
	if (res < 0) { perror("write"); return(1); }
	printf("wrote %d bytes via fd2", res);
	printf("; current r/w pos is %ld", lseek(fd2,0,SEEK_CUR));
	getchar();
	
	res = close(fd2);
	if (res < 0) { perror("close"); return(1); }
	printf("closed fd2"); 
	getchar();
	
	return(0);
}
