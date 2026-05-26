#include <unistd.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
	int s, n, count; 
	struct sockaddr_un addr;
	
	count = atoi(argv[2]);
	
	s = socket(AF_UNIX, SOCK_DGRAM, 0);
  
	addr.sun_family = AF_UNIX; 
	strcpy(addr.sun_path, argv[1]);
	
	do {
		sleep(3);
		printf("sending ...\n");
		n = sendto(s, &count, sizeof(int), 0, (struct sockaddr *)&addr, sizeof(addr));
		if (n <= 0) { perror("send"); break; }
		printf("sent value %d (%d bytes)\n", count, n);
	} while (--count > 0);
	
	close(s);
	
	return(0);
}





 
