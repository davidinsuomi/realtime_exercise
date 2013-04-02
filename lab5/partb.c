#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <errno.h>
	int main (void) {
	  pid_t pid,pid1;
	  char buf[20];
	  printf("Enter input (n = next, other input terminates):");
	  fgets(buf, 20, stdin);
	  while(buf[0] == 'n') {
	    pid = fork();
	    if (pid < 0) {
	      perror("Fork:");
	      exit(1);
	    }
	    if (pid == 0) {
	      pid1=fork();
	      if(pid1>0)      //child 1 teminate
            exit(0);

           sleep(2); // This is actually something real work
	      exit(0);

	    }
	    wait(NULL);
	    printf("Enter input (n = next, other input terminates):");
	    fgets(buf, 20, stdin);
	  }
	}
