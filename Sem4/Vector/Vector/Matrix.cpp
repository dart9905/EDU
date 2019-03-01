//
//  Matrix.cpp
//  Vector
//
//  Created by macbook on 22/02/2019.
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
#include "Matrix.hpp"
#include "iostream"

namespace MatA {
    
    Matrix::Matrix (int n):
    size_(n)
    {
        if (n < 1) {
            ASSERT_MAT (n < 1)
        }
        
        data_ = new subMatrix [size_];
        for (int i = 0; i < size_; i++) {
            data_[i].subMatrix2(size_);
        }
        
    }
    
    
    Matrix::Matrix (Matrix& M):
    size_(M.size_)
    {
        data_ = new subMatrix [size_];
        for (int i = 0; i < size_; i++) {
            data_[i].subMatrix2(size_);
        }
        for (int i = 0; i < size_; i++) {
            for (int j = 0; j < size_; j++) {
                (*this) [i] [j] = M[i][j];
            }
        }
        
        
    }
    
    
    Matrix::~Matrix () {
        delete [] data_;
    }
    
    
    
    subMatrix& Matrix::operator [] (int i) {
        
        ASSERT_MAT((i>=0 && i<size_))
        
        return *(data_ + i);
    }
    float& subMatrix::operator [] (int i) {
        ASSERT_MAT((i>=0 && i<size_))
        return *(data_ + i * size_);
    }
    
    std::ostream& operator<< (std::ostream &out, Matrix &M)
    {
        for (int i = 0; i < M.size_; i++) {
            out << "| ";
            for (int j = 0; j < M.size_; j++) {
                out << M [i] [j];
                out << " ";
            }
            out << "|\n";
        }
        
        
        return out;
    }
    
    std::istream& operator>> (std::istream &in, Matrix &M)
    {
        
        for (int i = 0; i < M.size_; i++) {
            for (int j = 0; j < M.size_; j++) {
                in >> M [i] [j];
            }
        }
        
        return in;
    }
    
    
    
    Matrix& Matrix::operator = (Matrix & A) {
        ASSERT_MAT(A.size_==(*this).size_)
        for (int i = 0; i < A.size_; i++) {
            for (int j = 0; j < A.size_; j++) {
                (*this) [i] [j] = A [i] [j];
            }
        }
        return *this;
    }
    Matrix& Matrix::operator = (const float & A) {
        for (int i = 0; i < (*this).size_; i++) {
            for (int j = 0; j < (*this).size_; j++) {
                (*this) [i] [j] = A;
            }
        }
        return *this;
    }
    
    
    Matrix operator + (Matrix& A, Matrix& B)  {
        ASSERT_MAT(A.size_==B.size_)
        Matrix M(A.size_);
        for (int i = 0; i < M.size_; i++) {
            for (int j = 0; j < M.size_; j++) {
                M [i] [j] = A [i] [j] + B [i] [j];
            }
        }
        return M;
    }
    Matrix operator - (Matrix& A, Matrix& B)  {
        ASSERT_MAT(A.size_==B.size_)
        Matrix M(A.size_);
        for (int i = 0; i < M.size_; i++) {
            for (int j = 0; j < M.size_; j++) {
                M [i] [j] = A [i] [j] - B [i] [j];
            }
        }
        return M;
    }
    
    Matrix operator * (Matrix& A, Matrix& B) {
        ASSERT_MAT(A.size_==B.size_)
        Matrix M(A.size_);
        for (int i = 0; i < M.size_; i++) {
            for (int j = 0; j < M.size_; j++) {
                for (int k = 0; k < M.size_; k++) {
                    M [i] [j] += A [i] [k] * B [k] [j];
                }
            }
        }
        return M;
    }
    
    
    
    Matrix operator + (Matrix& A, float a) {
        Matrix M(A.size_);
        for (int i = 0; i < M.size_; i++) {
            for (int j = 0; j < M.size_; j++) {
                M [i] [j] = A [i] [j] + a;
            }
        }
        return M;
    }
    
    Matrix operator * (Matrix& A, float a) {
        Matrix M(A.size_);
        for (int i = 0; i < M.size_; i++) {
            for (int j = 0; j < M.size_; j++) {
                M [i] [j] = A [i] [j] * a;
            }
        }
        return M;
    }
    Matrix operator - (Matrix& A, float a) {
        Matrix M(A.size_);
        for (int i = 0; i < M.size_; i++) {
            for (int j = 0; j < M.size_; j++) {
                M [i] [j] = A [i] [j] - a;
            }
        }
        return M;
    }
    Matrix operator / (Matrix& A, float a) {
        Matrix M(A.size_);
        for (int i = 0; i < M.size_; i++) {
            for (int j = 0; j < M.size_; j++) {
                M [i] [j] = A [i] [j] / a;
            }
        }
        return M;
    }
    
    Matrix operator * (float a, Matrix& A) {
        Matrix M(A.size_);
        for (int i = 0; i < M.size_; i++) {
            for (int j = 0; j < M.size_; j++) {
                M [i] [j] = A [i] [j] * a;
            }
        }
        return M;
    }
    
    Matrix& operator ++ (Matrix& A, int)  {
        for (int i = 0; i < A.size_; i++) {
            for (int j = 0; j < A.size_; j++) {
                A [i] [j]++;
            }
        }
        return A;
    }
    Matrix& operator -- (Matrix& A, int)  {
        for (int i = 0; i < A.size_; i++) {
            for (int j = 0; j < A.size_; j++) {
                A [i] [j]--;
            }
        }
        return A;
    }
    Matrix& operator ++ (Matrix& A)  {
        for (int i = 0; i < A.size_; i++) {
            for (int j = 0; j < A.size_; j++) {
                A [i] [j]++;
            }
        }
        return A;
    }
    Matrix& operator -- (Matrix& A)  {
        for (int i = 0; i < A.size_; i++) {
            for (int j = 0; j < A.size_; j++) {
                A [i] [j]--;
            }
        }
        return A;
    }
    
    const Matrix& operator + (const Matrix& A) {
        return A;
    }
    Matrix operator - (Matrix& A)  {
        Matrix M(A.size_);
        for (int i = 0; i < M.size_; i++) {
            for (int j = 0; j < M.size_; j++) {
                M [i] [j] = -(A [i] [j]);
            }
        }
        return M;
    }
    
    Matrix Matrix::operator += (Matrix& A)  {
        ASSERT_MAT(A.size_==(*this).size_)
        for (int i = 0; i < A.size_; i++) {
            for (int j = 0; j < A.size_; j++) {
                (*this) [i] [j] += (A [i] [j]);
            }
        }
        return *this;
    }
    
    
    Matrix Matrix::operator -= (Matrix& A)  {
        ASSERT_MAT(A.size_==(*this).size_)
        for (int i = 0; i < A.size_; i++) {
            for (int j = 0; j < A.size_; j++) {
                (*this) [i] [j] -= (A [i] [j]);
            }
        }
        return *this;
    }
    
    Matrix Matrix::operator -= (float a)  {
        for (int i = 0; i < (*this).size_; i++) {
            for (int j = 0; j < (*this).size_; j++) {
                (*this) [i] [j] -= a;
            }
        }
        return *this;
    }
    Matrix Matrix::operator += (float a)  {
        for (int i = 0; i < (*this).size_; i++) {
            for (int j = 0; j < (*this).size_; j++) {
                (*this) [i] [j] += a;
            }
        }
        return *this;
    }
    Matrix Matrix::operator *= (float a)  {
        for (int i = 0; i < (*this).size_; i++) {
            for (int j = 0; j < (*this).size_; j++) {
                (*this) [i] [j] *= a;
            }
        }
        return *this;
    }
    Matrix Matrix::operator /= (float a)  {
        for (int i = 0; i < (*this).size_; i++) {
            for (int j = 0; j < (*this).size_; j++) {
                (*this) [i] [j] -= a;
            }
        }
        return *this;
    }
    
    
    bool Matrix::operator == (Matrix& A)  {
        ASSERT_MAT(A.size_==(*this).size_)
        for (int i = 0; i < A.size_; i++) {
            for (int j = 0; j < A.size_; j++) {
                if ((*this) [i] [j] != (A [i] [j]))
                    return false;
            }
        }
        return true;
    }
}
#undef ASSERT_MAT
