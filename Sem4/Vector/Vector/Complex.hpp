//
//  Complex.hpp
//
//  Created by macbook on 01/03/2019.
//  Copyright © 2019 macbook. All rights reserved.
//

#ifndef Complex_hpp
#define Complex_hpp


#include <stdio.h>
#include <cassert>
#include <iostream>


namespace MatA {
    class Complex {
        friend float ABS(const Complex& A);
        float a_;
        float b_;
        
    public:
        Complex();
        Complex(float a);
        Complex(float a, float b);
        Complex(const Complex& A);
        
        ~Complex();
        
        void set_a(float a);
        float get_a();
        
        void set_b(float b);
        float get_b();
        
        
        
        Complex&   operator = (const Complex& arg);
        Complex&   operator = (const float& arg);
        
        
        friend Complex operator + (const Complex& A, const Complex& B);
        friend Complex operator * (const Complex& A, const Complex& B);
        friend Complex operator - (const Complex& A, const Complex& B);
        friend Complex operator / (const Complex& A, const Complex& B);
        
        friend Complex operator + (const Complex& A, float a);
        friend Complex operator * (const Complex& A, float a);
        friend Complex operator - (const Complex& A, float a);
        friend Complex operator / (const Complex& A, float a);
        friend Complex operator * (float a, const Complex& A);
        
        friend const Complex& operator + (const Complex& A);
        friend Complex operator - (const Complex& A);
        
        
        Complex operator += (const Complex& A);
        Complex operator -= (const Complex& A);
        Complex operator *= (const Complex& A);
        Complex operator /= (const Complex& A);
        
        
        Complex operator += (float a);
        Complex operator -= (float a);
        Complex operator *= (float a);
        Complex operator /= (float a);
        
        
        bool operator == (const Complex& A);
        bool operator != (const Complex& A);
        bool operator >= (const Complex& A);
        bool operator <= (const Complex& A);
        bool operator > (const Complex& A);
        bool operator < (const Complex& A);
        
        
        bool operator == (float a);
        bool operator != (float a);
        bool operator >= (float a);
        bool operator <= (float a);
        bool operator > (float a);
        bool operator < (float a);
        
        
        friend std::ostream& operator<< (std::ostream &out, const Complex &A);
        friend std::istream& operator>> (std::istream &in, Complex &A);
        
    };
}




#endif /* Complex_hpp */
