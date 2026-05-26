#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
	int pid,i;
	
	pid = fork();
	
	if (pid == 0) {
		for (i=0; i<10; i++) { 
			sleep(1);
			printf("hello from child %d\n",i);
		}
		return(0);
	}
	
	if ((argc == 2) && !strcmp(argv[1],"kill")) {
		sleep(5);
		printf("parent: send SIGINT to child\n");
		kill(pid, SIGINT);
	}
	return(0);
}
