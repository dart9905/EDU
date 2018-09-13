//
//  main.cpp
//  MyPrintf
//
//  Created by macbook on 17.03.2018.
//  Copyright © 2018 macbook. All rights reserved.
//
#include <stdint.h>

extern "C"
uint64_t MyPrintf(char*, ... );



int main(int argc, const char * argv[]) {
    
    uint64_t a = 17;
    char a1 = 'h';
    char* a2 = "big cat";
    MyPrintf("{%bb = %oo = %x%c = %dd %s %%}, and %c %s %x %d", a, a, a, a1, a, a2, 'I', "Love", 3802, 100);
    
    return 0;
}
