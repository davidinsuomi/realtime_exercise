#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>

int main()
{
     int fd,i;
     char buff[5]="AAAA";
     fd=open("exlog1.txt",O_CREAT|O_RDWR,0700);
     for(i=0;i<100000;i++)
	{
     	write(fd,buff,4);
 	
	}
     close(fd);
     return 0;
}
