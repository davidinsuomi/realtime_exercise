#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <sys/stat.h>
#include <stdlib.h>

int main(){
int sockfd, size;
struct sockaddr_un read_addr, write_addr;
char chr;
int i=0;
unlink("read.sock");
if((sockfd = socket(AF_UNIX,SOCK_DGRAM,0))<0)
    perror("read sockfd error");


read_addr.sun_family=AF_UNIX;
strcpy(read_addr.sun_path,"read.sock");
//client_addr.sun_family=AF_UNIX;
//strcpy(client_addr.sun_path,"write");

if((bind(sockfd,( struct sockaddr*)&read_addr,sizeof(read_addr)))<0)
     perror("read bind error");

    for(i=0;i<10;i++){
        size=sizeof(write_addr);
    if(((recvfrom(sockfd, &chr, 1, 0,(struct sockaddr*)&write_addr,&size))<0))
        perror("read receieve error");
    write(1,&chr,1);
    }
sendto(sockfd,  "OK", 2, 0,(struct sockaddr*)&write_addr, sizeof(write_addr));

exit(0);
}

