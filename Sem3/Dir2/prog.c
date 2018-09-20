#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
/*
открываем и записываем инфу в файл
 cd /Users/macbook/Documents/GitHub/EDU/Sem3/Dir2
*/
int main () {
    
    int array_file [2] = {};
    
    if (pipe (array_file) == -1) {
        printf ("error pipe\n");
        return 0;
    };
    
    write(array_file [1], "Hello", sizeof(char)*6);
    
    char array_str [6] = "";
    
    read (array_file [0], array_str, sizeof(char)*6);
    
    printf("%s\n", array_str);
    
    close(array_file  [0]);
    close(array_file [1]);
    
    return 0;
}
