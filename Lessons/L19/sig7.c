#include <unistd.h>
#include <signal.h>
#include <sys/time.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>

#define N 64

static void myhandler(int sig) { 
	write(STDOUT_FILENO,"got SIGALRM\n",12); 
}

int main(int argc, char *argv[]) {
	int n; 
	char data[N]; 
	struct sigaction action = {{0}};
	struct itimerval t = {{0}}; 
	
	action.sa_handler = myhandler;
	sigaction(SIGALRM,&action,NULL);
	
	t.it_value.tv_sec = atoi(argv[1]); // first tick
	t.it_value.tv_usec = 0;
	t.it_interval.tv_sec = atoi(argv[2]); // periodic tick
	t.it_interval.tv_usec = 0;
	
	setitimer(ITIMER_REAL,&t,NULL);
	printf("set timer\n");
	
	while (1) {
		n = read(STDIN_FILENO,data,N-1);
		if (n > 0) { 
			data[n] = '\0'; 
			printf("read (%d bytes): %s\n",n,data); 
		}
		else if (n == 0) { 
			printf("read (%d bytes): end of input\n",n); 
			break; 
		}
		else if (errno != EINTR) { 
			perror("read"); 
			break; 
		}
		else { 
			printf("read: interrupted, retrying\n"); 
		}
	}
	
	t.it_value.tv_sec = 0;
	t.it_value.tv_usec = 0;
	setitimer(ITIMER_REAL,&t,NULL);
	printf("cancel timer\n");  
	
	while (1) {
		n = read(STDIN_FILENO,data,N-1);
		if (n > 0) { 
			data[n] = '\0'; 
			printf("read (%d bytes): %s\n",n,data); 
		}
		else if (n == 0) { 
			printf("read (%d bytes): end of input\n",n); 
			break; 
		}
		else if (errno != EINTR) { 
			perror("read"); 
			break; 
		}
		else { 
			printf("read: interrupted, retrying\n"); 
		}
	}
	
	return(0);
}









 
