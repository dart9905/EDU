//
//  lib.cpp
//  Vector
//
//  Created by macbook on 08/02/2019.
//  Copyright © 2019 macbook. All rights reserved.
//
#include "lib.hpp"

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
    x = X * C;
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
