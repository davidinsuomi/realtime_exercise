#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>

int main()
{
     int fd,i;
     char buff[5]="AAAA";
     fd=open("exlog2.txt",O_CREAT|O_RDWR,0700);
     for(i=0;i<100000;i++)
	{
     	write(fd,buff,4);
	lseek(fd,0L,SEEK_END);
 	
	}
     close(fd);
     return 0;
}
