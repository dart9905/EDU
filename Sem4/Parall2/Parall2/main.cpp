//
//  main.cpp
//  Parall2
//
//  Created by macbook on 13/04/2019.
//  Copyright © 2019 macbook. All rights reserved.
//

#include <iostream>
#include <pthread.h>

void* fun (void*) {
    std::cout << "Hello, World!\n";
    return nullptr;
}

int main(int argc, const char * argv[]) {
    // insert code here...
    pthread_t thread [5];
    for (int i = 0; i < 5; i++) {
        pthread_attr_t attr;
        pthread_attr_init(&attr);
        pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
        pthread_create(&thread[i], &attr, fun, NULL);
    }

    for (int i = 0; i < 5; i++) {
        pthread_join(thread [i], NULL);
    }
    
    
    return 0;
}
