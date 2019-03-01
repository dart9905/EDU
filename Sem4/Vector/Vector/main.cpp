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
    /*
    MatA::Vector X (1,0,0);
    MatA::Vector Y (0,1,0);
    MatA::Vector Z = (2 * X) - +Y;
    if (X != Z) {
        std::cout << Z << std::endl;
    }
    //*/
    
    //*
    MatA::Matrix M(2);
    M[0][0] = 3;
    M[0][1] = 2;
    M[1][0] = 1;
    M[1][1] = 5;
    MatA::Matrix M1(2);
    M1[0][0] = 2;
    M1[0][1] = 3;
    M1[1][0] = 4;
    M1[1][1] = 5;
    
    
    MatA::Matrix M2(M1);
    
    std::cout << M << std::endl;
    std::cout << M1 << std::endl;
    M2 = (M - M1);
    std::cout << M2 << std::endl;
     //*/
    MatA::Complex A1(1,2);
    MatA::Complex A2(4);
    MatA::Complex A3(A2);
    MatA::Complex A4(A2);
    
    A3 *= -A1;
    A4 = A4 * A1 + 1;
    
    std::cout << "A1:" << A1 << std::endl;
    std::cout << "A2:" << A2 << std::endl;
    std::cout << "A3:" << A3 << std::endl;
    std::cout << "A4:" << A4 << std::endl;
    
    if (A3 > A4)
        std::cout << "LOL"<< std::endl;
    else
        std::cout << "Kek"<< std::endl;
    
    
    
    
    return 0;
}
