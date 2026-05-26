/*
 * The program expects as an argument the name of a file that is created or opened/truncated.
 * It prints a string in stdout using the standard printf function, redirects stdout to the file 
 * prints another string via printf which is written in the file, and then restores stdout.
 * Similarly, it reads a string from stdin, redirects stdin to the file, reads again 
 * one or more strings until the end of inut (file) is reached, and restores stdin.
*/ 

#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

int main(int argc , char *argv[]) {
	int fd, oldoutfd, oldinfd, res; 
	char buf[128];
	
	printf("WARNING: You are about to open file \"%s\" with the O_TRUNC option; if the file exists, this will ***delete*** all its contents; to abort press ctrl-C else press any key to continue\n", argv[1]);
	getchar();
	
	fd = open(argv[1],O_RDWR|O_CREAT|O_TRUNC,S_IRWXU);
	if (fd < 0) { perror("open"); return(1); }
	fprintf(stderr,"dbg: created/reset file"); 
	getchar();
	
	fprintf(stderr,"dbg: print to stdout\n");
	printf("hello world\n");
	
	oldoutfd = dup(STDOUT_FILENO); // copy stdout
	if (oldoutfd < 0) { perror("dup"); return(1); }
	fprintf(stderr,"dbg: copied stdout\n");
	
	res = dup2(fd, STDOUT_FILENO); // redirect stdout
	if (res < 0) { perror("dup2"); return(1); }
	fprintf(stderr,"dbg: redirected stdout to file %s",argv[1]); 
	getchar();
	
	fprintf(stderr,"dbg: print \"hello world again\\n\"to stdout\n");
	printf("hello world again\n");
	getchar();
	
	res = dup2(oldoutfd, 1); // restore stdout
	if (res < 0) { perror("dup2"); return(1); }
	fprintf(stderr,"dbg: restored stdout\n"); 
	
	printf("enter something\n");
	
	fprintf(stderr,"dbg: reading from stdin\n");
	scanf("%s",buf); 
	printf("you entered: %s\n",buf);
	
	res = lseek(fd, 0, SEEK_SET);
	if (res < 0) { perror("lseek"); return(1); }
	fprintf(stderr,"dbg: set file pos to %d\n", res);
	
	oldinfd = dup(STDIN_FILENO); // copy stdin
	if (oldinfd < 0) { perror("dup"); return(1); }
	fprintf(stderr,"dbg: copied stdin\n");
	
	res = dup2(fd, STDIN_FILENO); // redirect stdin
	if (res < 0) { perror("dup2"); return(1); }
	fprintf(stderr,"dbg: redirected stdin to file %s\n",argv[1]);
	
	fprintf(stderr,"dbg: reading from stdin\n");
	while (scanf("%s",buf) != EOF) { 
		printf("%s\n",buf);
	}
	
	res = dup2(oldinfd, STDIN_FILENO); // restore stdin
	if (res < 0) { perror("dup2"); return(1); }
	fprintf(stderr,"dbg: restored stdin\n");
	
	printf("enter something (Crtl-D to exit)\n");
	while (scanf("%s",buf) != EOF) { 
		printf("%s\n",buf);
	}
	
	close(fd);
	close(oldoutfd);
	close(oldinfd);
	
	return(0);
}
 
