#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/uio.h>

int main () {
    
    int FILE = open("/Users/macbook/Documents/GitHub/EDU/Sem3/Dir3/qwer.fifo", O_RDWR | O_CREAT);
    
    if (FILE == -1) {
        umask(0);
        
        switch (mknod("/Users/macbook/Documents/GitHub/EDU/Sem3/Dir3/qwer.fifo",S_IFIFO|0666,0)) {
            case -1:
                printf("NOT mknod\n");
                break;
            case 0:
                printf("OK mknod\n");
                break;
                printf("break\n");
            default:
                break;
        }
    }
    
    
    
    
    
    write(FILE, "Hello",sizeof(char)*6);
    char str [6];
    read(FILE,str, sizeof(char)*6);
    printf("%s\n", str);
    close(FILE);
    
    return 0;
}
///Users/macbook/Documents/GitHub/EDU/Sem3/Dir3⁩
