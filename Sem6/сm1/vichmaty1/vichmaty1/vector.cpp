//
//  vector.cpp
//  Sys
//  Khromov Alexey
//  Created by macbook on 01/10/2019.
//  Copyright © 2019 macbook. All rights reserved.
//

#include "vector.hpp"

#define ASSERT_MAT( expression ) \
if (expression) {\
\
} else {\
FILE *files = fopen ("LogFiles.txt", "at");\
\
fprintf(files, "==========ASSERT_VECTOR=========\n\n");\
fprintf(files, "ERROR:\nAssertion failed: %s\n   in file %s;\n   in line %i.\n", #expression, __FILE__, __LINE__);\
fprintf(files, "\n===========================\n\n");\
\
fclose(files);\
assert (expression);\
}


#include <cassert>
#include "iostream"
#include <math.h>

#include "matrix.hpp"



template <typename data_t>
class Matrix;





template <typename data_t>
class Vector {
    int size_;
    
    data_t* data_;
    
public:
    Vector ();
    Vector (int size);
    Vector (Vector& V);
    ~Vector ();
    
    data_t& operator [] (int i);
    
    double abc ();
    
    
    int getsize() {
        return size_;
    }
    
    template <typename data_t1>
    friend std::ostream& operator<< (std::ostream &out, Vector<data_t1> &V);
    template <typename data_t1>
    friend std::istream& operator>> (std::istream &in, Vector<data_t1> &V);
    
    Vector& operator = (const Vector& A);
    Vector& operator = (data_t x);
    //*
    template <typename data_t1>
    friend Vector<data_t1> operator + (Vector<data_t1>& A, Vector<data_t1>& B);
    template <typename data_t1>
    friend data_t1 operator * (Vector<data_t1>& A, Vector<data_t1>& B);
    template <typename data_t1>
    friend Vector<data_t1> operator - (Vector<data_t1>& A, Vector<data_t1>& B);
    
    template <typename data_t1>
    friend Vector<data_t1> operator * (Vector<data_t1>& A, data_t a);
    template <typename data_t1>
    friend Vector<data_t1> operator / (Vector<data_t1>& A, data_t a);
    template <typename data_t1>
    friend Vector<data_t1> operator * (float a, Vector<data_t1>& A);
    
    
    template <typename data_t1>
    friend const Vector<data_t1>& operator + (const Vector<data_t1>& A);
    template <typename data_t1>
    friend Vector<data_t1> operator - (Vector<data_t1>& A);
    
    Vector operator += (Vector& A);
    Vector operator -= (Vector& A);
    
    Vector operator *= (data_t a);
    
    bool operator == (Vector& A);
    
    template <typename data_t1>
    friend Vector <data_t1> operator * (Matrix<data_t1>& A, Vector<data_t1>& B);
    //*
    
};


template <typename data_t>
double Vector<data_t>::abc () {
    data_t sum = 0;
    for (int i = 0; i < size_; i++) {
        sum += data_ [i] * data_ [i];
    }
    return sqrt(sum);
}


template <typename data_t>
Vector<data_t>::Vector ():
size_(1)
{

    data_ = new data_t [size_] {};
    ASSERT_MAT(data_ != NULL)
}


template <typename data_t>
Vector<data_t>::Vector (int size):
size_(size)
{
    if (size_ < 1) {
        ASSERT_MAT (size_ < 1)
    }
    
    data_ = new data_t [size_] {};
    ASSERT_MAT(data_ != NULL)
    
}


template <typename data_t>
Vector<data_t>::Vector (Vector<data_t>& V):
size_(V.size_)
{
    if (size_ < 1) {
        ASSERT_MAT (size_ < 1)
    }
    
    data_ = new data_t [size_] {};
    ASSERT_MAT(data_ != NULL)
    
    for (int i = 0; i < size_; i++) {
        (*this) [i] = V [i];
    }
}


template <typename data_t>
Vector<data_t>::~Vector () {
    delete [] data_;
}


template <typename data_t>
data_t& Vector<data_t>::operator [] (int i) {
    
    ASSERT_MAT((i>=0 && i<size_))
    
    return data_[i];
}


template <typename data_t>
std::ostream& operator<< (std::ostream &out, Vector<data_t> &V)
{
    out << "(";
    for (int i = 0; i < V.size_; i++) {
        out << V [i];
        if(i < V.size_ - 1)
            out << " ";
    }
    out << ")";
    return out;
}
        
template <typename data_t>
std::istream& operator>> (std::istream &in, Vector<data_t> &V)
{
    for (int i = 0; i < V.size_; i++) {
        in >> V [i];
    }
    return in;
}


template <typename data_t>
Vector<data_t>& Vector<data_t>::operator = (const Vector<data_t> & A) {
        
    ASSERT_MAT(A.size_ == (*this).size_)
        
    for (int i = 0; i < A.size_; i++) {
        (*this) [i] = A.data_[i];
    }
    
    return *this;
}

template <typename data_t>
Vector<data_t>& Vector<data_t>::operator = (data_t x) {
        
    for (int i = 0; i < size_; i++) {
        (*this) [i] = x;
    }
    
    return *this;
}


template <typename data_t>
Vector<data_t> operator + (Vector<data_t>& A, Vector<data_t>& B)  {
    ASSERT_MAT((A.size_ == B.size_))
        
    Vector<data_t> M(A.size_);
    for (int i = 0; i < M.size_; i++) {
            M [i] = A [i] + B [i];
    }
    return M;
}

template <typename data_t>
Vector<data_t> operator - (Vector<data_t>& A, Vector<data_t>& B)  {
    
    Vector<data_t> M(A.size_);
    for (int i = 0; i < M.size_; i++) {
            M [i] = A [i] - B [i];
    }
    return M;
}


        
        
template <typename data_t>
data_t operator * (Vector<data_t>& A, Vector<data_t>& B) {
    ASSERT_MAT(A.size_==B.size_)
    data_t S = 0;
    for (int i = 0; i < A.size_; i++) {
        S += A [i] * B [i];
    }
    return S;
}

template <typename data_t>
Vector<data_t> operator * (Vector<data_t>& A, data_t a) {
    Vector<data_t> M (A.size_);
    for (int i = 0; i < M.size_; i++) {
        M [i] = A [i] * a;
    }
    return M;
}

template <typename data_t>
Vector<data_t> operator / (Vector<data_t>& A, data_t a) {
    Vector<data_t> M (A.size_);
    for (int i = 0; i < M.size_; i++) {
        M [i] = A [i] / a;
    }
    return M;
}

template <typename data_t>
Vector<data_t> operator * (data_t a, Vector<data_t>& A) {
    Vector<data_t> M (A.size_);
    for (int i = 0; i < M.size_; i++) {
        M [i] = A [i] * a;
    }
    return M;
}

template <typename data_t>
const Vector<data_t>& operator + (const Vector<data_t>& A) {
    return A;
}
template <typename data_t>
Vector<data_t> operator - (Vector<data_t>& A)  {
    Vector<data_t> M (A.size_);
    for (int i = 0; i < M.size_; i++) {
        M [i] = -(A [i]);
    }
    return M;
}

template <typename data_t>
Vector<data_t> Vector<data_t>::operator += (Vector<data_t>& A)  {
    ASSERT_MAT(A.size_==(*this).size_)
    for (int i = 0; i < A.size_; i++) {
        (*this) [i] += (A [i]);
    }
    return *this;
}


template <typename data_t>
Vector<data_t> Vector<data_t>::operator -= (Vector<data_t>& A)  {
    ASSERT_MAT(A.size_ == (*this).size_)
    for (int i = 0; i < A.size_; i++) {
        (*this) [i] -= (A [i]);
    }
    return *this;
}

template <typename data_t>
Vector<data_t> Vector<data_t>::operator *= (data_t a)  {
    for (int i = 0; i < (*this).size_; i++) {
        (*this) [i] *= a;
    }
    return *this;
}
        

template <typename data_t>
bool Vector<data_t>::operator == (Vector<data_t>& A)  {
    ASSERT_MAT(A.size_==(*this).size_)
    for (int i = 0; i < A.size_; i++) {
        if ((*this) [i] != (A [i]))
            return false;
    }
    return true;
}



#undef ASSERT_MAT
