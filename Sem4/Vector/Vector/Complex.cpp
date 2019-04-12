//
//  Complex.cpp
//
//  Created by macbook on 01/03/2019.
//  Copyright © 2019 macbook. All rights reserved.
//
#define ASSERT_MAT( expression ) \
if (expression) {\
\
} else {\
FILE *files = fopen ("LogFiles.txt", "at");\
\
fprintf(files, "==========ASSERT_MAT=========\n\n");\
fprintf(files, "ERROR:\nAssertion failed: %s\n   in file %s;\n   in line %i.\n", #expression, __FILE__, __LINE__);\
fprintf(files, "\n===========================\n\n");\
\
fclose(files);\
assert (expression);\
}

#include "Complex.hpp"
#include <cassert>
#include <iostream>


namespace MatA {
    Complex::Complex():a_(0), b_(0)
    {}
    Complex::Complex(float a):a_(a), b_(a)
    {}
    Complex::Complex(float a, float b):a_(a), b_(b)
    {}
    Complex::Complex(const Complex& A):a_(A.a_), b_(A.b_)
    {}
    
    Complex::~Complex() {
        a_ = 0; b_ = 0;
    }
    
    void Complex::set_a(float a) {
        a_ = a;
    }
    
    float Complex::get_a() {
        return a_;
    }
    
    void Complex::set_b(float b) {
        b_ = b;
    }
    float Complex::get_b() {
        return b_;
    }
    
    
    Complex& Complex::operator = (const Complex & arg) {
        a_ = arg.a_;
        b_ = arg.b_;
        return *this;
    }
    Complex& Complex::operator = (const float & arg) {
        a_ = arg;
        b_ = 0;
        return *this;
    }
    
    std::ostream& operator<< (std::ostream &out, const Complex &A)
    {
        out << "Complex(" << A.a_ << ", " << A.b_ << ")";
        
        return out;
    }
    
    std::istream& operator>> (std::istream &in, Complex &A)
    {
        in >> A.a_;
        in >> A.b_;
        return in;
    }
    
    
    Complex operator + (const Complex& A, const Complex& B)  {
        return Complex (A.a_ + B.a_, A.b_ + B.b_);
    }
    Complex operator * (const Complex& A, const Complex& B) {
        return Complex (A.a_ * B.a_ - A.b_ * B.b_, A.a_ * B.b_ + A.b_ * B.a_);
    }
    Complex operator - (const Complex& A, const Complex& B)  {
        return Complex (A.a_ - B.a_, A.b_ - B.b_);
    }
    Complex operator / (const Complex& A, const Complex& B) {
        ASSERT_MAT( ABS(B)!=0 )
        return Complex ((A.a_ * B.a_ - A.b_ * B.b_) / (B.a_ * B.a_ - B.b_ * B.b_), (A.b_ * B.a_ - A.a_ * B.b_) / (B.a_ * B.a_ - B.b_ * B.b_));
    }
    
    Complex operator + (const Complex& A, float a) {
        return Complex (A.a_ + a, A.b_);
    }
    Complex operator * (const Complex& A, float a) {
        return Complex (A.a_ * a, A.b_ * a);
    }
    Complex operator * (float a, const Complex& A) {
        return Complex (A.a_ * a, A.b_ * a);
    }
    Complex operator - (const Complex& A, float a) {
        return Complex (A.a_ - a, A.b_);
    }
    Complex operator / (const Complex& A, float a) {
        ASSERT_MAT( a!=0 )
        return Complex (A.a_ / a, A.b_ / a);
    }
    
    
    
    Complex operator - ( const Complex& A) {
        return Complex(-A.a_, -A.b_);
    }
    
    const Complex& operator + ( const Complex& A) {
        return A;
    }
    
    
    Complex Complex::operator += (const Complex& A) {
        a_+=A.a_;
        b_+=A.b_;
        return *this;
    }
    Complex Complex::operator -= (const Complex& A) {
        a_-=A.a_;
        b_-=A.b_;
        return *this;
    }
    Complex Complex::operator *= (const Complex& A) {
        float x = a_ * A.a_ - b_ * A.b_;
        float y = a_ * A.b_ + b_ * A.a_;
        a_= x;
        b_= y;
        return *this;
    }
    Complex Complex::operator /= (const Complex& A) {
        ASSERT_MAT( ABS(A)!=0 )
        float x = (a_ * A.a_ - b_ * A.b_) / (A.a_ * A.a_ - A.b_ * A.b_);
        float y = (b_ * A.a_ - a_ * A.b_) / (A.a_ * A.a_ - A.b_ * A.b_);
        a_ = x;
        b_ = y;
        return *this;
    }
    
    
    Complex Complex::operator += (float a) {
        a_+=a;
        return *this;
    }
    Complex Complex::operator -= (float a) {
        a_-=a;
        return *this;
    }
    Complex Complex::operator *= (float a) {
        a_*=a;
        b_*=a;
        return *this;
    }
    Complex Complex::operator /= (float a) {
        ASSERT_MAT( a!=0 )
        a_/=a;
        b_/=a;
        return *this;
    }
    
    
    bool Complex::operator == (const Complex& A) {
        if (ABS(A) == ABS(*this))
            return true;
        return false;
    }
    bool Complex::operator != (const Complex& A) {
        if (ABS(A) != ABS(*this))
            return true;
        return false;
    }
    bool Complex::operator >= (const Complex& A) {
        if (ABS(*this) >= ABS(A))
            return true;
        return false;
    }
    bool Complex::operator <= (const Complex& A) {
        if (ABS(*this) <= ABS(A))
            return true;
        return false;
    }
    bool Complex::operator > (const Complex& A) {
        if (ABS(*this) > ABS(A))
            return true;
        return false;
    }
    bool Complex::operator < (const Complex& A) {
        if (ABS(*this) < ABS(A))
            return true;
        return false;
    }
    
    bool Complex::operator == (float a) {
        if (a == ABS(*this))
            return true;
        return false;
    }
    bool Complex::operator != (float a) {
        if (a != ABS(*this))
            return true;
        return false;
    }
    bool Complex::operator >= (float a) {
        if (ABS(*this) >= a)
            return true;
        return false;
    }
    bool Complex::operator <= (float a) {
        if (ABS(*this) <= a)
            return true;
        return false;
    }
    bool Complex::operator > (float a) {
        if (ABS(*this) > a)
            return true;
        return false;
    }
    bool Complex::operator < (float a) {
        if (ABS(*this) < a)
            return true;
        return false;
    }
    
}


#undef ASSERT_MAT
