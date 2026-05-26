#include <unistd.h>
#include <signal.h>
#include <stdio.h>

static void myhandler(int sig) {
	write(STDOUT_FILENO,"got SIGINT\n",11);
	//sleep(2);
}

int main(int argc, char *argv[]) {
	int i, res;
	struct sigaction oldaction, action = {{0}};
	
	if (argc != 2) {
		action.sa_handler = SIG_DFL; 
		printf("handler for SIGINT is SIG_DFL\n");
	} else if (argv[1][0] == 'i') {
		action.sa_handler = SIG_IGN; 
		printf("handler for SIGINT is SIG_IGN\n");
	} 
	else if (argv[1][0] == 'o') {
		action.sa_handler = myhandler; 
		printf("handler for SIGINT is own/custom handler\n");
	} 
	else {
		printf("wrong handler option\n");
		return(0);
	}
	
	printf("replacing handler for SIGINT\n");
	sigaction(SIGINT,&action,&oldaction);
	
	for (i=0; i<3; i++) {
		printf("going to sleep\n");
		res = sleep(10);
		//pause();
		printf("sleep returned = %d\n",res);
	}

	printf("restoring old handler for SIGINT\n");
	sigaction(SIGINT,&oldaction,NULL);  
	
	printf("going to sleep\n");
	res = sleep(10);
	printf("sleep returned = %d\n",res);
	
	return(0);
}
