//
//  MatA.cpp
//  Vector
//
//  Created by macbook on 15/02/2019.
//  Copyright © 2019 macbook. All rights reserved.
//
#define ASSERT_MAT( expression ) \
if (expression) {\
\
} else {\
FILE *files = fopen ("LogFiles.txt", "at");\
\
fprintf(files, "==========ASSERT_MAT=========\n\n");\
fprintf(files, "ERROR:\nAssertion failed: %s\n   in file %s;\n   in line %i.\n", #expression, __FILE__, __LINE__);\
fprintf(files, "\n===========================\n\n");\
\
fclose(files);\
assert (expression);\
}

#include <cassert>
#include "MatA.hpp"

namespace MatA {
    float ABS (const Vector& A) {
        return sqrt(A.x_ * A.x_ + A.y_ * A.y_ + A.z_ * A.z_);
    }
    /*
    float ABS (const Vector2D& A) {
        return sqrt(A.x_ * A.x_ + A.y_ * A.y_);
    }
     //*/
    float ABS (const Complex& A) {
        return sqrt(A.a_ * A.a_ + A.b_ * A.b_);
    }
}
#undef ASSERT_MAT
