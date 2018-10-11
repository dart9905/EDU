#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

const int SIZE_STR_MAX = 256;
const int SIZE_BUF_MAX = 1024;

int openfile(char* namefile);
int show (int FILE, int size_buf, char* buf);
int print (int FILE, int size_buf, char* buf, char* str, int size_str);

int main () {
    
    int FILE = openfile("qwer.fifo");
    if (FILE == -1) {
        printf("NOT\n");
        return 0;
    }
    
    
    
    
    char str [SIZE_STR_MAX] = "";
    char buf [SIZE_BUF_MAX] = "";
    int size_buf = 0;
    int size_str = 0;
    
    
    
    for (;strcmp(str, "exit") != 0;) {
        printf(":");
        scanf("%255[^\n]%*c", str);
        
        if (strcmp(str, "exit") != 0) {
            size_str = strlen(str);
            //printf("ln str >%i | str = [[%s]] | str == show{%i}\n", size_str, str, strcmp(str, "show"));
            
            if (strcmp(str, "show") != 0) {
                print (FILE, size_buf, buf, str, size_str);
            } else {
                show (FILE, size_buf, buf);
                
            }
        }
         
        
    }
    
    read(FILE, &size_buf, sizeof(int));
    
    if (size_buf == -1) {
        close(FILE);
        printf("qwer.fifo close\n");
        system("rm qwer.fifo");
        printf("qwer.fifo del\n");
    } else {
        
        int size_buf_end = -1;
        
        read(FILE, buf, sizeof(char) * size_buf);
        
        
        write(FILE, &size_buf_end, sizeof(int));
        write(FILE, &size_buf, sizeof(int));
        write(FILE, buf, sizeof(char) * size_buf);
        
    }
    
    
    return 0;
}
/*
 
 FUN
 
*/



int openfile(char* namefile) {
    
    umask(0);
    
    int num = 1;
    char str = '\0';
    int FILE = 0;
    
    
    switch (mknod(namefile ,S_IFIFO|0666,0)) {
        case -1:
            printf("NOT mknod\n");
            FILE = open(namefile, O_RDWR);
            switch (FILE) {
                case -1:
                    printf("File not open\n");
                    break;
                    
                default:
                    printf("File open\n");
                    break;
            }
            
            break;
        case 0:
            printf("OK mknod\n");
            FILE = open(namefile, O_RDWR);
            switch (FILE) {
                case -1:
                    printf("File not create\n");
                    break;
                    
                default:
                    printf("Create file\n");
                    write(FILE, &num, sizeof(int));
                    write(FILE, &str, sizeof(char));
                    break;
            }
            
            break;
        default:
            printf("break\n");
            break;
    }
    
    
    return FILE;
}


int show (int FILE, int size_buf, char* buf) {
    read(FILE, &size_buf, sizeof(int));
    
    if (size_buf == -1) {
        
        int size_buf_end = -1;
        read(FILE, &size_buf, sizeof(int));
        read(FILE, buf, sizeof(char) * size_buf);
        system("clear");
        printf("ofline\n");
        
        write(FILE, &size_buf_end, sizeof(int));
    } else {
        
        read(FILE, buf, sizeof(char) * size_buf);
        system("clear");
        
    }
    
    printf("=============\n%s=============\n", buf);
    printf("size buf: %d\n", size_buf);
    write(FILE, &size_buf, sizeof(int));
    write(FILE, buf, sizeof(char) * size_buf);
    return 0;
}



int print (int FILE, int size_buf, char* buf, char* str, int size_str) {
    str[size_str] = '\n';
    size_str++;
    str[size_str] = '\0';
    size_str++;
    
    read(FILE, &size_buf, sizeof(int));
    
    if (size_buf != -1) {
        read(FILE, buf, sizeof(char) * size_buf);
        system("clear");
        
    } else {
        
        int size_buf_end = -1;
        read(FILE, &size_buf, sizeof(int));
        read(FILE, buf, sizeof(char) * size_buf);
        system("clear");
        printf("ofline\n");
        
        write(FILE, &size_buf_end, sizeof(int));
        
    }
    
    
    printf("=============\n%s\n%s=============\n", buf, str);
    
    
    size_buf += (size_str - 1);
    printf("size buf: %d\n", size_buf);
    
    write(FILE, &size_buf, sizeof(int));
    write(FILE, buf, sizeof(char) * (size_buf - size_str));
    write(FILE, str, sizeof(char) * size_str);
    
    return 0;
}

//Users/macbook/Documents/GitHub/EDU/Sem3/HW/Dir⁩1/
