#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

const int SIZE = 256;

int main ()
{
    int sock;
    struct sockaddr_in addr;
    char buf [SIZE];
    int bytes_read;
    
    sock = socket (AF_INET, SOCK_DGRAM, 0);
    if (sock < 0)
    {
        printf ("socket");
        return 1;
    }
    
    addr.sin_family = AF_INET;
    addr.sin_port = htons (10001);
    addr.sin_addr.s_addr = htonl (INADDR_ANY);
    if (bind (sock, (struct sockaddr *)&addr, sizeof (addr)) < 0)
    {
        printf ("bind");
        return 2;
    }
    
    while(1)
    {
        bytes_read = recvfrom (sock, buf, SIZE, 0, NULL, NULL);
        buf[bytes_read] = '\0';
        printf("%s\n",buf);
    }
    
    return 0;
}
