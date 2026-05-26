/*
 * This program creates a pipe and a child process.
 * The childs redirects its stdout to the pipe and writes its arguments,
 * The parent redirects its stdin to the pipe and reads character by character 
 * until there is no more data. 
 */ 

#include <unistd.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
	int fd[2], i; 
	char c;
	
	pipe(fd);
	
	if (!fork()) {
		printf("This printf will set stdout to line buffered\n");  
		dup2(fd[1],STDOUT_FILENO); /* redirect stdout */
		close(fd[0]); close(fd[1]); /* close pipe ends */
		for (i=0; i<argc; i++) {
			sleep(3);
			printf("%s\n",argv[i]);
			fprintf(stderr, "child wrote: %s\n",argv[i]);
		}
		fprintf(stderr, "child bye\n");
		return(0);
	}
	
	dup2(fd[0],STDIN_FILENO); /* redirect stdin */
	close(fd[0]); close(fd[1]); /* close pipe ends */ 
	while (scanf("%c",&c) != EOF) {
		printf("parent read: %c\n",c); 
	}
	
	return(0);
} 
