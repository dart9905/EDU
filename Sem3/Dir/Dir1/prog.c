#include <unistd.h>
#include <stdio.h>
/*
 Производися 100 запусков параллельных процессов с помощью команды fork
*/
int fun (int b) {
    int a = fork ();
    switch (a) {
        case 0:
            
            printf("ch %i: getpid = %d\n", b ,getpid());
            printf("ch %i: getppid = %d\n", b ,getppid());
            
            b++;
            if (b < 100)
                fun (b);
            break;
        case -1:
            
            printf ("er %i\n", b);
            break;
            
        default:
            printf("pr %i: getch = %i\n", b , a);
            printf("pr %i: getpid = %d\n", b ,getpid());
            printf("pr %i: getppid = %d\n", b ,getppid());
            break;
    }
    return 0;
}

int main () {
    fun (0);
    return 0;
}
