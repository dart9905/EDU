#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
/*
 открываем и записываем инфу в файл
 cd /Users/macbook/Documents/GitHub/EDU/Sem3/Dir2
 */
int main () {
    
    int array_file_1 [2] = {};
    int array_file_2 [2] = {};
    
    
    if (pipe (array_file_1) == -1) {
        printf ("error pipe array_file_1_and_2\n");
        return 0;
    };
    
    if (pipe (array_file_2) == -1) {
        printf ("error pipe array_file_1_and_3\n");
        return 0;
    };
    
    char array_str [13] = "";
    
    int prog_1_to_2 = fork ();
    int prog_1_to_3 = 0;
    
    
    
    
    switch (prog_1_to_2) {
        case 0:
            
            write(array_file_2 [1], "2 -> 1 Hello", sizeof(char) * 13);
            read(array_file_1 [0], array_str, sizeof(char) * 13);
            printf("1 -> 2: %s\n", array_str);
            
            write(array_file_1 [1], "2 -> 3 Hello", sizeof(char) * 13);
            read(array_file_2 [0], array_str, sizeof(char) * 13);
            printf("3 -> 2: %s\n", array_str);
            
            break;
        case -1:
            
            printf ("error fork prog_1_to_2\n");
            break;
            
        default:
            
            prog_1_to_3 = fork ();
            
            switch (prog_1_to_3) {
                case 0:
                    
                    
                    write(array_file_2 [1], "3 -> 1 Hello", sizeof(char) * 13);
                    read(array_file_1 [0], array_str, sizeof(char) * 13);
                    printf("2 -> 3: %s\n", array_str);
                    
                    write(array_file_2 [1], "3 -> 2 Hello", sizeof(char) * 13);
                    read(array_file_1 [0], array_str, sizeof(char) * 13);
                    printf("1 -> 3: %s\n", array_str);
                    
                    break;
                case -1:
                    
                    printf ("error fork prog_1_to_3\n");
                    break;
                    
                default:
                    
                    write(array_file_1 [1], "1 -> 2 Hello", sizeof(char) * 13);
                    read(array_file_2 [0], array_str, sizeof(char) * 13);
                    printf("2 -> 1: %s\n", array_str);
                    
                    write(array_file_1 [1], "1 -> 3 Hello", sizeof(char) * 13);
                    read(array_file_2 [0], array_str, sizeof(char) * 13);
                    printf("3 -> 1: %s\n", array_str);
                    
                    
                    break;
            }
            
            break;
    }
    //*
    close(array_file_1 [0]);
    close(array_file_1 [1]);
    close(array_file_2 [0]);
    close(array_file_2 [1]);
    //*/
    return 0;
}
