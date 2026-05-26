#include <unistd.h>
#include <signal.h>
#include <stdio.h>

static void myhandler(int sig) {
	write(STDOUT_FILENO,"got SIGINT\n",11);
}

int main(int argc, char *argv[]) {
	sigset_t s1,s2;
	struct sigaction action = {{0}};
	//int sig;
	
	action.sa_handler = myhandler;
	sigaction(SIGINT, &action, NULL);
	printf("own handler for SIGINT installed\n");
	
	sigemptyset(&s1); 
	sigaddset(&s1, SIGINT);
	
	while (1) {
		sigprocmask(SIG_BLOCK, &s1, NULL);
		printf("blocked SIGINT\n");
		sleep(10);
		sigpending(&s2);
		if (sigismember(&s2, SIGINT)) {
			printf("SIGINT is pending\n");
			//sigwait(&s1, &sig);  
			//printf("sigwait cleared signal %d\n", sig);
		}
		printf("unblocking SIGINT\n");
		sigprocmask(SIG_UNBLOCK, &s1, NULL);
		sleep(10);
	}  
	
	return(0);
}

