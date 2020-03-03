//
//  main.cpp
//  vichmaty1
//
//  Created by macbook on 02.03.2020.
//  Copyright © 2020 macbook. All rights reserved.
//
#include <iostream>
#include "math.cpp"

#define SuperPuperDeBUG(vol)\
//vol;

#define PRINTtoFILE(vol)\
//vol;



const double PI = 3.14159265359;


int main(int argc, const char * argv[]) {
    /*
     
     CONST!!!!!!!!!!
     
     */
    //==============================
    const double    L = 9.81,
                    Gamma = 0.3,
                    G = 9.81,
                    U0 = 1.0,
                    V0 = 1.0;
    
    const double omega0 = sqrt(G / L),
    T = 2 * PI / omega0,
    tau = T / 20;
    int size_time = T * 3 / tau;
    
    
    /*
     точное решение (AN) из курса общей физики!!!!!
     */
    
    double U_an [size_time];
    if (G/L > Gamma * Gamma / L / L) {
        
        double omega = sqrt(G/L - Gamma * Gamma / L / L);
        double phi = atan(U0 * omega /(V0 + Gamma / L * U0));
        double A = U0 / sin(phi);
        for (int i = 0; i < size_time; i++) {
            U_an[i] = A * exp(-Gamma / L * tau * i) * sin(omega * tau * i + phi);
        }
    }
    /*
     явнуя схема Эйлера (EE)
     */
    
    double U_ee [size_time];
    double U_XX [size_time];
    U_ee [0] = U0;
    U_XX [0] = V0;
    
    
    for (int i = 0; i < size_time - 1; i++) {
        U_ee [i + 1] = U_ee [i] + tau * U_XX [i];
        U_XX [i + 1] = U_XX [i] - tau * (2 * Gamma * U_XX [i] + omega0 * omega0 * sin(U_ee [i]));
    }
    /*
     схема Рунге-Кутты 4го порядка (RK)
     */
    
    double U_rk [size_time];
    U_rk [0] = U0;
    
    double k1 = 0, k2 = 0, k3 = 0, k4 = 0;
    
    for (int i = 0; i < size_time - 1; i++) {
        k1 = tau * U_XX[i];
        k2 = tau * (U_XX [i] + 0.5 * k1);
        k3 = tau * (U_XX [i] + 0.5 * k2);
        k4 = tau * (U_XX [i] + k3);
        U_rk [i + 1] = U_rk [i] + (k1 + 2 * k2 + 2 * k3 + k4) / 6;
        k1 = tau * (- omega0 * omega0 * U_rk [i] - 2 * Gamma * U_XX [i]);
        k2 = tau * (- omega0 * omega0 * U_rk [i] - 2 * Gamma * (U_XX [i] + k1 / 2));
        k3 = tau * (- omega0 * omega0 * U_rk [i] - 2 * Gamma * (U_XX [i] + k2 / 2));
        k4 = tau * (- omega0 * omega0 * U_rk [i] - 2 * Gamma * (U_XX [i] + k3));
    }
    
    
    
    PRINTtoFILE(FILE *files = fopen ("Print.txt", "wt");)
    
    printf("num       U_an           U_ee           U_rk\n");
    PRINTtoFILE(fprintf(files, "num       U_an           U_ee           U_rk\n");)
    for (int i = 0; i < size_time; i++) {
        printf("%02d    % 10.8g   % 10.9g   % 10.9g\n", i, U_an[i], U_ee[i], U_rk [i]);
        PRINTtoFILE(fprintf (files,"%d %g %g %g\n", i, U_an[i], U_ee[i], U_rk [i]);)
    }
       
    PRINTtoFILE(fclose(files);)
    return 0;
}
