/*
 * The program expects a file name as a first arugment. It creates or opens/truncates the file.
 * By default it prints to the stdout (terminal) using the automatic line buffered policy.
 * If the second argument is equal to "n", the buffering policy is set to non buffered,
 * whereas is it is equal to "f", the buffering policy is set to fully buffered.
 * The effects of the buffering policy can be subsequently observed as the program writes 
 * to stdout single characters (and \n) in a loop. The same characters are written in the stderr
 * so that the user can track what the program is doing.
*/

#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main(int argc , char *argv[]) {
	char str[]="hello\nthere\nhow are you?\n";
	int res, i;
	
	if (!strcmp(argv[1],"LB")) {
		fprintf(stderr,"dbg: buffering policy for stdout set to line-buffered (default)\n");
	}
	else if (!strcmp(argv[1],"NB")) {
		res = setvbuf(stdout,NULL,_IONBF,0);
		if (res != 0) { perror("setvbuf"); } 
		fprintf(stderr,"dbg: buffering policy for stdout set to non-buffered\n");
	}
	else if (!strcmp(argv[1],"FB")) {
		res = setvbuf(stdout,NULL,_IOFBF,0);
		if (res != 0) { perror("setvbuf"); }
		fprintf(stderr,"dbg: buffering policy for stdout set to fully-buffered\n");
	}
	else {
		printf("specify LB or NB or FB\n");
		return(1);
	}
	
	fprintf(stderr,"dbg: start printing\n");
	
	for (i=0; i < strlen(str); i++) {
		sleep(1);
		fprintf(stderr," dbg: '%c' ",str[i]);
		printf("%c",str[i]);
	}
	
	return(0);
}
