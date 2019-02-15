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
    MatA::Vector Z = X - 1;
    
    std::cout << Z.get_x() << ' ' << Z.get_y() << ' ' << Z.get_z() << std::endl;
    return 0;
}
