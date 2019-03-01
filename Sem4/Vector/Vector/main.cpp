//
//  main.cpp
//  Vector
//
//  Created by macbook on 08/02/2019.
//  Copyright © 2019 macbook. All rights reserved.
//

#include <iostream>


#include "MatA.hpp"


int main(int argc, const char * argv[]) {
    MatA::Vector X (1,0,0);
    MatA::Vector Y (0,1,0);
    MatA::Vector Z = (2 * X) - +Y;
    if (X != Z) {
        std::cout << Z << std::endl;
    }
    
    MatA::Matrix M(2);
    M[0][0] = 1;
    M[0][1] = 0;
    M[1][0] = 1;
    M[1][1] = 1;
    MatA::Matrix M1(2);
    M1[0][0] = 2;
    M1[0][1] = 3;
    M1[1][0] = 4;
    M1[1][1] = 5;
    
    
    MatA::Matrix M2(M1);
    
    M2 = M + 1;
    std::cout << M2 << std::endl;
    
    
    
    return 0;
}
