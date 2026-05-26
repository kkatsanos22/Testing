#include <unistd.h>
#include <signal.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
	pid_t pid; 
	sigset_t s; 
	int wflag, signum;
	
	wflag = ((argc > 1) && (argv[1][0] == 'w'));
	
	if (wflag) {
		sigemptyset(&s); 
		sigaddset(&s,SIGUSR1);
		sigprocmask(SIG_BLOCK,&s,NULL);
	}
	
	if (!(pid=fork())) {
		printf("Child has started.\n");
		if (wflag) {
			sigwait(&s,&signum); // wait for SIGUSR1
			printf("child: received signal %d\n", signum);
		}
		printf("this should print second\n");
		return(0);
	}
	
	sleep(1);
	
	printf("this should print first\n");
	if (wflag) {
		printf("parent: sent signal %d\n", SIGUSR1);
		kill(pid,SIGUSR1);
	}
	
	return(0);
}








 
