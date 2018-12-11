#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

const int SIZE = 256;

int main ()
{
    
    char msg1 [SIZE] = "Hello";
    char msg2 [SIZE] = "Bye";
    int sock;
    struct sockaddr_in addr;
    
    sock = socket (AF_INET, SOCK_DGRAM, 0);
    if (sock < 0)
    {
        printf ("socket");
        return 1;
    }
    
    addr.sin_family = AF_INET;
    addr.sin_port = htons (10001);
    addr.sin_addr.s_addr = htonl (INADDR_LOOPBACK);
    sendto (sock, msg1, sizeof (msg1), 0,
           (struct sockaddr *)&addr, sizeof (addr));
    
    connect (sock, (struct sockaddr *)&addr, sizeof (addr));
    send (sock, msg2, sizeof (msg2), 0);
    
    close (sock);
    
    return 0;
}


/*
 /Documents/GitHub/EDU/Sem3/Dir/Dir10
 */
