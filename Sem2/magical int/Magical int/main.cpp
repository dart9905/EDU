//
//  main.cpp
//  Magical int
//
//  Created by macbook on 31.03.2018.
//  Copyright © 2018 macbook. All rights reserved.
//

#include <iostream>
#include <stdio.h>
#include "../resources/Magical_int.h"


int main() {
    mint a = 2;
    mint b = 1;
    a = a - 1;
    a = a - b;
    if (a == b)
        printf("2 * 2 = %i\n", a.data);
    a = 1;
    b = 0;
    if (a == b)
        printf("Да крч 1 = 0\n");
    return 0;
}
