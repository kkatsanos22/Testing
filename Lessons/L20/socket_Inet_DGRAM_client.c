#include <unistd.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
	int s, n, count; 
	struct sockaddr_in addr;
	
	count = atoi(argv[3]);
	
	s = socket(AF_INET, SOCK_DGRAM, 0);
	
	addr.sin_family = AF_INET;
	inet_aton(argv[1], &addr.sin_addr);
	addr.sin_port = htons(atoi(argv[2])); 
	
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

