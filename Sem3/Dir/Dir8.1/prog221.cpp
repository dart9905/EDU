#include <stdio.h>
#include <unistd.h>


int main () {
    link("prog2.cpp", "prog221.cpp");//твёрдая ссылка
    symlink("prog2.cpp", "prog222.cpp");//мягая ссылка
    return 0;
}
//Documents/GitHub/EDU/Sem3/Dir/Dir8/
