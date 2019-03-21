//
//  MatA.hpp
//  Vector
//
//  Created by macbook on 15/02/2019.
//  Copyright © 2019 macbook. All rights reserved.
//

#ifndef MatA_hpp
#define MatA_hpp

#include <stdio.h>
#include <math.h>

#include "lib.hpp"
#include "Matrix.hpp"
#include "Complex.hpp"

namespace MatA {
    float ABS (const Vector& A);
    //float ABS (const Vector2D& A);
    float ABS (const Complex& A);
}

#endif /* MatA_hpp */

