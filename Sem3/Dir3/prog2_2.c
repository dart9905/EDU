#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/uio.h>

int main () {
    
    int FILE = open("/Users/macbook/Documents/GitHub/EDU/Sem3/Dir3/qwer.fifo", O_RDWR);
    if (FILE == -1) {
        printf("NOT\n");
        return 0;
    }
    
    char str [6];
    read(FILE,str, sizeof(char)*6);
    printf("%s\n", str);
    
    close(FILE);
    
    
    return 0;
}
///Users/macbook/Documents/GitHub/EDU/Sem3/Dir3⁩
