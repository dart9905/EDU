//
//  lib.cpp
//  Vector
//
//  Created by macbook on 08/02/2019.
//  Copyright © 2019 macbook. All rights reserved.
//
#include "lib.hpp"

namespace MatA {
    
    Vector::Vector() {
        x = 0; y = 0; z = 0;
    }
    Vector::Vector(float A) {
        x = A; y = A; z = A;
    }
    Vector::Vector(float X, float Y, float Z) {
        x = X; y = Y; z = Z;
    }
    
    Vector::~Vector() {
        x = 0; y = 0; z = 0;
    }
    
    void Vector::set_x(float X) {
        x = X;
    }
    
    float Vector::get_x() {
        return x;
    }
    
    void Vector::set_y(float Y) {
        y = Y;
    }
    float Vector::get_y() {
        return y;
    }
    void Vector::set_z(float Z) {
        z = Z;
    }
    float Vector::get_z() {
        return z;
    }
    
    
    
    
    Vector Vector::operator + (Vector B)  {
        return Vector (x + B.get_x(), y + B.get_y(), z + B.get_z());
    }
    double Vector::operator * (Vector B) {
        return x * B.get_x() + y * B.get_y() + z * B.get_z();
    }
    Vector Vector::operator - (Vector B)  {
        return Vector (x - B.get_x(), y - B.get_y(), z - B.get_z());
    }
    Vector Vector::operator ^ (Vector B) {
        return Vector (y * B.get_z() - z * B.get_y(), -x * B.get_z() + z * B.get_x(), x * B.get_y() - y * B.get_x());
    }
    
    Vector Vector::operator + (double a) {
        return Vector (x + a, y + a, z + a);
    }
    Vector Vector::operator * (double a) {
        return Vector (x * a, y * a, z * a);
    }
    Vector Vector::operator - (double a) {
        return Vector (x - a, y - a, z - a);
    }
    Vector Vector::operator / (double a) {
        return Vector (x / a, y / a, z / a);
    }

}
