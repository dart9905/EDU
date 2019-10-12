//
//  file.hpp
//  Sys
//
//  Created by macbook on 02/10/2019.
//  Copyright © 2019 macbook. All rights reserved.
//

#ifndef file_hpp
#define file_hpp

#include <stdio.h>
#include <cassert>
#include <unistd.h>
#include <sys/stat.h>

char *Read_File_To_Buffer(const char *name, int *state_func, bool UNIX = false);

FILE *open_file(const char *name, unsigned long *file_size, bool UNIX);

#endif /* file_hpp */
