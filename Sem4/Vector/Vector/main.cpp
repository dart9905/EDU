//
//  main.cpp
//
//  Created by macbook on 08/02/2019.
//  Copyright © 2019 macbook. All rights reserved.
//

#include <iostream>


#include "MatA.hpp"
#include "Vector.cpp"
#include "Matrix.cpp"

int main(int argc, const char * argv[]) {
    
    try {
        int a = 0;
        MatA::Vector<int, 3> A(2), B(1), C;
        C = A + B;
        std::cout << C << std::endl;
    } catch (int i) {
        printf("Ошибка:");
        switch (i) {
            case 12:
                printf("%d -- неосвпадения размера\n", i);
                break;
            case 11:
                printf("%d -- несовпадения размера в конструкторе\n", i);
                break;
            case 10:
                printf("%d -- разных размеров\n", i);
                break;
            case 9:
                printf("%d -- выход за массив\n", i);
                break;
            case 8:
                printf("%d -- применимо для 3д вектора\n", i);
                break;
            case 7:
                printf("%d -- деление на хуй\n", i);
                break;

                
        }
    };
    
    return 0;
}
