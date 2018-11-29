#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

/*
 \file prog.cpp
 \authors Khromov Alexey
 \version A2.3mac
 \date 13.10.2018
 \bug scanf() can enter the loop if the user enters a blank message, at the moment the problem is solved by an error message and the program exits from the abort () loop.
 \warning do not enter a blank message
 
 
 
 */


/*!
 \brief terminal messenger.
 
 Terminal messenger launched in the console of a single computer.
 */

///maximum allowable length of input string.
/*!
 Constant of the maximum value of the string length, the message entered by the user.
 */
const int SIZE_STR_MAX = 256;

///maximum allowed message buffer length.
/*!
 Constant of the maximum length of the buffer storing user messages.
 */
const int SIZE_BUF_MAX = 1024;



/*!
 \brief Opens or creates a fifo file using functions mknod () and open ().
 \param[in] namefile full file path.
 \return int File or error in case the file has not been opened.
 */
int openfile(char* namefile);

/*!
 \brief Displays the entire message buffer on the terminal screen.
 \param[in] File returned by openfile ().
 \param[out] buf pointer to the message buffer to write.
 \return 0.
 */
int show (int FILE, char* buf);

/*!
 \brief Writes the text of the message entered by the user to the common message buffer, and also displays the entire buffer on the screen, similar to the show () function.
 \param[in] File returned by openfile ().
 \param[out] buf pointer to the message buffer to write.
 \param[in] str pointer to the user's message string.
 \param[in] size_str message size.
 \return 0.
 */
int print (int FILE, char* buf, char* str, int size_str);

/*!
 \brief Prepares to close the fifo file or closes it before the end of the program.
 \param[in] File returned by openfile ().
 \param[out] buf pointer to the message buffer to write.
 \return 0.
 */
int closeprog (int FILE, char* buf);

/*!
 \brief Function for an adequate program crash when a user enters an empty message.
 \param[in] File returned by openfile ().
 \param[out] buf pointer to the message buffer to write.
 \return 0.
 */
int ERRORen(int FILE, char* buf);





int main () {
    
    int FILE = openfile("qwer.fifo");
    if (FILE == -1) {
        printf("NOT\n");
        return 0;
    }
    
    
    
    
    char str [SIZE_STR_MAX] = "";
    char buf [SIZE_BUF_MAX] = "";
    int size_str = 0;
    
    
    
    
    for (;strcmp(str, "exit") != 0;) {
        
        str[0] = '\0';
        printf(":");
        for (;scanf("%255[^\n]%*c", str) == 0; ERRORen (FILE, buf)) {};
        
        if (strcmp(str, "exit") != 0) {
            size_str = strlen(str);
            //printf("ln str >%i | str = [[%s]] | str == show{%i}\n", size_str, str, strcmp(str, "show"));
            
            if (strcmp(str, "show") == 0 || strlen(str) == 0) {
                show (FILE, buf);
            } else {
                print (FILE, buf, str, size_str);
            }
        }
        
    }
    
    closeprog(FILE, buf);
    
    return 0;
}
/*
 
 FUN
 
*/



int openfile(char* namefile) {
    
    umask(0);
    
    int num = 1;
    char str = '\0';
    int FILE = -1;
    
    
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
    
    printf("\nIf the program does not work or messages are not sent, try closing all windows and manually delete the fifo file, run the program again.\n\n");
    
    
    return FILE;
}


int show (int FILE, char* buf) {
    int size_buf = 0;
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



int print (int FILE, char* buf, char* str, int size_str) {
    int size_buf = 0;
    str[size_str] = '\n';
    size_str++;
    str[size_str] = '\0';
    size_str++;
    
    read(FILE, &size_buf, sizeof(int));
    
    if (size_buf != -1) {
        read(FILE, buf, sizeof(char) * size_buf);
        system("clear");
        
    } else {
        int
        int size_buf_end = -1;
        read(FILE, &size_buf, sizeof(int));
        read(FILE, buf, sizeof(char) * size_buf);
        system("clear");
        printf("ofline\n");
        
        write(FILE, &size_buf_end, sizeof(int));
        
    }
    
    
    printf("=============\n%s\n%s=============\n", buf, str);
    
    
    size_buf += (size_str - 1);
    if (size_buf >= SIZE_BUF_MAX) {
        size_buf = size_str;
        buf[0] = '\0';
        printf("Clear buf\n");
    }
    printf("size buf: %d\n", size_buf);
    
    write(FILE, &size_buf, sizeof(int));
    write(FILE, buf, sizeof(char) * (size_buf - size_str));
    write(FILE, str, sizeof(char) * size_str);
    
    return 0;
}




int closeprog (int FILE, char* buf) {
    int size_buf = 0;
    
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



int ERRORen(int FILE, char* buf) {
    printf("sorry, but before you enter the message, write it))) otherwise I will drop the program\n");
    closeprog(FILE, buf);
    abort ();
    return 0;
}

//Users/macbook/Documents/GitHub/EDU/Sem3/HW/Dir⁩1/
