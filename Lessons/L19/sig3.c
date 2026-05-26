#include <unistd.h>
#include <signal.h>
#include <errno.h>
#include <stdio.h>

#define N 64

static void myhandler(int sig) {
	write(STDOUT_FILENO,"got SIGINT\n",11);
}

int main(int argc, char *argv[]) {
	int n; 
	char data[N];
	struct sigaction action = {{0}};
	
	action.sa_handler = myhandler;
	//action.sa_handler = SIG_IGN;
	
	if ((argc == 2) && (argv[1][0] == 'r')) {
		printf("setting syscall restart flag\n");
		action.sa_flags = SA_RESTART;
	}
	else {
		printf("leaving flags to default\n");
	}
	
	sigaction(SIGINT,&action,NULL);
	
	while (1) {
		printf("reading from stdin\n");
		n = read(STDIN_FILENO,data,N-1);
		if (n > 0) { 
			data[n] = '\0'; 
			printf("%s\n", data); 
		}
		else if (n == 0) { 
			printf("end of input\n"); 
			break; 
		}
		else if (errno != EINTR) { 
			perror("read"); 		
		}
		else { 		
			printf("read interrupted, retrying\n"); 
		}
	}
	
	return(0);
}
