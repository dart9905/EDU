#include "stdio.h"
/*
 С помощью команды мы выводим на консоль информацию о содержащихся в папке объектов
*/

int main (int argc, char * argv []) {
    execl("/bin/ls","/bin/ls","-l","/",NULL);
    
    return 0;
}
