//
//  lib.cpp
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

#define ASSERT_MAT_S( expression ) \
{\
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
    
    Vector3D::Vector3D():x_(0), y_(0), z_(0)
    {}
    Vector3D::Vector3D(float A):x_(A), y_(A), z_(A)
    {}
    Vector3D::Vector3D(float X, float Y, float Z):x_(X), y_(Y), z_(Z)
    {}
    Vector3D::Vector3D(const Vector3D& A):x_(A.x_), y_(A.y_), z_(A.z_)
    {}
    
    Vector3D::~Vector3D() {
        x_ = 0; y_ = 0; z_ = 0;
    }
    
    void Vector3D::set_x(float X) {
        x_ = X;
    }
    
    float Vector3D::get_x() {
        return x_;
    }
    
    void Vector3D::set_y(float Y) {
        y_ = Y;
    }
    float Vector3D::get_y() {
        return y_;
    }
    void Vector3D::set_z(float Z) {
        z_ = Z;
    }
    float Vector3D::get_z() {
        return z_;
    }
    
    
    float& Vector3D::operator [] (int i) {
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
    
    
    
    Vector3D& Vector3D::operator = (const Vector3D & arg) {
        this->x_ = arg.x_;
        this->y_ = arg.y_;
        this->z_ = arg.z_;
        return *this;
    }
    Vector3D& Vector3D::operator = (const float & arg) {
        this->x_ = arg;
        this->y_ = arg;
        this->z_ = arg;
        return *this;
    }
    
    
    
    
    Vector3D operator + (const Vector3D& A, const Vector3D& B)  {
        return Vector3D (A.x_ + B.x_, A.y_ + B.y_, A.z_ + B.z_);
    }
    float operator * (const Vector3D& A, const Vector3D& B) {
        return A.x_ * B.x_ + A.y_ * B.y_ + A.z_ * B.z_;
    }
    Vector3D operator - (const Vector3D& A, const Vector3D& B)  {
        return Vector3D (A.x_ - B.x_, A.y_ - B.y_, A.z_ - B.z_);
    }
    Vector3D operator ^ (const Vector3D& A, const Vector3D& B) {
        return Vector3D (A.y_ * B.z_ - A.z_ * B.y_, -A.x_ * B.z_ + A.z_ * B.x_, A.x_ * B.y_ - A.y_ * B.x_);
    }
    
    Vector3D operator + (const Vector3D& A, float a) {
        return Vector3D (A.x_ + a, A.y_ + a, A.z_ + a);
    }
    Vector3D operator * (const Vector3D& A, float a) {
        return Vector3D (A.x_ * a, A.y_ * a, A.z_ * a);
    }
    Vector3D operator * (float a, const Vector3D& A) {
        return Vector3D (A.x_ * a, A.y_ * a, A.z_ * a);
    }
    Vector3D operator - (const Vector3D& A, float a) {
        return Vector3D (A.x_ - a, A.y_ - a, A.z_ - a);
    }
    Vector3D operator / (const Vector3D& A, float a) {
        return Vector3D (A.x_ / a, A.y_ / a, A.z_ / a);
    }
    
    
    Vector3D& operator ++ ( Vector3D& A, int) {
        A.x_++;
        A.y_++;
        A.z_++;
        return A;
    }
    Vector3D& operator ++ ( Vector3D& A) {
        A.x_++;
        A.y_++;
        A.z_++;
        return A;
    }
    Vector3D& operator -- ( Vector3D& A, int) {
        A.x_--;
        A.y_--;
        A.z_--;
        return A;
    }
    Vector3D& operator -- ( Vector3D& A) {
        A.x_--;
        A.y_--;
        A.z_--;
        return A;
    }
    
    
    Vector3D operator - ( const Vector3D& A) {
        return Vector3D(-A.x_, -A.y_, -A.z_);
    }
    
    const Vector3D& operator + ( const Vector3D& A) {
        return A;
    }
    
    
    
    
    Vector3D Vector3D::operator += (const Vector3D& A) {
        x_+=A.x_;
        y_+=A.y_;
        z_+=A.z_;
        return *this;
    }
    Vector3D Vector3D::operator -= (const Vector3D& A) {
        x_-=A.x_;
        y_-=A.y_;
        z_-=A.z_;
        return *this;
    }
    
    
    Vector3D Vector3D::operator += (float a) {
        x_+=a;
        y_+=a;
        z_+=a;
        return *this;
    }
    Vector3D Vector3D::operator -= (float a) {
        x_-=a;
        y_-=a;
        z_-=a;
        return *this;
    }
    Vector3D Vector3D::operator *= (float a) {
        x_*=a;
        y_*=a;
        z_*=a;
        return *this;
    }
    Vector3D Vector3D::operator /= (float a) {
        x_/=a;
        y_/=a;
        z_/=a;
        return *this;
    }
    
    bool Vector3D::operator == (const Vector3D& A) {
        if (ABS(A) == ABS(*this))
            return true;
        return false;
    }
    bool Vector3D::operator != (const Vector3D& A) {
        if (ABS(A) != ABS(*this))
            return true;
        return false;
    }
    bool Vector3D::operator >= (const Vector3D& A) {
        if (ABS(*this) >= ABS(A))
            return true;
        return false;
    }
    bool Vector3D::operator <= (const Vector3D& A) {
        if (ABS(*this) <= ABS(A))
            return true;
        return false;
    }
    bool Vector3D::operator > (const Vector3D& A) {
        if (ABS(*this) > ABS(A))
            return true;
        return false;
    }
    bool Vector3D::operator < (const Vector3D& A) {
        if (ABS(*this) < ABS(A))
            return true;
        return false;
    }
    
    
    std::ostream& operator<< (std::ostream &out, const Vector3D &A)
    {
        out << "Vector3D(" << A.x_ << ", " << A.y_ << ", " << A.z_ << ")";
        
        return out;
    }
    
    std::istream& operator>> (std::istream &in, Vector3D &A)
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
        out << "Vector3D(" << A.x_ << ", " << A.y_ << ")";
        
        return out;
    }
    
    std::istream& operator>> (std::istream &in, Vector2D &A)
    {
        in >> A.x_;
        in >> A.y_;
        
        return in;
    }
    void VectorV::set_x(float X) {
        ASSERT_MAT_S("virtual class")
    }
    
    float VectorV::get_x() {
        ASSERT_MAT_S("virtual class")
        return 0;
    }
    
    void VectorV::set_y(float Y) {
        ASSERT_MAT_S("virtual class")
    }
    float VectorV::get_y() {
        ASSERT_MAT_S("virtual class")
        return 0;
    }
    
    float& VectorV::operator [] (int i) {
        ASSERT_MAT_S("virtual class")
        float a = 0;
        return a;
    }
    bool VectorV::operator == (const VectorV& A) {
        ASSERT_MAT_S("virtual class")
        return false;
    }
    bool VectorV::operator != (const VectorV& A) {
        ASSERT_MAT_S("virtual class")
        return false;
    }
    bool VectorV::operator >= (const VectorV& A) {
        ASSERT_MAT_S("virtual class")
        return false;
    }
    bool VectorV::operator <= (const VectorV& A) {
        ASSERT_MAT_S("virtual class")
        return false;
    }
    bool VectorV::operator > (const VectorV& A) {
        ASSERT_MAT_S("virtual class")
        return false;
    }
    bool VectorV::operator < (const VectorV& A) {
        ASSERT_MAT_S("virtual class")
        return false;
    }
}
#undef ASSERT_MAT_S
#undef ASSERT_MAT
