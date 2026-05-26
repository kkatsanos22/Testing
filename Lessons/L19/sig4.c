#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdio.h>

static void myhandler(int sig) {
	write(STDOUT_FILENO,"got SIGCHLD\n",12);
}

int main(int argc, char *argv[]) {
	pid_t pid; 
	int status, cnt, ret;
	struct sigaction action = {{0}};
	
	cnt = atoi(argv[1]);
	
	action.sa_handler = myhandler;
	action.sa_flags = SA_RESTART;
	sigaction(SIGCHLD,&action,NULL);
	
	if (!(pid=fork())) { 
		while (cnt > 0) {
			sleep(3);
			printf("hello from child\n");
			cnt--;
		}
		printf("child: bye\n");
		return(42);
	}
	
	while (1) {
		printf("parent: blocking for child\n");
		ret = waitpid(pid,&status,WUNTRACED|WCONTINUED);
		if (ret == -1) {
			perror("waitpid");
			return 1;
		}
		if (WIFEXITED(status)) {
			printf("child returned %d\n",WEXITSTATUS(status)); 
			break;
		}
		else if (WIFSIGNALED(status)) {
			printf("child terminated %d\n",WTERMSIG(status)); 
			break;
		}
		else if (WIFSTOPPED(status)) {
			printf("child stopped %d\n",WSTOPSIG(status));
		}
		else if (WIFCONTINUED(status)) {
			printf("child continued\n");
		}
	} 
	
	return(0);
}








 
