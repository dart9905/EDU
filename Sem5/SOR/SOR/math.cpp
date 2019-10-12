//
//  math.cpp
//  Sys
//  Khromov Alexey
//  Created by macbook on 01/10/2019.
//  Copyright © 2019 macbook. All rights reserved.
//


#include <cassert>
#include "iostream"
#include "math.hpp"

#include "vector.cpp"
#include "matrix.cpp"

#define ASSERT_MAT( expression ) \
if (expression) {\
\
} else {\
FILE *files = fopen ("LogFiles.txt", "at");\
\
fprintf(files, "==========ASSERT_MATH=========\n\n");\
fprintf(files, "ERROR:\nAssertion failed: %s\n   in file %s;\n   in line %i.\n", #expression, __FILE__, __LINE__);\
fprintf(files, "\n===========================\n\n");\
\
fclose(files);\
assert (expression);\
}



template <typename data_t>
Vector<data_t> operator * (Matrix<data_t>& A, Vector<data_t>& B) {
    ASSERT_MAT(A.size_ == B.size_)
    Vector<data_t> M (A.size_);
    for (int i = 0; i < M.size_; i++) {
        for (int j = 0; j < M.size_; j++) {
            M [i] += A [i] [j] * B [j];
        }
    }
    return M;
}


#undef ASSERT_MAT
