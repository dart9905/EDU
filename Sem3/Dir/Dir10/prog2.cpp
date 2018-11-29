#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
/*
 Mmap
 munmap
*/
int main () {
    
    char buf[1024];
    
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    int len = 0;
    
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = 10001;
    addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    //bind(sockfd,, *addr, 16);
    bind(sockfd, (struct sockaddr*)&addr, sizeof(addr));
    for (;;) {
        
        recvfrom(sockfd, buf, 1024, 0, NULL, NULL);//(struct sockaddr*)&addr, &len);
        
        printf("%s\n", buf);
    }
    
    close(sockfd);
    
    return 0;
}
//Documents/GitHub/EDU/Sem3/Dir/Dir10/
