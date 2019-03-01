//
//  Matrix.hpp
//  Vector
//
//  Created by macbook on 22/02/2019.
//  Copyright © 2019 macbook. All rights reserved.
//

#ifndef Matrix_hpp
#define Matrix_hpp

#include <stdio.h>
#include "iostream"


namespace MatA {
    class subMatrix {
        int size_;
        float* data_;
    public:
        
        void subMatrix2 (int i)
        {
            size_ = i;
            data_ = new float [size_] {NULL};
        }
        ~subMatrix()
        {
            delete [] data_;
        }
        
        float get (int y) const;
        float& set (int y);
        
        float& operator [] (int i);
        
    };
    
    
    
    
    class Matrix {
        int size_;
        subMatrix* data_;
        
    public:
        Matrix (int n);
        Matrix (Matrix& M);
        ~Matrix ();
        
        float get(int x, int y) const;
        float& set(int x, int y);
        
        subMatrix& operator [] (int i);
        friend std::ostream& operator<< (std::ostream &out, Matrix &M);
        friend std::istream& operator>> (std::istream &in, Matrix &M);
        
        Matrix& operator = (const Matrix& A);
        Matrix& operator = (const float & A);
        //*
        friend Matrix operator + (Matrix& A, Matrix& B);
        friend Matrix operator * (Matrix& A, Matrix& B);
        friend Matrix operator - (Matrix& A, Matrix& B);
        
        friend Matrix operator + (Matrix& A, float a);
        friend Matrix operator * (Matrix& A, float a);
        friend Matrix operator - (Matrix& A, float a);
        friend Matrix operator / (Matrix& A, float a);
        friend Matrix operator * (float a, Matrix& A);
        
        friend Matrix& operator ++ (Matrix& A, int);
        friend Matrix& operator -- (Matrix& A, int);
        friend Matrix& operator ++ (Matrix& A);
        friend Matrix& operator -- (Matrix& A);
        
        friend const Matrix& operator + (const Matrix& A);
        friend Matrix operator - (Matrix& A);
        
        Matrix operator += (Matrix& A);
        Matrix operator -= (Matrix& A);
        
        
        Matrix operator += (float a);
        Matrix operator -= (float a);
        Matrix operator *= (float a);
        Matrix operator /= (float a);
        
        bool operator == (Matrix& A);
        //*/
        
    };
}


#endif /* Matrix_hpp */


