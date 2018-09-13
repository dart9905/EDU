//
//  main.cpp
//  Stack C++
//
//  Created by macbook on 06.03.2018.
//  Copyright © 2018 macbook. All rights reserved.
//

#include <iostream>
#include <cassert>

#include "../resources/Stack.h"

int main() {
    stackmy <int> stack;
    stack.push(1);
    stack.push(2);
    stack.push(3);
    stack.push(4);
    stack.push(5);
    stack.push(6);
    stack.push(7);
    printf("%i\n",stack.pop());
    printf("%i\n",stack.pop());
    printf("%i\n",stack.pop());
    return 0;
}
