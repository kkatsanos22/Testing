/*
 * This program creates a pipe and a child process.
 * The childs redirects its stdout to the pipe and runs program add.
 * The parent redirects its stdin to the pipe and reads character by character 
 * until there is no more data. 
 */ 

#include <unistd.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
	int fd[2];
	char c;
	
	pipe(fd);
	
	if (!fork()) { 
		dup2(fd[1],STDOUT_FILENO); /* redirect stdout */
		close(fd[0]); close(fd[1]);
		execl("./add", "add", "123", "456", NULL);
		return(1);
	}
	
	dup2(fd[0],STDIN_FILENO); /* redirect stdin */
	close(fd[0]); close(fd[1]);
	
	while (scanf("%c", &c) != EOF) {
		printf("parent read: %c\n", c); 
	}
	
	return(0);  
} 
