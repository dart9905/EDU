#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

const int SIZE = 256;



int main()
{
    char message[SIZE] = "Hello";
    char buf[SIZE];
    int sock;
    struct sockaddr_in addr;
    
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if(sock < 0)
    {
        printf ("socket");
        return 1;
    }
    
    addr.sin_family = AF_INET;
    addr.sin_port = htons(10001);
    addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    if(connect(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0)
    {
        printf("connect");
        return 2;
    }
    
    send(sock, message, sizeof(message), 0);
    recv(sock, buf, sizeof(message), 0);
    
    printf("%s\n", buf);
    close(sock);
    
    return 0;
}


/*
 /Documents/GitHub/EDU/Sem3/Dir/Dir10
 */
