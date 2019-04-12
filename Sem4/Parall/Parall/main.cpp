//
//  main.cpp
//  Parall
//
//  Created by macbook on 12/04/2019.
//  Copyright © 2019 macbook. All rights reserved.
//

#include <omp.h>
#include <stdio.h>
int main() {
#pragma omp parallel
    printf("Hello from thread %d, nthreads %d\n", omp_get_thread_num(), omp_get_num_threads());
}
