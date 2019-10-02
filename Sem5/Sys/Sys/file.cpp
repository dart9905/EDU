//
//  file.cpp
//  Sys
//
//  Created by macbook on 02/10/2019.
//  Copyright © 2019 macbook. All rights reserved.
//

#include "file.hpp"

FILE *open_file(const char *name, unsigned long *file_size, bool UNIX = false) {
    // Размер файла выдаётся в байтах
    // --------------------------------------------------------------------
    // В системе UNIX можно сделать проверку на существование и на
    // доступность чтения данного файла перед тем, как его открыть, и при
    // помощи fseek и ftell узнать размер файла (Переменной UNIX передать true).
    // Но для кроссплатформенности нужно использовать fstat (UNIX == false)
    // То есть: !(UNIX) => UNIX == false
    // --------------------------------------------------------------------

    assert(name != nullptr);
    assert(file_size != nullptr);

    FILE *file = nullptr;

    if (UNIX) { // Узнаём размер будучи в ОС на UNIX
        if (!access(name, 3) || !access(name, 4)) {  // Проверим доступность файла

            if ((file = fopen(name, "r")) != nullptr) {
                fseek(file, 0, SEEK_END);
                *file_size = ftell(file);
                fseek(file, 0, SEEK_SET);
            } else {
                printf("\n""ERROR open_file UNIX: %s nullptr \n", name);
            }

        } else {
            printf("\n""ERROR open_file UNIX: "
                   "the file %s is ", name);
            if (access(name, 0))
                printf("not present\n");
            else
                printf("access is denied\n");
        }

    } else {

        if ((file = fopen(name, "rb")) != nullptr) {
            struct stat file_specification{};
            if (!fstat(fileno(file), &file_specification)) {
                *file_size = file_specification.st_size;
            } else {
                printf("\n""ERROR open_file: %s nullptr \n", name);
            }
        } else {
            printf("\n""ERROR open_file: "
                   "the file %s is either not present or access is denied\n", name);
            perror("meow");
        }
    }
    return file;
}


char *Read_File_To_Buffer(const char *name, int *state_func, bool UNIX) {
    const unsigned amount_of_free_RAM = 300; //MB

    assert (name != nullptr);
    assert (state_func != nullptr);

    // Сам очистит буффер при ошибке
    // В конце ставит \n \0 для удобства конвертирования
    // state_func == 0 ошибки отсутствуют
    // state_func == 1 файл пустой
    // state_func == 2 ошибка чтения или записи в файл
    // state_func == 3 не хватает оперативной памяти для считывания текста

    unsigned long file_size = 0;
    bool error_read = false;
    FILE *file = open_file(name, &file_size, UNIX);

    if (file_size == 0) {
        *state_func = 1;
        if (file) fclose(file);
        return nullptr;
    }
    //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    /* Проверка на наличие RAM для buf
    struct sysinfo info = {}; // The toopenkiy CLion cannot handle it :((
    sysinfo(&info);
    if (info.freeram / (1024 * 1024) - file_size < amount_of_free_RAM) {
        printf("Read_File_To_Buffer: ERROR Not enough RAM for reading text");
        fclose(file);
        *state_func = 3;
        return nullptr;
    }
     //*/
    
    
    
    // В buf будет храниться весь файл name + знак '\0'
    char *buf = (char *) calloc(file_size + 1, sizeof(char));
    if (fread(buf, sizeof(char), file_size, file) != file_size) {
        if (feof(file)) {
            printf("Read_File_To_Buffer: Error fread file %s\n"
                   "feof(%s) == 1\n", name, name);
            error_read = true;
        } else if (ferror((file))) {
            printf("Read_File_To_Buffer: Error fread file %s\n"
                   "ferror(%s) == 1\n", name, name);
            error_read = true;
        }
    }

    fclose(file);

    if (error_read) {
        *state_func = 2;
        free(buf);
        return nullptr;
    }

    buf[file_size - 1] = '\n';
    buf[file_size] = '\0';
    *state_func = 0;
    return buf;
}
