#include "stdio.h"

/*
 просто вызов другой программы execl
*/

int main (int argc, char * argv []) {
    execl("/Users/macbook/Documents/Dir/prog.out","/Users/macbook/Documents/Dir/prog.out",NULL);
    
    return 0;
}
