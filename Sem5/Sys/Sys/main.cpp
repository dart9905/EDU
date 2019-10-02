//
//  main.cpp
//  Sys
//  Khromov Alexey
//  Created by macbook on 28/09/2019.
//  Copyright © 2019 macbook. All rights reserved.
//
#include <iostream>
#include "math.cpp"
#include "file.hpp"


int SearchLU (Matrix<double> &A, Matrix<double> &L, Matrix<double> &U, int SIZE);

int SolutionLU(Vector<double> &b, Vector<double> &x, Matrix<double> &A, int SIZE);




int main(int argc, const char * argv[]) {
    // insert code here...
    
    
    const char name[] = "matrix_t.txt";
    
    
    int state_func_ReadFile = 0;
    char *buf = Read_File_To_Buffer(name, &state_func_ReadFile);
    if (buf == nullptr) {
        printf("\n" "it's very bad!! ERROR in Read_File_To_Buffer: %d\n", state_func_ReadFile);
        return 1;
    }
    
    int SIZE = buf [0] - '0';
    
    Matrix<double> A (SIZE);
    Vector<double> x (SIZE);
    Vector<double> b (SIZE);
    
    A.BufToMatrix(buf);
    free(buf);
    //std::cout << "A = \n" << A << std::endl;
    
    
    
    for (int i = 0; i < SIZE; i++) {
        x [i] = i + 1;
    }
    b = A * x;
    //std::cout << "b = \n" << b << std::endl;
    
    
    if (SolutionLU(b, x, A, SIZE) == -1) {
        printf("it's very very very bad!!");
        return 0;
    }
    
    Vector<double> x1 (SIZE);
    for (int i = 0; i < SIZE; i++) {
        x1 [i] = x [i] - (i + 1);
    }
    printf("%lf\n", x1.abc());
    //std::cout << "x = \n" << x << std::endl;
    
    return 0;
}




int SolutionLU(Vector<double> &b, Vector<double> &x, Matrix<double> &A, int SIZE) {
    
    
    Matrix<double> L (SIZE);
    Matrix<double> U (SIZE);
    Vector<double> y (SIZE);
    
    
    if (SearchLU(A, L, U, SIZE) == -1) {
        printf("it's very very bad!!");
        return -1;
    }
    //std::cout << "L = \n" << L << std::endl;
    //std::cout << "U = \n" << U << std::endl;
    
    for (int i = 0, sum = 0; i < SIZE; i++, sum = 0) {
        for (int j = 0; j < i; j++) {
            sum += y [j] * L [i] [j];
        }
        y [i] = b [i] - sum;
    }
    
    for (int i = SIZE - 1, sum = 0; i >= 0; i--, sum = 0) {
        for (int j = SIZE - 1; j > i; j--) {
            sum += x [j] * U [i] [j];
        }
        x [i] = (y [i] - sum) / U [i] [i];
    }
    
    return 0;
}




int SearchLU (Matrix<double> &A, Matrix<double> &L, Matrix<double> &U, int SIZE) {
    
    
    if (!(A.nondegeneracy())) {
        printf("it's very bad!! ERROR: 1\n");
        return 0;
    }
    
    if (A [0] [0] == 0) {
        printf("it's very bad!! ERROR: 2\n");
        return 0;
    }
    
    U = A;
    
    
    
    for (int i = 0; i < SIZE; i++)
        for (int j = i; j < SIZE; j++)
            L [j] [i] = U [j] [i] / U [i] [i];
    
    for (int k = 1; k < SIZE; k++)
    {
        for (int i = k - 1; i < SIZE; i++)
            for (int j = i; j < SIZE; j++)
                L [j] [i] = U [j] [i] / U [i] [i];

        for (int i = k; i < SIZE; i++)
            for (int j = k - 1; j < SIZE; j++)
                U [i] [j] = U [i] [j] - L [i] [k - 1] * U [k - 1] [j];
    }
    
    
    Matrix<double> LU (SIZE);
    LU = L * U;
    
    if (!(LU == A)) {
        printf("it's very bad!! ERROR: 3\n");
        std::cout << "A = LU =\n" << LU << std::endl;
        return -1;
    }
    return 0;
}


