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
    /*
    class Vector_0
    {
    public:
        virtual void set_x(float X);
        virtual float get_x();
        
        
        virtual void set_y(float Y);
        virtual float get_y();
        
        
        virtual void set_z(float Z);
        virtual float get_z();
        
        
        virtual float& operator [] (int i);
        
        virtual bool operator == (const Vector_0& A);
        virtual bool operator != (const Vector_0& A);
        virtual bool operator >= (const Vector_0& A);
        virtual bool operator <= (const Vector_0& A);
        virtual bool operator >  (const Vector_0& A);
        virtual bool operator <  (const Vector_0& A);
    };
    //*/
    class Vector//: public Vector_0
    {
        friend float ABS(const Vector& A);
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
    /*
    class Vector2D//: public Vector
    {
        friend float ABS(const Vector2D& A);
        float x_, y_;
    public:
        
        Vector2D();
        Vector2D(float A);
        Vector2D(float X, float Y);
        Vector2D(const Vector2D& A);
        
        ~Vector2D();
        
        void set_x(float X);
        float get_x();
        
        
        void set_y(float Y);
        float get_y();
        
        
        float& operator [] (int i);
        Vector2D&   operator = (const Vector2D & arg);
        Vector2D&   operator = (const float & arg);
        
        friend Vector2D operator + (const Vector2D& A, const Vector2D& B);
        friend float operator * (const Vector2D& A, const Vector2D& B);
        friend Vector2D operator - (const Vector2D& A, const Vector2D& B);
        
        friend Vector2D operator + (const Vector2D& A, float a);
        friend Vector2D operator * (const Vector2D& A, float a);
        friend Vector2D operator - (const Vector2D& A, float a);
        friend Vector2D operator / (const Vector2D& A, float a);
        friend Vector2D operator * (float a, const Vector2D& A);
        
        friend Vector2D& operator ++ (Vector2D& A, int);
        friend Vector2D& operator -- (Vector2D& A, int);
        friend Vector2D& operator ++ (Vector2D& A);
        friend Vector2D& operator -- (Vector2D& A);
        
        friend const Vector2D& operator + (const Vector2D& A);
        friend Vector2D operator - (const Vector2D& A);
        
        Vector2D operator += (const Vector2D& A);
        Vector2D operator -= (const Vector2D& A);
        
        
        Vector2D operator += (float a);
        Vector2D operator -= (float a);
        Vector2D operator *= (float a);
        Vector2D operator /= (float a);
        
        bool operator == (const Vector2D& A);
        bool operator != (const Vector2D& A);
        bool operator >= (const Vector2D& A);
        bool operator <= (const Vector2D& A);
        bool operator > (const  Vector2D& A);
        bool operator < (const  Vector2D& A);
        
        
        
        friend std::ostream& operator<< (std::ostream &out, const Vector2D &A);
        friend std::istream& operator>> (std::istream &in, Vector2D &A);
    };
     //*/
}
