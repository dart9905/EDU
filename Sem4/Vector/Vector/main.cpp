//
//  main.cpp
//  Vector
//
//  Created by macbook on 08/02/2019.
//  Copyright © 2019 macbook. All rights reserved.
//

#include <iostream>

#include "lib.hpp"








int main(int argc, const char * argv[]) {
    
    
    Vector a(5);
    a.set_x(5);
    a.set_y(6);
    a.set_z(7);
    
    std::cout << a.get_x() << '\n' << a.get_y() << '\n' << a.get_z() << std::endl;
    return 0;
}
