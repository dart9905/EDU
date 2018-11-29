#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>



int main () {
    
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = 10001;
    addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    //bind(sockfd,, *addr, 16);
    sendto(sockfd, "Hello", sizeof(char) * 6, 0, (struct sockaddr*)&addr, sizeof(addr));
    
    close(sockfd);
    
    return 0;
}
//Documents/GitHub/EDU/Sem3/Dir/Dir10/
