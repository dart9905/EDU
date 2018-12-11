#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <dirent.h>


#include <sys/stat.h>
#include <time.h>

const int FILEMEGODIRSUPER = 16877;


int fun (int num_read, int *num_file, int *num_file_whl, char* namedir, int lenamedir) {
    DIR* dir_n;
    dirent* buf;
    int size_dir = strlen(namedir);
    int size_file = 0;
    struct stat buf_file;
    
    if ((dir_n = opendir(namedir)) == 0) {
        perror("Планету Оби-Ван потерял\n");
    }
    
    for (buf =  readdir(dir_n); buf != NULL; buf =  readdir(dir_n)) {
        for (int i = lenamedir + 1, j = 0; j < strlen(buf->d_name); j++, i++) {
            namedir [i] = (buf->d_name)[j];
            namedir [i+1] = '\0';
        }
        namedir [lenamedir] = '/';
        if (stat (namedir, &buf_file) == -1)
            printf("\nError stat %s\n\n", namedir);
        namedir [lenamedir] = '\0';
        
        if (buf_file.st_mode == FILEMEGODIRSUPER) {
            if (num_read == 1) {
                printf("%s\n", buf->d_name);
            }
            if ((strcmp(buf->d_name, ".") != 0) && (strcmp(buf->d_name, "..") != 0)) {
                size_file = strlen (buf->d_name);
                char *name = new char[size_dir+size_file+256];
                for (int i = 0, j = size_dir+1; (i < size_dir) || (j < size_dir + size_file+1); i++, j++) {
                    if (i < size_dir)
                        name[i] = namedir[i];
                    if (i < size_file)
                        name[j] = (buf->d_name)[i];
                }
                name [size_dir] = '/';
                name [size_dir + size_file+1] = '\0';
                size_file = strlen(name);
                
                fun(0, num_file, num_file_whl, name, size_file);
                
                delete [] name;
                
            }
        } else {
            //printf("%s/%s\n", namedir, buf->d_name);
            
            (*num_file)++;
            if (buf_file.st_nlink == 1)
                (*num_file_whl)++;
             //*/
        }
        
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
    
    fun(1, &num_file, &num_file_whl, argv[1], strlen(argv[1]));
    
    printf("колличество файлов: %d\n", num_file);
    printf("колличество файлов без жёстких связей: %d\n", num_file_whl);
    return 0;
}
/*
 /Users/macbook/Documents/GitHub/EDU/Sem3/Dir/Dirkr2
 
*/
/*
 
 написать ls -l
 
 каталог
*/
