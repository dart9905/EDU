//
//  main.cpp
//  N
//
//  Created by macbook on 11.05.2020.
//  Copyright © 2020 macbook. All rights reserved.
//
//cmod +x build.sh
//./build.sh
//
//

/*
 
 Начально краевая задача с уравнением переноса:
 
    (du / dt) + 2 * (du / dx) = x + t
 
    u(x = 0) = exp(-t)
 
    u(t = 0) = cos(\pi * x)
 
 Введем сетку:
 
 x_n = n * h; n = 0,...,N; N * h = 1;
 t_j = j * \tau; j = 0,...,J; J * \tau = 1;
 
 Схема тогда:
 
    (y_n^{j + 1} - y_n^j) / \tau + 2 * (y_n^j - y_{n - 1}^j) / h = x_n + t_j
 
    y_0^j = exp (-t_j)
 
    y_n^0 = cos(\pi * x_n)
 
 устойчика при 2\tau <= h или J >= 2N
 порядок аппроксимации О(+h)
 
            |(n;j + 1)
            |
            |
            |
 ___________|(n;j)
 (n - 1;j)
 
 
 тогда:
 
 y_n^{j + 1} = y_n^j + \tau * (x_n + t_j) - 2 * \tau / h * (y_n^j - y_{n - 1}^j)
 
 */


#include <iostream>
#include <cstdlib>
#include <math.h>



//============================================================================
//customization
/*
 For comparison with the analytical solution remove the comment from the body
 To disable the analytical solution add a comment to the body
 */
#define ANALIT(body)\
//body
//============================================================================

const double pi = 3.1415926535;

double mistake (double a, double b);

int solution (int j, int n, double* data, int N, double h, double tau);
int solution_analit (int j, int n, double* data, int N, double h, double tau);

double* accessdata (double* data, int N, int j, int n);


int main (int argc, char *argv[])
{
    
    int N = 40,
    J = 3 * N;
    
    
    double* data = (double *) calloc(N * J, sizeof(double));
    ANALIT(double* data_analit = (double *) calloc(N * J, sizeof(double));)
    
    //accessdata(data, N, j, n)
    
    double h = 1.0 / (double)N,
    tau = 1.0 / (double)J;
    
    //
    // y_0^0 = exp (0) = cos(0) = 1
    //
    
    *accessdata(data, N, 0, 0) = 1.0;
    
    for (int j = 0; j < J; j++) {
        for (int n = 0; n < N; n++) {
            solution(j, n, data, N, h, tau);
            ANALIT(solution_analit(j, n, data_analit, N, h, tau);)
        }
    }
    
    double maxmistake = 0, newmistake = 0;
    
    for (int j = 0; j < J; j++) {
        for (int n = 0; n < N; n++) {
            
            printf("data_       [%i] [%i] = %lg\n", j, n, *accessdata(data, N, j, n));
            //printf("%lg %i %i\n", j, n, *accessdata(data, N, j, n));
            
            
            
            ANALIT(
            printf("data_analit [%i] [%i] = %lg\n", j, n, *accessdata(data_analit, N, j, n));
            newmistake = mistake(*accessdata(data, N, j, n), *accessdata(data_analit, N, j, n));
            if (maxmistake < newmistake) {
                maxmistake = newmistake;
            }
            )
            
        }
    }
    
    ANALIT(printf("max mistake = %lg\n", maxmistake);)
    
    free(data);
    ANALIT(free(data_analit);)
    
    return 0;

}



double* accessdata (double* data, int N, int j, int n) {
    return (data + j * N + n);
}


int solution (int j, int n, double* data, int N, double h, double tau) {
    
    
    if (j == 0) {
        *accessdata(data, N, j, n) = cos(pi * n * h);
    }
    
    if (n == 0) {
        *accessdata(data, N, j, n) = exp(-j * tau);
    }
    
    if ((n != 0) && (j != 0)) {
        *accessdata(data, N, j, n) =
        *accessdata(data, N, j - 1, n)
        + tau * (n * h + tau * (j - 1))
        - 2 * tau / h * (*accessdata(data, N, j - 1, n) -  *accessdata(data, N, j - 1, n - 1));
    }
    
    return 0;
}


int solution_analit (int j, int n, double* data, int N, double h, double tau) {
    double x = n * h,
    t = tau * j;
    
    if (2 * t > x) {
        *accessdata(data, N, j, n) = x * t - t * t / 2 + (2 * t - x) * (2 * t - x) / 8 + exp(-t + x/2);
    } else
    {
        *accessdata(data, N, j, n) = x * t - t * t / 2 + cos(pi * (2 * t - x));
    }
    
    return 0;
}

double mistake (double a, double b) {
    if (a - b > b - a) {
        return a - b;
    }

    return b - b;
}
