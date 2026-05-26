/*
 * The program writes into a file a string of 8 bytes
 * and then reads back the same contents while interpreting
 * these bytes as the binary encoding of two 4-byte integers.
 * Note how endianness affects the bytes order in multi-byte 
 * integer values. 
*/ 

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc , char *argv[]) {
	int fd,res; 
	int i1, i2;
	char str[]="wow!wow?";
	char *c;
	
	printf("WARNING: You are about to open file \"%s\" with the O_TRUNC option; if the file exists, this will ***delete*** all its contents; to abort press ctrl-C else press any key to continue\n", argv[1]);
	getchar();
	
	fd = open(argv[1],O_RDWR|O_CREAT|O_TRUNC,S_IRWXU);
	if (fd < 0) { perror("open"); return(1); }
	printf("opened/reset file and got fd with value %d", fd); 
	printf("; current r/w pos is %ld", lseek(fd,0,SEEK_CUR));
	getchar();
	
	res = write(fd,str,8);
	if (res < 0) { perror("write"); return(1); }
	printf("wrote %d bytes via fd %d: ",res, fd);
	printf("; current r/w pos is %ld", lseek(fd,0,SEEK_CUR));
	getchar();
	
	res = lseek(fd,0L,SEEK_SET);
	printf("; current r/w pos is %ld", lseek(fd,0,SEEK_CUR));
	getchar();
	
	res = read(fd,&i1,sizeof(int));
	printf("read %d bytes via fd %d: ",res, fd);
	printf("; current r/w pos is %ld", lseek(fd,0,SEEK_CUR));
	getchar();

	res = read(fd,&i2,sizeof(int));
	printf("read %d bytes via fd %d: ",res, fd);
	printf("; current r/w pos is %ld", lseek(fd,0,SEEK_CUR));
	getchar();
	
	printf("read int values %d(%x) and %d(%x)\n",i1,i1,i2,i2);
	c = (char *)&i1;
	printf("bytes of 1st int are %c(%x) %c(%x) %c(%x) %c(%x)\n", \
	       *c,*c,*(c+1),*(c+1),*(c+2),*(c+2),*(c+3),*(c+3));
	c = (char *)&i2;
	printf("bytes of 1st int are %c(%x) %c(%x) %c(%x) %c(%x)\n", \
	       *c,*c,*(c+1),*(c+1),*(c+2),*(c+2),*(c+3),*(c+3));
	close(fd);
	  
	return(0);
}
 
