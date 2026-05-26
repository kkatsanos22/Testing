#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
	int s, n, val; 
	struct sockaddr_in addr;
	
	s = socket(AF_INET, SOCK_DGRAM, 0);
	
	addr.sin_family = AF_INET; 
	addr.sin_addr.s_addr = htonl(INADDR_ANY); 
	addr.sin_port = htons(atoi(argv[1]));
	bind(s, (struct sockaddr *)&addr, sizeof(addr));
	
	do {
		printf("receiving ...\n");
		n = recvfrom(s, &val, sizeof(int), 0, NULL, NULL); 
		if (n < 0) { perror("receive"); break; }
		printf("received value %d (%d bytes)\n", val, n);
	} while ((n > 0) && (val != -1));
	
	close(s); 
	
	return(0);
}
