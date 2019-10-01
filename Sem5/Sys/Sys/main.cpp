//
//  main.cpp
//  Sys
//
//  Created by macbook on 28/09/2019.
//  Copyright © 2019 macbook. All rights reserved.
//

#include <iostream>
#include "matrix.cpp"


int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    
    //*
    Matrix<double> A (2);
    Matrix<double> B (3);
    std::cout << "in A \n";
    std::cin >> A;
    std::cout << "A = \n" << A;

    std::cout << "\nin B \n";
    std::cin >> B;
    std::cout << "B = \n" << B;
    
            
    
    /*
    Matrix<double> C (3);
    C = A * B;
    
    std::cout << "out C = A * B\n" << C << std::endl;
    //*/
    
    
    return 0;
}
