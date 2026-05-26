#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
	int s, s2, n, val; 
	struct sockaddr_un addr;
	
	s2 = socket(AF_UNIX, SOCK_STREAM, 0);
	
	addr.sun_family = AF_UNIX; 
	strcpy(addr.sun_path, argv[1]);
	bind(s2, (struct sockaddr *)&addr, sizeof(addr));
	
	listen(s2, 0);
	
	do {
		printf("waiting for new connection ...\n");
		s = accept(s2, NULL, NULL);
		printf("got new connection\n");
		do {
			printf("receiving ...\n");
			n = recv(s, &val, sizeof(int), 0); 
			//n = read(s, &val, sizeof(int));
			if (n < 0) { perror("receive"); break; }
			printf("received value %d (%d bytes)\n", val, n);
		} while ((n > 0) && (val != -1));
		printf("close connection\n");
		close(s);
	} while (val != -1); 
	
	close(s2); 
	unlink(argv[1]); 
	
	return(0);
}
