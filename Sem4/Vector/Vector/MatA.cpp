//
//  MatA.cpp
//  Vector
//
//  Created by macbook on 15/02/2019.
//  Copyright © 2019 macbook. All rights reserved.
//

#include "MatA.hpp"

namespace MatA {
    double ABS (Vector A) {
        return sqrt(A.x * A.x + A.y * A.y + A.z * A.z);
    }
}
