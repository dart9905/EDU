#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <sys/ipc.h>
#include <sys/shm.h>


/*
 \file
 \brief prog.cpp
 \authors Khromov Alexey
 \version A1.2mac
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
 \brief Messenger buffer class.
 
 This class stores a message buffer and controls all events occurring with the buffer.
 */
class message {
private:
    int _capacity; ///< a pointer to the current character of the end of the string in the buffer, meaning str.
    
public:
    
    /*!
     \brief Standard constructor.
     */
    message();
    
    /*!
     \brief The constructor which, when created, is oriented to the string arg, the buffer now points to it, and _data coincides with arg and _str points to the string from the second element.
     \param[in] arg pointer to the string, the size of the string must match SIZE_BUF_MAX.
     */
    message(char* arg);
    
    /*!
     \brief Standard destructor.
     */
    ~message();
    
    /*!
     \brief The operator equals the string, that is, appends it to the end of the current line of the _str buffer, focusing on the _capacity value, if there is not enough space in the buffer, the first values in the buffer are erased, meaning _str
     \param[in] arg pointer to the string, the string must not exceed SIZE_BUF_MAX otherwise characters whose indices exceed SIZE_BUF_MAX will be ignored.
     \return returns a link to this.
     */
    //message& operator = (char *arg);
    
    
    /*!
     \brief The operator equals the string, that is, appends it to the end of the current line of the _str buffer, focusing on the _capacity value, if there is not enough space in the buffer, the first values in the buffer are erased, meaning _str
     \param[in] arg pointer to the string, the string must not exceed SIZE_BUF_MAX otherwise characters whose indices exceed SIZE_BUF_MAX will be ignored.
     \return returns a link to this.
     */
    message& operator = (const char *arg);
    
    /*!
     \brief Appends it to the current buffer line's string _str based on the value of _capacity.
     \param[in] arg pointer to the string, the string must not exceed SIZE_BUF_MAX otherwise characters whose indices exceed SIZE_BUF_MAX will be ignored.
     \return 0.
     */
    //int add(char *arg);
    
    /*!
     \brief Appends it to the current buffer line's string _str based on the value of _capacity.
     \param[in] arg pointer to the string, the string must not exceed SIZE_BUF_MAX otherwise characters whose indices exceed SIZE_BUF_MAX will be ignored.
     \return 0.
     */
    int add(const char *arg);
    
    /*!
     \brief Shifts a string to the beginning by a specified number of characters.
     \param[in] len the length of the rubbed line.
     \return 0.
     */
    int mov(int len);
    
    /*!
     \brief The function considers the new value as a private variable _capacity, based on changes to the _str buffer, and provides the new real value to the user.
     \return private variable value _capacity.
     */
    int capacity();
    
    
    char* _data;///< pointer to full buffer.
    char* _str;///< pointer to string in buffer.
    int _size;///< line size or buffer size minus one.
};


/*!
 \brief Opens or creates a file using functions ftok(), shmget().
 \param[in] namefile full file path.
 \return pointer to string array.
 */
char* openfile(char* namefile);

/*!
 \brief Prepares to close files or closes it before the end of the program.
 \param[out] buf pointer to the message buffer to write.
 \return 0.
 */

int closeprog(message* buf);

/*!
 \brief Function for an adequate program crash when a user enters an empty message.
 \param[out] buf pointer to the message buffer to write.
 \return 0.
 */
int ERRORen(message* buf);

//*

int main () {
    
    message buf(openfile("file.txt"));
    if (buf._data == NULL) {
        printf("NOT\n");
        return 0;
    }
    
    
    
    
    char str [SIZE_STR_MAX] = "";
    int size_str = 0;
    
    
    
    for (;strcmp(str, "exit") != 0;) {
        
        str[0] = '\0';
        printf(":");
        for (;scanf("%255[^\n]%*c", str) == 0; ERRORen (&buf)) {};
        
        if (strcmp(str, "exit") != 0) {
            size_str = strlen(str);
            
            if (strcmp(str, "show") != 0 && strlen(str) != 0) {
                buf = str;
                buf = "\n";
            }
            system("clear");
            printf("online: %d\n", buf._data[0]);
            printf("==========\n%s==========\n", buf._str);
            printf("%d/%d\n", buf.capacity(), buf._size);
        }
        
    }
    
    closeprog(&buf);
    
    return 0;
}

/*
 
 FUN
 
*/

char* openfile(char* namefile) {
    
    int IDftok = ftok(namefile, 9);
    int IDshm = shmget(IDftok, sizeof(char) * SIZE_BUF_MAX, 0666|IPC_CREAT|IPC_EXCL);
    
    char* array = NULL;
    
    switch (IDshm) {
        case -1:
            IDshm = shmget(IDftok, sizeof(int)*3, 0666);
            
            switch (IDshm) {
                case -1:
                    printf("HERNI POLNAI\n");
                    return NULL;
                    break;
                    
                default:
                    //открытие
                    printf("File open\n");
                    array = (char*) shmat(IDshm, NULL, 0);
                    array[0]++;
                    break;
            }
            break;
            
        default:
            //первый запуск
            printf("Create file\n");
            array = (char*) shmat(IDshm, NULL, 0);
            array[0] = 1;
            array[1] = '\0';
            break;
    }
    
    return array;
}
//*




int closeprog (message* buf) {
    
    buf->_data[0] -- ;
    if (buf->_data[0] == 0) {
        shmdt(buf->_data);
    }
    return 0;
}



int ERRORen(message* buf) {
    printf("sorry, but before you enter the message, write it))) otherwise I will drop the program\n");
    closeprog(buf);
    abort ();
    return 0;
}
//*/













message:: message():
_data(NULL),
_str(NULL),
_size(SIZE_BUF_MAX - 1),
_capacity(1) {}

message:: message(char* arg):
_data(NULL),
_str(NULL),
_size(SIZE_BUF_MAX - 1),
_capacity(1) {
    _data = arg;
    _str = arg++;
    for (; *arg != '\0'; arg++, _capacity++) {}
}

message:: ~message() {
    _data = NULL;
    _str = NULL;
    _size = 0;
    _capacity = 0;
}
/*
message& message::operator = (char* arg) {
    capacity();
    if (_capacity + strlen(arg) >_size) {
        mov(_capacity + strlen(arg) - _size);
    }
    add(arg);
    return *this;
}
//*/
message& message::operator = (const char* arg) {
    capacity();
    if (_capacity + strlen(arg) >_size) {
        mov(_capacity + strlen(arg) - _size);
    }
    add(arg);
    return *this;
}
/*
int message::add(char *arg) {
    for (int i = 0; arg[i] != '\0'; i++, _capacity++) {
        _str [_capacity] = arg[i];
    }
    _str [_capacity] = '\0';
    return 0;
}
//*/
int message::add(const char *arg) {
    for (int i = 0; arg[i] != '\0'; i++, _capacity++) {
        _str [_capacity] = arg[i];
    }
    _str [_capacity] = '\0';
    return 0;
}

int message::mov(int len) {
    for (int i = 0; i < _size - len; i++, _capacity--) {
        _str[i] = _str[i + len];
    }
    return 0;
}

int message::capacity() {
    _capacity = 0;
    for (int i = 0; _str[i] != '\0'; i++, _capacity++) {}
    return _capacity;
}

//Users/macbook/Documents/GitHub/EDU/Sem3/HW/Dir⁩1/
