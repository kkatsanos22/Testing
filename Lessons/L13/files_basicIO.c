/*
 * The program expects as an argument the name of a file that is created or opened/truncated.
 * It illustrates how to write in a file, how to read from a file, how to change the r/w position 
 * of the file descriptor, and how to obtain the current r/w position. It also illustrates 
 * how to truncate a file, the fact that this does not change the r/w position of the file descriptor, 
 * and the side-effect of writing from a position that is beyond the end of the file.
*/ 

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc , char *argv[]) {
	int fd, res, i;
	char str[]="hello world";
	
	printf("WARNING: You are about to open file \"%s\" with the O_TRUNC option; if the file exists, this will ***delete*** all its contents; to abort press ctrl-C else press any key to continue\n", argv[1]);
	getchar();
	
	fd = open(argv[1],O_RDWR|O_CREAT|O_TRUNC,S_IRWXU);
	if (fd < 0) { perror("open"); return(1); }
	printf("opened/reset file and got fd with value %d", fd); 
	printf("; current r/w pos is %ld", lseek(fd,0,SEEK_CUR));
	getchar();
	
	res = write(fd,str,5);
	if (res < 0) { perror("write"); return(1); }
	printf("wrote %d bytes via fd %d: ",res, fd);
	for (i=0; i<res; i++) { printf("%c ",str[i]); }
	printf("; current r/w pos is %ld", lseek(fd,0,SEEK_CUR));
	getchar();
	
	res = write(fd,&str[5],6);
	if (res < 0) { perror("write"); return(1); }
	printf("wrote %d bytes via fd %d: ",res, fd);
	for (i=0; i<res; i++) { printf("%c ",str[5+i]); }
	printf("; current r/w pos is %ld", lseek(fd,0,SEEK_CUR));
	getchar();
	
	res = write(fd," :-)",4);
	if (res < 0) { perror("write"); return(1); }
	printf("wrote %d bytes via fd %d: ",res, fd);
	for (i=0; i<res; i++) { printf("%c "," :-)"[i]); }
	printf("; current r/w pos is %ld", lseek(fd,0,SEEK_CUR));
	getchar();
	
	res = lseek(fd,(off_t)-3,SEEK_CUR);
	if (res < 0) { perror("lseek"); return(1); }
	printf("set file pos -3 from current pos of fd %d", fd); 
	printf("; current r/w pos is %ld", lseek(fd,0,SEEK_CUR));
	getchar();

	res = read(fd,str,5);
	if (res < 0) { perror("read"); return(1); }
	printf("read %d bytes via fd %d: ",res, fd);
	for (i=0; i<res; i++) { printf("%c ",str[i]); }
	printf("\nstr is: %s",str); 
	printf("; current r/w pos is %ld", lseek(fd,0,SEEK_CUR));
	getchar();
	
	res = read(fd,str,3);
	if (res < 0) { perror("read"); return(1); }
	printf("read %d bytes via fd %d: ",res, fd);
	if (res == 0) { printf("reached EOF"); }
	printf("; current r/w pos is %ld", lseek(fd,0,SEEK_CUR));
	getchar();
	
	res = lseek(fd,(off_t)-9,SEEK_CUR);
	if (res < 0) { perror("lseek"); return(1); }
	printf("set file pos -9 from current pos of fd %d", fd); 
	printf("; current r/w pos is %ld", lseek(fd,0,SEEK_CUR));
	getchar();
	
	res = write(fd,"there",5);
	if (res < 0) { perror("write"); return(1); }
	printf("wrote %d bytes via fd %d: ",res, fd);
	for (i=0; i<res; i++) { printf("%c ","there"[i]); }
	printf("; current r/w pos is %ld", lseek(fd,0,SEEK_CUR));
	getchar();
	
	res = ftruncate(fd,5);
	if (res < 0) { perror("ftruncate"); return(1); }
	printf("truncated file to 5 bytes via fd %d", fd);
	printf("; current r/w pos is %ld", lseek(fd,0,SEEK_CUR));
	getchar();
	
	res = write(fd,&str[6],5);
	if (res < 0) { perror("write"); return(1); }
	printf("wrote %d bytes via fd %d: ",res, fd);
	for (i=0; i<res; i++) { printf("%c ",str[6+i]); }
	printf("; current r/w pos is %ld", lseek(fd,0,SEEK_CUR));
	getchar();
	
	res = close(fd);
	if (res < 0) { perror("close"); return(1); }
	printf("closed file via fd %d\n", fd); 
	printf("; current r/w pos is %ld", lseek(fd,0,SEEK_CUR));
	getchar();
	
	return(0);
}
