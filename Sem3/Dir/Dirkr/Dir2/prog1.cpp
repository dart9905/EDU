#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
/*
 запусти меня так:
 ./a.out 3
 или 3 или 4
 оно запустит 2, 3 и 4 файла соответственно а потом будет считать числа 2+1+0 или 3+2+1+0 или 4+3+2+1+0 соответственно
 */

int fun (int* prog_2, int* array_file, int* n) {
    
    *prog_2 = fork ();
    
    int val = 0;
    
    if (*n == 0)
        return 0;
    
    switch (*prog_2) {
        case 0:
            
            write(array_file [1], n, sizeof(int));
            
            break;
        case -1:
            
            printf ("error fork\n");
            
            break;
            
        default:
            
            *n = *n - 1;
            read (*array_file, &val, sizeof(int));
            
            int sum = fun (prog_2, array_file, n);
            
            return sum + val;
            
            break;
    }
    
    return 0;
}


int main (int argc, char * argv[]) {
    int array_file [2];
    
    if (pipe (array_file) == -1) {
        printf ("error pipe\n");
        return 0;
    };
    int prog_2 = 0;
    int n = (int) (argv [1] [0]) - (int) '0';
    printf("%d\n", n);
    
    int sum = fun (&prog_2, array_file, &n);
    
    
    if (prog_2 != 0) {
        printf("sum = %d\n", sum);
        close(*array_file);
        close(array_file [1]);
    }
    
    return 0;
}
