//
//  main.cpp
//  KR
//
//  Created by macbook on 05/04/2019.
//  Copyright © 2019 macbook. All rights reserved.
//

#include <iostream>
#include "timeme.hpp"
#include "fract.cpp"

int main(int argc, const char * argv[]) {
    // insert code here...
    try {
        //
        //
        //      frc::fract<...> A1(числитель,знаменатель,целая часть);
        //
        //
        frc::fract<int> A1(1,2,3);
        frc::fract<int> B1(0,2,0);
        
        frc::fract<int> C1 = A1 / B1;
        std::cout << C1 << std::endl;
        
        tmm::timehhmmss A(2, 0, 2);
        tmm::timehhmmss B(2, 0, 1);
        tmm::timehhmmss C = A - B;
        std::cout << C << std::endl;
        
    } catch (int i) {
        printf("Ошибка:");
        switch (i) {
            case 0:
                printf("%d -- отрицательное время\n", i);
                break;
            case 1:
                printf("%d -- деление на 0\n", i);
                break;
                
            default:
                break;
        }
    }
    return 0;
}
