#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

const int SIZE = 256;


int main()
{
    int sock, listener;
    struct sockaddr_in addr;
    char buf[SIZE];
    int bytes_read;
    
    listener = socket(AF_INET, SOCK_STREAM, 0);
    if(listener < 0)
    {
        printf("socket");
        return 1;
    }
    
    addr.sin_family = AF_INET;
    addr.sin_port = htons(10001);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    if(bind(listener, (struct sockaddr *)&addr, sizeof(addr)) < 0)
    {
        printf("bind");
        return 2;
    }
    
    listen(listener, 1);
    
    while(1)
    {
        sock = accept(listener, NULL, NULL);
        if(sock < 0)
        {
            printf("accept");
            return 3;
        }
        
        while(1)
        {
            bytes_read = recv(sock, buf, SIZE, 0);
            if(bytes_read <= 0) break;
            send(sock, buf, bytes_read, 0);
        }
        
        close(sock);
    }
    
    return 0;
}
