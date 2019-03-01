//
//  lib.hpp
//  Vector
//
//  Created by macbook on 08/02/2019.
//  Copyright © 2019 macbook. All rights reserved.
//


#include <cassert>
#include "iostream"
namespace MatA {
    
    class Vector
    {
        friend float ABS(const Vector& A);
    private:
        float x_, y_, z_;
        
    public:
        
        Vector();
        Vector(float A);
        Vector(float X, float Y, float Z);
        Vector(const Vector& A);
        
        ~Vector();
        
        void set_x(float X);
        float get_x();

        
        void set_y(float Y);
        float get_y();

        
        void set_z(float Z);
        float get_z();
        
        
        float& operator [] (int i);
        Vector&   operator = (const Vector & arg);
        Vector&   operator = (const float & arg);
        
        friend Vector operator + (const Vector& A, const Vector& B);
        friend float operator * (const Vector& A, const Vector& B);
        friend Vector operator - (const Vector& A, const Vector& B);
        friend Vector operator ^ (const Vector& A, const Vector& B);
        
        friend Vector operator + (const Vector& A, float a);
        friend Vector operator * (const Vector& A, float a);
        friend Vector operator - (const Vector& A, float a);
        friend Vector operator / (const Vector& A, float a);
        friend Vector operator * (float a, const Vector& A);
        
        friend Vector& operator ++ (Vector& A, int);
        friend Vector& operator -- (Vector& A, int);
        friend Vector& operator ++ (Vector& A);
        friend Vector& operator -- (Vector& A);
        
        friend const Vector& operator + (const Vector& A);
        friend Vector operator - (const Vector& A);
        
        Vector operator += (const Vector& A);
        Vector operator -= (const Vector& A);
        
        
        Vector operator += (float a);
        Vector operator -= (float a);
        Vector operator *= (float a);
        Vector operator /= (float a);
        
        bool operator == (const Vector& A);
        bool operator != (const Vector& A);
        bool operator >= (const Vector& A);
        bool operator <= (const Vector& A);
        bool operator > (const Vector& A);
        bool operator < (const Vector& A);
        
        
        
        friend std::ostream& operator<< (std::ostream &out, const Vector &A);
        friend std::istream& operator>> (std::istream &in, Vector &A);
    };

}
