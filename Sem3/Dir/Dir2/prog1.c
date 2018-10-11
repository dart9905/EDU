#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
/*
 открываем и записываем инфу в файл
 cd /Users/macbook/Documents/GitHub/EDU/Sem3/Dir2
 */
int main () {
    
    int array_file [2];
    
    if (pipe (array_file) == -1) {
        printf ("error pipe\n");
        return 0;
    };
    
    int prog_2 = fork ();
    
    char array_str [6] = "";
    switch (prog_2) {
        case 0:
            
            write(array_file [1], "Hello w", sizeof(char)*8);
            
            break;
        case -1:
            
            printf ("error fork\n");
            
            break;
            
        default:
        
            read (*array_file, array_str, sizeof(char)*7);
            printf("%s\n", array_str);
            
            break;
    }
    
    close(*array_file);
    close(array_file [1]);
    
    return 0;
}
