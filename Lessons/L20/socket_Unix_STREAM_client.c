#include <unistd.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
	int s, n, count; 
	struct sockaddr_un addr;
	
	count = atoi(argv[2]);
	
	s = socket(AF_UNIX, SOCK_STREAM, 0);
	
	addr.sun_family = AF_UNIX; 
	strcpy(addr.sun_path, argv[1]);
	
	connect(s, (struct sockaddr *)&addr, sizeof(addr));
	
	do {
		sleep(3);
		printf("sending ...\n");
		n = send(s, &count, sizeof(int), 0);
		//n = write(s, &count, sizeof(int));
		if (n <= 0) { perror("send"); break; }
		printf("sent value %d (%d bytes)\n", count, n);
	} while (--count > 0);
	
	close(s);
	
	return(0);
}
