//
//  main.cpp
//  Hash
//
//  Created by macbook on 15.04.2018.
//  Copyright © 2018 macbook. All rights reserved.
//

#include <iostream>
#include <cassert>
#include <ctype.h>

#include "../resources/List.h"
const char FILES_READ_NAME [] = "Text.txt";
const char FILES_WRITE_NAME1 [] = "TextW1.txt";
const char FILES_WRITE_NAME0 [] = "TextW0.txt";
const char FILES_WRITE_NAME2 [] = "TextW2.txt";
const char FILES_WRITE_NAME3 [] = "TextW3.txt";
const char FILES_WRITE_NAME4 [] = "TextW4.txt";
const char FILES_WRITE_NAME5 [] = "TextW5.txt";
const char FILES_WRITE_NAME6 [] = "TextW6.txt";



char* ReadFiles (const char* name_files, int *number_of_char);
int PrintFiles (const char* name_files, list<char*>* array, int* size);


unsigned int Hash1 (char* str);
unsigned int Hash0 (char* str);
unsigned int Hash2 (char* str);
unsigned int Hash3 (char* str);
unsigned int Hash4 (char* str);
unsigned int Hash5 (char* str);

int frol(int n, int len);



int TablFind (list<char*>* array, char* str, int* size, unsigned int (*Hash)(char*));



bool strcheck(char* arg1, cell_t<char*>* cell, int size);



int CraftString (list<char*>* array, int* size, unsigned int (*Hash)(char*), int text_length, char* buf, const char* name_files);



int Clear (list<char*>* array, int size);



int main(int argc, const char * argv[]) {
    int text_length = -1;
    char* buf = ReadFiles (FILES_READ_NAME, &text_length);
    int size = 1000;
    
    list<char*> array [size];
    
    CraftString (array, &size, Hash1, text_length, buf, FILES_WRITE_NAME1);
    Clear(array, size);
    CraftString (array, &size, Hash0, text_length, buf, FILES_WRITE_NAME0);
    Clear(array, size);
    CraftString (array, &size, Hash2, text_length, buf, FILES_WRITE_NAME2);
    Clear(array, size);
    CraftString (array, &size, Hash3, text_length, buf, FILES_WRITE_NAME3);
    Clear(array, size);
    CraftString (array, &size, Hash4, text_length, buf, FILES_WRITE_NAME4);
    Clear(array, size);
    CraftString (array, &size, Hash5, text_length, buf, FILES_WRITE_NAME5);
    Clear(array, size);
    
    
    return 0;
}



int Clear (list<char*>* array, int size) {
    for (int i = 0; i < size; i++) {
        (array [i]).Clear();
    }
    return 0;
}




int CraftString (list<char*>* array, int* size, unsigned int (*Hash)(char*), int text_length, char* buf, const char* name_files) {
    
    char* str = nullptr;
    for (int num = 0; num < text_length; num++) {
        
        if (std::isalpha(buf [num])) {
            
            
            buf [num] = std::tolower(buf [num]);
            str = &(buf [num]);
            
            for (;std::isalpha(buf [num]); num++)
                buf [num] = std::tolower(buf [num]);
                
            buf [num] = '\0';
            TablFind (array, str, size, Hash);
        }
    }
    PrintFiles(name_files, array, size);
    return 0;
}



char* ReadFiles (const char* name_files, int *number_of_char) {
    
    
    FILE *files = fopen (name_files, "rt");
    
    
    if (files == NULL)
    {
        assert(files != NULL);
    }
    
    fseek (files, 0, SEEK_END);
    *number_of_char = ftell(files);
    
    char* file_validation = new char [++*number_of_char];
    
    
    fseek (files, 0, SEEK_SET);
    fread (file_validation, sizeof (char), *number_of_char, files);
    fclose (files);
    file_validation [*number_of_char - 1] = '\0';
    return file_validation;
}



unsigned int Hash1 (char* str) {
    return 1;
}

unsigned int Hash0 (char* str) {
    return (int)(str [0]);
}

unsigned int Hash2 (char* str) {
    return strlen(str);
}

unsigned int Hash3 (char* str) {
    int sum = 0;
    for (int i = 0; str [i] != '\0'; sum += str [i], i++) {}
    return sum;
}

unsigned int Hash4 (char* str) {
    int h = 0;
    for (int i = 0; str [i] != '\0'; h = ((h << 5) + h) + str [i], i++) {}
    return h;
}

unsigned int Hash5 (char* str) {
    unsigned int h = 0;
    
    for (int i = 0; str [i] != '\0'; i++) {
        h = frol(h, 1) ^ str [i];
    }
    return h;
}

int frol (int n, int len) //ROL
{
    if ((n % 2) == 1)
    {
        return ((n << len) | 0x80);
    }
    return n << len;
}



int TablFind (list<char*>* array, char* str, int* size, unsigned int (*Hash)(char*)) {
    
    unsigned int h = Hash (str) % *size;
    if ((array [h])._end->_data == NULL)
        (array [h])._end->_data = str;
    else {
        (array [h])._cell = (array [h])._position_cell;
        
        if (strcheck(str, (array [h])._cell, (array [h])._size))
            (array [h]).addbe((array [h])._end, str);
            
    }
    
    return 0;
}


bool strcheck(char* arg1, cell_t<char*>* cell, int size) {
    int flag = 0;
    //bool flag = true;
    for (int j = 0; cell != nullptr; j++) {
        
        flag = 0;
        __asm__ ("xor %%rax, %%rax              \n\t"
                 "L1:                           \n"
                 "lodsb                         \n\t"
                 "test %%al, %%al               \n\t"
                 "jz EQU                        \n\t"
                 "xorb (%%rdi), %%al            \n\t"
                 "jnz EXIT                      \n\t"
                 "inc %%rdi                     \n\t"
                 "jmp L1                        \n\t"
                 "EQU:                          \n"
                 "xorb (%%rdi), %%al            \n\t"
                 "EXIT:                         \n"
                 "mov %%eax, %[x]               \n\t"
                 "\n\t"
                 : [x] "=r" (flag)
                 : [a] "S" (arg1), [b] "D" (cell->_data)
                 :
                 );
        if (flag == 0)
            return false;
        cell = cell->_next;
        //*/
        
    /*
        flag = true;
        if (strcmp(arg1, cell->_data) != 0) {
            flag = false;
        }
        
        if (flag)
            return false;
        cell = cell->_next;
        //*/
    }
    
    return true;
}






int PrintFiles (const char* name_files, list<char*>* array, int* size) {
    FILE *files = fopen (name_files, "wt");
    assert(files);
    
    for (int i = 0; i < *size; i++) {
        (array [i])._cell = (array [i])._position_cell;
        if ((array [i])._cell->_data != nullptr)
            fprintf(files, "%i; %i\n", i, (array [i])._size);
        else
            fprintf(files, "%i; 0\n", i);
    }
    
    fclose(files);
    return 0;
}
