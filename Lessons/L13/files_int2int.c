/*
 * The program writes into a file two integer values and closes the file.
 * Then it re-opens the file and reads the two integer values.
 * Open the file with xxd to see the actual byes written into / read from the file. 
*/ 

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc , char *argv[]) {
	int fd,res; 
	int i1, i2;
	
	printf("WARNING: You are about to open file \"%s\" with the O_TRUNC option; if the file exists, this will ***delete*** all its contents; to abort press ctrl-C else press any key to continue\n", argv[1]);
	getchar();
	
	fd = open(argv[1],O_WRONLY|O_CREAT|O_TRUNC,S_IRWXU);
	if (fd < 0) { perror("open"); return(1); }
	
	printf("Enter two integer values to be saved into the file: ");
	scanf("%d %d",&i1,&i2);
	
	res = write(fd,&i1,sizeof(int));
	if (res < 0) { perror("write"); return(1); }
	printf("wrote int value %d as %d bytes\n", i1, res);
	
	res = write(fd,&i2,sizeof(int));
	if (res < 0) { perror("write"); return(1); }
	printf("wrote int value %d as %d bytes\n", i2, res);
	
	printf("Closing file\n");
	close(fd);
	
	printf("Reopening file\n");
	fd = open(argv[1],O_RDONLY,0);
	if (fd < 0) { perror("open"); return(1); }
	
	res = read(fd,&i2,sizeof(int));
	printf("read %d bytes as int value %d\n",res, i2);
	
	res = read(fd,&i1,sizeof(int));
	printf("read %d bytes as int value %d\n",res, i1);
	
	close(fd);
	  
	return(0);
}
 
