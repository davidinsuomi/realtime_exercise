#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <signal.h>


void  main(int argc, char ** argv){
	int i;
	char chr;
   
    for(i=0;i<10;i++)
    {   chr='0'+i;
        write(1,chr,1);
        sleep(1);
    }


  
    exit(0);
    
    return;
}
 
