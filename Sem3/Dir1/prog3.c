#include "stdio.h"
/*
 запускаемся копируемся далее дочерняя программа вызывает другую программу а родительская просто заканчивается 
*/

int main (int argc, char * argv []) {
    int a = fork ();
    switch (a) {
        case 0:
            
            printf("pr: getpid = %d\n", getpid());
            printf("pr: getppid = %d\n", getppid());
            
            break;
        case -1:
            
            printf ("er\n");
            break;
            
        default:
            printf("ch: getpid = %d\n",getpid());
            printf("ch: getppid = %d\n",getppid());
            execl("/Users/macbook/Documents/Dir/prog.out","/Users/macbook/Documents/Dir/prog.out",NULL);
            break;
    }
    return 0;
    
    return 0;
}
