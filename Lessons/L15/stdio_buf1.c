/*
 * The program expects a file name as a first arugment. It creates or opens/truncates the file.
 * By default it will print a message to the terminal before redirecting stdout to the file,
 * which automatically sets the buffering policy for stdout to line buffered. 
 * When invoked with any additional argument(s), the program will immediately redirect stdout to the file,
 * which automatically sets the buffering policy for stdout to fully buffered. 
 * The buffering policy can be observed both for the output that is written in the file before flushing
 * and for the output that is written to the terminal after stdout is redirected back to it.   
*/ 

#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>

int main(int argc , char *argv[]) {
	int fd, oldout;   
	
	fd=open(argv[1],O_WRONLY|O_CREAT|O_TRUNC,S_IRWXU);
	
	if (!strcmp(argv[2],"LB")) {
		fprintf(stderr,"dbg: printing to stdout at this point will set the buffering policy to line-buffered\n"); 
		fprintf(stderr,"dbg: even when redirecting stdout to a file\n"); 
		printf("Print something\n");
	}
	else if (!strcmp(argv[2],"FB")) {
		fprintf(stderr,"dbg: not printing anything to stdout at this point will set the buffering policy to fully-buffered as a side-effect of redirection to a file\n"); 
		fprintf(stderr,"dbg: and this setting will remain even after redirecting stdout back to the terminal\n");
	}
	else {
		printf("specify LB or FB\n");
		return(1);
	}
	
	oldout = dup(STDOUT_FILENO);
	fprintf(stderr,"dbg: copied stdout");
	getchar();
	
	dup2(fd,STDOUT_FILENO); 
	fprintf(stderr,"dbg: redirected stdout"); 
	getchar();
	
	printf("hello world\n");
	fprintf(stderr,"dbg: wrote \"hello world\\n\" into stdout"); 
	getchar();
	
	fflush(stdout); 
	fprintf(stderr,"dbg: flushed stdout"); 
	getchar();
	
	dup2(oldout,STDOUT_FILENO); 
	fprintf(stderr,"dbg: restored stdout"); 
	getchar();
	
	printf("hello world again\n");
	fprintf(stderr,"dbg: wrote \"hello world again\\n\" into stdout"); 
	getchar();
	
	fflush(stdout); 
	fprintf(stderr,"dbg: flushed stdout"); 
	getchar();
	
	return(0);
}
 
