#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
	int s, n, val; 
	struct sockaddr_un addr;
	
	s = socket(AF_UNIX, SOCK_DGRAM, 0);
	
	addr.sun_family = AF_UNIX; 
	strcpy(addr.sun_path, argv[1]);
	bind(s, (struct sockaddr *)&addr, sizeof(addr));
	
	do {
		printf("receiving ...\n");
		n = recvfrom(s, &val, sizeof(int), 0, NULL, NULL); 
		if (n < 0) { perror("receive"); break; }
		printf("received value %d (%d bytes)\n", val, n);
	} while ((n > 0) && (val != -1));
	
	close(s); 
	unlink(argv[1]);
	
	return(0);
}
