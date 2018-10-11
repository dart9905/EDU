#include "stdio.h"

/*
./a.out Hello world
Далее прога пишет привет мир
*/


int main (int argc, char * argv []) {
    for (int i = 1; i < argc; ++i)
        printf ("%s ", argv [i]);
    printf ("\n");
    return 0;
}
