#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
/*
 Mmap
 munmap
*/
int main () {
    int File = open("text.txt", O_RDWR);
    
    char* pstr = (char*)(mmap(NULL, sizeof(char)*8, PROT_WRITE|PROT_READ, MAP_SHARED, File, 0));
    
    printf("%s\n", pstr);
    
    pstr[0] = 'H';
    pstr[1] = 'e';
    pstr[2] = 'l';
    pstr[3] = 'l';
    pstr[4] = 'o';
    pstr[5] = ' ';
    pstr[6] = ' ';
    pstr[7] = '\0';
    
    munmap((void*)pstr, sizeof(char)*8);
    
    close(File);
    return 0;
}
//Documents/GitHub/EDU/Sem3/Dir/Dir9/
