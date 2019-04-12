//
//  lib.hpp
//
//  Created by macbook on 08/02/2019.
//  Copyright © 2019 macbook. All rights reserved.
//


#include <cassert>
#include "iostream"
namespace MatA {
    
    
    class VectorV
    {
    public:
        virtual ~VectorV() {};
        
        virtual void set_x(float X);
        virtual float get_x();
        
        
        virtual void set_y(float Y);
        virtual float get_y();
        
        
        
        virtual float& operator [] (int i);
        
        virtual bool operator == (const VectorV& A);
        virtual bool operator != (const VectorV& A);
        virtual bool operator >= (const VectorV& A);
        virtual bool operator <= (const VectorV& A);
        virtual bool operator > (const VectorV& A);
        virtual bool operator < (const VectorV& A);
        
    };
    
    class Vector3D: virtual public VectorV
    {
        friend float ABS(const Vector3D& A);
        float x_, y_, z_;
        
    public:
        
        Vector3D();
        Vector3D(float A);
        Vector3D(float X, float Y, float Z);
        Vector3D(const Vector3D& A);
        
        ~Vector3D();
        
        void set_x(float X);
        float get_x();
        
        
        void set_y(float Y);
        float get_y();
        
        
        void set_z(float Z);
        float get_z();
        
        
        float& operator [] (int i);
        Vector3D&   operator = (const Vector3D & arg);
        Vector3D&   operator = (const float & arg);
        
        friend Vector3D operator + (const Vector3D& A, const Vector3D& B);
        friend float    operator * (const Vector3D& A, const Vector3D& B);
        friend Vector3D operator - (const Vector3D& A, const Vector3D& B);
        friend Vector3D operator ^ (const Vector3D& A, const Vector3D& B);
        
        friend Vector3D operator + (const Vector3D& A, float a);
        friend Vector3D operator * (const Vector3D& A, float a);
        friend Vector3D operator - (const Vector3D& A, float a);
        friend Vector3D operator / (const Vector3D& A, float a);
        friend Vector3D operator * (float a, const Vector3D& A);
        
        friend Vector3D& operator ++ (Vector3D& A, int);
        friend Vector3D& operator -- (Vector3D& A, int);
        friend Vector3D& operator ++ (Vector3D& A);
        friend Vector3D& operator -- (Vector3D& A);
        
        friend const Vector3D& operator + (const Vector3D& A);
        friend Vector3D operator - (const Vector3D& A);
        
        Vector3D operator += (const Vector3D& A);
        Vector3D operator -= (const Vector3D& A);
        
        
        Vector3D operator += (float a);
        Vector3D operator -= (float a);
        Vector3D operator *= (float a);
        Vector3D operator /= (float a);
        
        bool operator == (const Vector3D& A);
        bool operator != (const Vector3D& A);
        bool operator >= (const Vector3D& A);
        bool operator <= (const Vector3D& A);
        bool operator >  (const Vector3D& A);
        bool operator <  (const Vector3D& A);
        
        
        
        friend std::ostream& operator<< (std::ostream &out, const Vector3D &A);
        friend std::istream& operator>> (std::istream &in, Vector3D &A);
    };

    
    class Vector2D: virtual public VectorV
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
        bool operator > (const Vector2D& A);
        bool operator < (const Vector2D& A);
        
        
        
        friend std::ostream& operator<< (std::ostream &out, const Vector2D &A);
        friend std::istream& operator>> (std::istream &in, Vector2D &A);
    };
    
}
