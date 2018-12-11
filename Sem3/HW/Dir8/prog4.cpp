#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <dirent.h>


#include <sys/stat.h>
#include <time.h>

const int FILEMEGODIRSUPER = 16877;

int ls (char* namedir) {
    
    struct stat buf;
    
    
    if (stat (namedir, &buf) == -1)
        printf("Error stat %s\n", namedir);
    
    char* data1 = asctime(localtime(&buf.st_atime));
    data1[strlen(data1)-1] = '\0';
    
    printf("%d ", buf.st_mode);
    printf("%s ", data1);
    printf("%8lldb ", buf.st_size);
    printf("%s\n", namedir);

    return 0;
}


int fun (int num_read, int *num_file, int *num_file_whl, char* namedir) {
    DIR* dir_n;
    dirent* buf;
    struct stat buf_file;
    
    if ((dir_n = opendir(namedir)) == 0) {
        perror("Планету Оби-Ван потерял\n");
    }
    
    for (buf =  readdir(dir_n); buf != NULL; buf =  readdir(dir_n)) {
        
        ls (buf->d_name);
        /*
        if (buf_file.st_mode == FILEMEGODIRSUPER) {
            if (num_read == 1) {
                printf("%s\n", buf->d_name);
            }
            if ((strcmp(buf->d_name, ".") != 0) && (strcmp(buf->d_name, "..") != 0)) {
                fun(0, num_file, num_file_whl, buf->d_name);
            }
        } else {
            (*num_file)++;
            if (buf_file.st_nlink == 1)
                (*num_file_whl)++;
        }
        */
        
    }
    
    
    rewinddir(dir_n);
    closedir(dir_n);
    return 0;
}

int main (int argc, char **argv) {
    
    if (argc == 1) {
        printf("не тупи\n назвние введи\n");
        return 0;
    }
    int num_file = 0;
    int num_file_whl = 0;
    
    fun(1, &num_file, &num_file_whl, argv[1]);
    
    printf("колличество файлов: %d\n", num_file);
    printf("колличество файлов без жёстких связей: %d\n", num_file_whl);
    return 0;
}
/*
 /Users/macbook/Documents/GitHub/EDU/Sem3/HW/Dir8
 
*/
/*
 
 написать ls -l
 
 каталог
 
*/
