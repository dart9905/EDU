#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>

const int SIZE = 256;
const char* ch = "10.55.128.113";

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
    
    if ((inet_aton (ch, &addr.sin_addr)) == 0) {
        printf("inet\n");
        return 2;
    }
    
    if(bind(listener, (struct sockaddr *)&addr, sizeof(addr)) < 0)
    {
        printf("bind\n");
        return 2;
    }
    
    listen(listener, 32);
    
    for(;;) {
        sock = accept(listener, NULL, NULL);
        printf("%d\n", sock);
        if(sock < 0)
        {
            printf("accept\n");
            return 3;
        }
        //*
        for(;;) {
            bytes_read = recv(sock, buf, SIZE, 0);
            if (bytes_read <= 0)
                break;
            printf("%s\n", bytes_read);
            send(sock, buf, bytes_read, 0);
        }
        //*/
        
        close(sock);
    }
    
    return 0;
}
