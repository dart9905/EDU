//
//  main.cpp
//  SOR
//  Khromov Alexey
//  Created by macbook on 10.10.2019.
//  Copyright © 2019 macbook. All rights reserved.
//

#include <iostream>
#include "math.cpp"
#include "file.hpp"

#define SuperPuperDeBUG(vol)\
;


int SolutionSOR(Vector<double> &f, Vector<double> &x, Matrix<double> &A, int SIZE);

int SolutionGS(Vector<double> &f, Vector<double> &x, Matrix<double> &A, int SIZE);

int Polus(Matrix<double> &A, int SIZE);


int main(int argc, const char * argv[]) {
    // insert code here...
    const char name[] = "matrix_3.txt";
    
    
    int state_func_ReadFile = 0;
    char *buf = Read_File_To_Buffer(name, &state_func_ReadFile);
    if (buf == nullptr) {
        printf("\n" "it's very bad!! ERROR in Read_File_To_Buffer: %d\n", state_func_ReadFile);
        return 1;
    }
    
    int SIZE = buf [0] - '0';
    
    Matrix<double> A (SIZE);
    Vector<double> x0 (SIZE);
    Vector<double> x1 (SIZE);
    Vector<double> x2 (SIZE);
    Vector<double> f (SIZE);
    
    A.BufToMatrix(buf);
    free(buf);
    SuperPuperDeBUG(std::cout << "A = \n" << A << std::endl)
    
    
    for (int i = 0; i < SIZE; i++) {
        x0 [i] = i + 1;
        x1 [i] = 0;
        x2 [i] = 0;
    }
    SuperPuperDeBUG(std::cout << "x0 = \n" << x0 << std::endl)
    SuperPuperDeBUG(std::cout << "x1 = \n" << x1 << std::endl)
    SuperPuperDeBUG(std::cout << "x2 = \n" << x2 << std::endl)
    f = A * x0;
    
    
    SuperPuperDeBUG(std::cout << "f = \n" << f << std::endl)
    
    
    int SORsize = SolutionSOR(f, x1, A, SIZE);
    switch (SORsize) {
        case 0:
            break;
        
        case -1:
            printf(" A != A.T \n");
            break;
        
        case -2:
            printf(" A <= 0 \n");
            break;
        
        case -3:
            printf(" detA <= 0 \n");
            break;
            
        default:
            break;
    }
    SuperPuperDeBUG(std::cout << "x1 = \n" << x1 << std::endl)
    
    int GSsize = SolutionGS(f, x2, A, SIZE);
       switch (GSsize) {
           case 0:
               break;
           
           case -1:
               printf(" A != A.T \n");
               break;
           
           case -2:
               printf(" A <= 0 \n");
               break;
           
           case -3:
               printf(" detA <= 0 \n");
               break;
               
           default:
               break;
       }
       SuperPuperDeBUG(std::cout << "x2 = \n" << x2 << std::endl)
    
    if (SORsize < GSsize)
        printf("SOR convergence is faster than the Seidel method!!!\nSORsize = %i\nGSsize = %i\n", SORsize, GSsize);
    else
        if (SORsize > GSsize)
            printf("SOR convergence slower than the Seidel method!!!\nSORsize = %i\nGSsize = %i\n", SORsize, GSsize);
        else
            printf("SOR convergence equal Seidel method!!!\nSORsize = %i\nGSsize = %i\n", SORsize, GSsize);
    return 0;
}



int SolutionSOR(Vector<double> &f, Vector<double> &x, Matrix<double> &A, int SIZE) {
    SuperPuperDeBUG(printf("SolutionSOR: Ok\n"))
    if (A != A.T()) {
        return -1;
    }
    
    if (Polus(A, SIZE) != 1) {
        return -2;
    }
    
    if (A.det() <= 0) {
        return -3;
    }
    
    
    SuperPuperDeBUG(printf("SolutionSOR: A Ok\n"))
    
    double omega = 1.09;
    double epsilon = 0.000001;
    double r = epsilon * 2;
    double S1 = 0, S2 = 0;
    
    Vector<double> x0 (SIZE);
    Vector<double> f_0 (SIZE);
    
    //*
    int s = 0;
    
    printf("relaxation parameter = %lg\n", omega);
    for (; r > epsilon; s++) {
        x0 = x;
        
        for (int i = 0; i < SIZE; i++) {
            
            for (int j = 0; j < i; j++) {
                S1 +=  A[i] [j] * x [j];
            }
            
            for (int j = i + 1; j < SIZE; j++) {
                S2 += A[i] [j] * x0 [j];
            }
            
            x [i] = (1 - omega) * x0 [i] + omega / A [i] [i] * (f[i] - S1 - S2);
            S1 = 0;
            S2 = 0;
        }
        
        SuperPuperDeBUG(std::cout << "x[" << s << "] = \n" << x << std::endl)
        
        f_0 = (A * x);
        f_0 = f - f_0;
        r = f_0.abc();
        
        printf("SOR :: iteration number %i: Residual rate = %lg\n", s, r);
        
    }
    
    
    SuperPuperDeBUG(printf("SolutionSOR:%i Ok\n", s))
    
    
    return s;
}



int SolutionGS(Vector<double> &f, Vector<double> &x, Matrix<double> &A, int SIZE) {
    SuperPuperDeBUG(printf("SolutionGS: Ok\n"))
    if (A != A.T()) {
        return -1;
    }
    
    if (Polus(A, SIZE) != 1) {
        return -2;
    }
    
    if (A.det() <= 0) {
        return -3;
    }
    SuperPuperDeBUG(printf("SolutionGS: A Ok\n"))
    
    double epsilon = 0.000001;
    double r = epsilon * 2;
    double S1 = 0, S2 = 0;
    
    Vector<double> x0 (SIZE);
    Vector<double> f_0 (SIZE);
    
    //*
    int s = 0;
    for (; r > epsilon; s++) {
        x0 = x;
        
        for (int i = 0; i < SIZE; i++) {
            
            for (int j = 0; j < i; j++) {
                S1 +=  A[i] [j] * x [j];
            }
            
            for (int j = i + 1; j < SIZE; j++) {
                S2 += A[i] [j] * x0 [j];
            }
            
            x [i] = 1 / A [i] [i] * (f[i] - S1 - S2);
            S1 = 0;
            S2 = 0;
        }
        
        SuperPuperDeBUG(std::cout << "x[" << s << "] = \n" << x << std::endl)
        
        f_0 = (A * x);
        f_0 = f - f_0;
        r = f_0.abc();
        
        printf("GS :: iteration number %i: Residual rate = %lg\n", s, r);
        
    }
    
    
    SuperPuperDeBUG(printf("SolutionGS:%i Ok\n", s))
    
    
    return s;
}


int Polus(Matrix<double> &A, int SIZE) {
    
    int n = 0, m = 0;
    
    for (int i = 1; i <= SIZE; i+=2) {
        if (A.det(i) > 0) {
            m++;
        } else {
            n++;
        }
    }
    
    if ((m > 0) && (n == 0)) {
        return 1;
    }
    
    if ((n > 0) && (m == 0)) {
        return -1;
    }
    
    return 0;
}
