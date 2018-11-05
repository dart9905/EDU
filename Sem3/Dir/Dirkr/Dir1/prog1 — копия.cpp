#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>


int main () {
    FILE* file = fopen("text.txt", "w");
    fprintf (file, "%s", getenv("PWD"));
    printf ("%s", getenv("PWD"));
    return 0;
}
