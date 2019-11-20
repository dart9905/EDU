//
//  main.cpp
//  N
//
//  Created by macbook on 18.11.2019.
//  Copyright © 2019 macbook. All rights reserved.
//

#include <iostream>
#include "math.cpp"
#include "file.hpp"

#define SuperPuperDeBUG(vol)\
//vol;


int SearchLU (Matrix<double> &A, Matrix<double> &L, Matrix<double> &U, int SIZE);

int SolutionLU(Vector<double> &b, Vector<double> &x, Matrix<double> &A, int SIZE);



int main(int argc, const char * argv[]) {
    
    const char *name = argv[1];
    
    SuperPuperDeBUG(printf("%s\n",argv[1]))
    

    int state_func_ReadFile = 0;
    char *buf = Read_File_To_Buffer(name, &state_func_ReadFile);
    if (buf == nullptr) {
        printf("\n" "it's very bad!! ERROR in Read_File_To_Buffer: %d\n", state_func_ReadFile);
        return 1;
    }
    
    int SIZE = buf [0] - '0';
    
    Matrix<double> A (SIZE);
    Matrix<double> I (SIZE);
    Vector<double> F (SIZE);
    Vector<double> u (SIZE);
    Vector<double> x (SIZE);
    double epsilon = 0.000001;
    double r = epsilon * 2;
    
    
    A.BufToMatrix(buf);
    free(buf);
    SuperPuperDeBUG(std::cout << "A = \n" << A << std::endl)
    
    
    
    if (!(A.symmetry())) {
        printf("\n" "it's very bad!! ERROR the matrix A is asymmetric!\n");
        return 1;
    }
    if (!(A.positive())) {
        printf("\n" "it's very bad!! ERROR the matrix A is not positive!\n");
        return 1;
    }

    I = A;
    
    for (int i = 0; i < SIZE; i++) {
        F [i] = F [i] - exp(- u [i]);
        I [i] [i] = A [i] [i] + exp(- u [i]);
    }
    
    
    for (int s = 0; r > epsilon; s++) {
        
        
        SuperPuperDeBUG(std::cout << "F = \n" << F << std::endl)
        SuperPuperDeBUG(std::cout << "I = \n" << I << std::endl)
        
        if (SolutionLU(F, x, I, SIZE) == -1) {
            printf("it's very very very bad!!");
            return 0;
        }
        
        u = u - x;
        F = A * u;
        for (int i = 0; i < SIZE; i++) {
            F [i] = F [i] - exp(- u [i]);
            I [i] [i] = A [i] [i] + exp(- u [i]);
        }
        r = F.abc();
        
        printf("Iteration number %i: Residual rate = %lg\n", s, r);
        std::cout << "u = \n" << u << std::endl;
    }
    
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
    //*
    if (A [0] [0] == 0) {
        printf("it's very bad!! ERROR: 2\n");
        return 0;
    }
    //*/
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
    
    SuperPuperDeBUG(std::cout << "L = \n" << L << std::endl)
    SuperPuperDeBUG(std::cout << "U = \n" << U << std::endl)
    /*
    Matrix<double> LU (SIZE);
    LU = L * U;
    
    if (A != LU) {
        printf("it's very bad!! ERROR: 3\n");
        SuperPuperDeBUG(std::cout << "A = \n" << A << std::endl)
        SuperPuperDeBUG(std::cout << "A = LU =\n" << LU << std::endl)
        return -1;
    }
    //*/
    return 0;
}


