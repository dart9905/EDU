//
//  lib.cpp
//  Vector
//
//  Created by macbook on 08/02/2019.
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

#include <cassert>
#include "lib.hpp"
#include "iostream"

namespace MatA {
    
    Vector::Vector():x_(0), y_(0), z_(0)
    {}
    Vector::Vector(float A):x_(A), y_(A), z_(A)
    {}
    Vector::Vector(float X, float Y, float Z):x_(X), y_(Y), z_(Z)
    {}
    Vector::Vector(const Vector& A):x_(A.x_), y_(A.y_), z_(A.z_)
    {}
    
    Vector::~Vector() {
        x_ = 0; y_ = 0; z_ = 0;
    }
    
    void Vector::set_x(float X) {
        x_ = X;
    }
    
    float Vector::get_x() {
        return x_;
    }
    
    void Vector::set_y(float Y) {
        y_ = Y;
    }
    float Vector::get_y() {
        return y_;
    }
    void Vector::set_z(float Z) {
        z_ = Z;
    }
    float Vector::get_z() {
        return z_;
    }
    
    
    float& Vector::operator [] (int i) {
        switch (i) {
            case 0:
                return x_;
                break;
                
            case 1:
                return y_;
                break;
                
            case 2:
                return z_;
                break;

            default:
                ASSERT_MAT((i>=0)&&(i<=2))
                break;
        }
        return x_;
    }
    
    
    
    Vector& Vector::operator = (const Vector & arg) {
        this->x_ = arg.x_;
        this->y_ = arg.y_;
        this->z_ = arg.z_;
        return *this;
    }
    Vector& Vector::operator = (const float & arg) {
        this->x_ = arg;
        this->y_ = arg;
        this->z_ = arg;
        return *this;
    }
    
    
    
    
    Vector operator + (const Vector& A, const Vector& B)  {
        return Vector (A.x_ + B.x_, A.y_ + B.y_, A.z_ + B.z_);
    }
    float operator * (const Vector& A, const Vector& B) {
        return A.x_ * B.x_ + A.y_ * B.y_ + A.z_ * B.z_;
    }
    Vector operator - (const Vector& A, const Vector& B)  {
        return Vector (A.x_ - B.x_, A.y_ - B.y_, A.z_ - B.z_);
    }
    Vector operator ^ (const Vector& A, const Vector& B) {
        return Vector (A.y_ * B.z_ - A.z_ * B.y_, -A.x_ * B.z_ + A.z_ * B.x_, A.x_ * B.y_ - A.y_ * B.x_);
    }
    
    Vector operator + (const Vector& A, float a) {
        return Vector (A.x_ + a, A.y_ + a, A.z_ + a);
    }
    Vector operator * (const Vector& A, float a) {
        return Vector (A.x_ * a, A.y_ * a, A.z_ * a);
    }
    Vector operator * (float a, const Vector& A) {
        return Vector (A.x_ * a, A.y_ * a, A.z_ * a);
    }
    Vector operator - (const Vector& A, float a) {
        return Vector (A.x_ - a, A.y_ - a, A.z_ - a);
    }
    Vector operator / (const Vector& A, float a) {
        return Vector (A.x_ / a, A.y_ / a, A.z_ / a);
    }
    
    
    Vector& operator ++ ( Vector& A, int) {
        A.x_++;
        A.y_++;
        A.z_++;
        return A;
    }
    Vector& operator ++ ( Vector& A) {
        A.x_++;
        A.y_++;
        A.z_++;
        return A;
    }
    Vector& operator -- ( Vector& A, int) {
        A.x_--;
        A.y_--;
        A.z_--;
        return A;
    }
    Vector& operator -- ( Vector& A) {
        A.x_--;
        A.y_--;
        A.z_--;
        return A;
    }
    
    
    Vector operator - ( const Vector& A) {
        return Vector(-A.x_, -A.y_, -A.z_);
    }
    
    const Vector& operator + ( const Vector& A) {
        return A;
    }
    
    
    
    
    Vector Vector::operator += (const Vector& A) {
        x_+=A.x_;
        y_+=A.y_;
        z_+=A.z_;
        return *this;
    }
    Vector Vector::operator -= (const Vector& A) {
        x_-=A.x_;
        y_-=A.y_;
        z_-=A.z_;
        return *this;
    }
    
    
    Vector Vector::operator += (float a) {
        x_+=a;
        y_+=a;
        z_+=a;
        return *this;
    }
    Vector Vector::operator -= (float a) {
        x_-=a;
        y_-=a;
        z_-=a;
        return *this;
    }
    Vector Vector::operator *= (float a) {
        x_*=a;
        y_*=a;
        z_*=a;
        return *this;
    }
    Vector Vector::operator /= (float a) {
        x_/=a;
        y_/=a;
        z_/=a;
        return *this;
    }
    
    bool Vector::operator == (const Vector& A) {
        if (ABS(A) == ABS(*this))
            return true;
        return false;
    }
    bool Vector::operator != (const Vector& A) {
        if (ABS(A) != ABS(*this))
            return true;
        return false;
    }
    bool Vector::operator >= (const Vector& A) {
        if (ABS(*this) >= ABS(A))
            return true;
        return false;
    }
    bool Vector::operator <= (const Vector& A) {
        if (ABS(*this) <= ABS(A))
            return true;
        return false;
    }
    bool Vector::operator > (const Vector& A) {
        if (ABS(*this) > ABS(A))
            return true;
        return false;
    }
    bool Vector::operator < (const Vector& A) {
        if (ABS(*this) < ABS(A))
            return true;
        return false;
    }
    
    
    std::ostream& operator<< (std::ostream &out, const Vector &A)
    {
        out << "Vector(" << A.x_ << ", " << A.y_ << ", " << A.z_ << ")";
        
        return out;
    }
    
    std::istream& operator>> (std::istream &in, Vector &A)
    {
        in >> A.x_;
        in >> A.y_;
        in >> A.z_;
        
        return in;
    }

    
    Vector2D::Vector2D():x_(0), y_(0)
    {}
    Vector2D::Vector2D(float A):x_(A), y_(A)
    {}
    Vector2D::Vector2D(float X, float Y):x_(X), y_(Y)
    {}
    Vector2D::Vector2D(const Vector2D& A):x_(A.x_), y_(A.y_)
    {}
    
    Vector2D::~Vector2D() {
        x_ = 0; y_ = 0;
    }
    
    void Vector2D::set_x(float X) {
        x_ = X;
    }
    
    float Vector2D::get_x() {
        return x_;
    }
    
    void Vector2D::set_y(float Y) {
        y_ = Y;
    }
    float Vector2D::get_y() {
        return y_;
    }
    
    
    float& Vector2D::operator [] (int i) {
        switch (i) {
            case 0:
                return x_;
                break;
                
            case 1:
                return y_;
                break;
                
            default:
                ASSERT_MAT((i>=0)&&(i<=2))
                break;
        }
        return x_;
    }
    
    
    
    Vector2D& Vector2D::operator = (const Vector2D & arg) {
        this->x_ = arg.x_;
        this->y_ = arg.y_;
        return *this;
    }
    Vector2D& Vector2D::operator = (const float & arg) {
        this->x_ = arg;
        this->y_ = arg;
        return *this;
    }
    
    
    
    
    Vector2D operator + (const Vector2D& A, const Vector2D& B)  {
        return Vector2D (A.x_ + B.x_, A.y_ + B.y_);
    }
    float operator * (const Vector2D& A, const Vector2D& B) {
        return A.x_ * B.x_ + A.y_ * B.y_;
    }
    Vector2D operator - (const Vector2D& A, const Vector2D& B)  {
        return Vector2D (A.x_ - B.x_, A.y_ - B.y_);
    }
    
    Vector2D operator + (const Vector2D& A, float a) {
        return Vector2D (A.x_ + a, A.y_ + a);
    }
    Vector2D operator * (const Vector2D& A, float a) {
        return Vector2D (A.x_ * a, A.y_ * a);
    }
    Vector2D operator * (float a, const Vector2D& A) {
        return Vector2D (A.x_ * a, A.y_ * a);
    }
    Vector2D operator - (const Vector2D& A, float a) {
        return Vector2D (A.x_ - a, A.y_ - a);
    }
    Vector2D operator / (const Vector2D& A, float a) {
        return Vector2D (A.x_ / a, A.y_ / a);
    }
    
    
    Vector2D& operator ++ ( Vector2D& A, int) {
        A.x_++;
        A.y_++;
        return A;
    }
    Vector2D& operator ++ ( Vector2D& A) {
        A.x_++;
        A.y_++;
        return A;
    }
    Vector2D& operator -- ( Vector2D& A, int) {
        A.x_--;
        A.y_--;
        return A;
    }
    Vector2D& operator -- ( Vector2D& A) {
        A.x_--;
        A.y_--;
        return A;
    }
    
    
    Vector2D operator - ( const Vector2D& A) {
        return Vector2D(-A.x_, -A.y_);
    }
    
    const Vector2D& operator + ( const Vector2D& A) {
        return A;
    }
    
    
    
    
    Vector2D Vector2D::operator += (const Vector2D& A) {
        x_+=A.x_;
        y_+=A.y_;
        return *this;
    }
    Vector2D Vector2D::operator -= (const Vector2D& A) {
        x_-=A.x_;
        y_-=A.y_;
        return *this;
    }
    
    
    Vector2D Vector2D::operator += (float a) {
        x_+=a;
        y_+=a;
        return *this;
    }
    Vector2D Vector2D::operator -= (float a) {
        x_-=a;
        y_-=a;
        return *this;
    }
    Vector2D Vector2D::operator *= (float a) {
        x_*=a;
        y_*=a;
        return *this;
    }
    Vector2D Vector2D::operator /= (float a) {
        x_/=a;
        y_/=a;
        return *this;
    }
    
    bool Vector2D::operator == (const Vector2D& A) {
        if (ABS(A) == ABS(*this))
            return true;
        return false;
    }
    bool Vector2D::operator != (const Vector2D& A) {
        if (ABS(A) != ABS(*this))
            return true;
        return false;
    }
    bool Vector2D::operator >= (const Vector2D& A) {
        if (ABS(*this) >= ABS(A))
            return true;
        return false;
    }
    bool Vector2D::operator <= (const Vector2D& A) {
        if (ABS(*this) <= ABS(A))
            return true;
        return false;
    }
    bool Vector2D::operator > (const Vector2D& A) {
        if (ABS(*this) > ABS(A))
            return true;
        return false;
    }
    bool Vector2D::operator < (const Vector2D& A) {
        if (ABS(*this) < ABS(A))
            return true;
        return false;
    }
    
    
    std::ostream& operator<< (std::ostream &out, const Vector2D &A)
    {
        out << "Vector(" << A.x_ << ", " << A.y_ << ")";
        
        return out;
    }
    
    std::istream& operator>> (std::istream &in, Vector2D &A)
    {
        in >> A.x_;
        in >> A.y_;
        
        return in;
    }

    
}
#undef ASSERT_MAT
