//
//  Matrix.cpp
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
    
    
    template <typename data_t, int size>
    class subMatrix {
        int size_;
        data_t* data_;
    public:
        
        void subMatrix2 (int i)
        {
            size_ = i;
            data_ = new data_t [size_] {NULL};
        }
        ~subMatrix()
        {
            delete [] data_;
        }
        
        data_t get (int y) const;
        data_t& set (int y);
        
        data_t& operator [] (int i);
        
    };
    
    
    
    
    template <typename data_t, int size>
    class Matrix {
        int size_;
        subMatrix<data_t, size>* data_;
        
    public:
        Matrix ();
        Matrix (Matrix& M);
        ~Matrix ();
        
        data_t get(int x, int y) const;
        data_t& set(int x, int y);
        
        subMatrix<data_t, size>& operator [] (int i);
        
        template <typename data_t1, int size1>
        friend std::ostream& operator<< (std::ostream &out, Matrix<data_t1, size1> &M);
        template <typename data_t1, int size1>
        friend std::istream& operator>> (std::istream &in, Matrix<data_t1, size1> &M);
        
        Matrix& operator = (const Matrix& A);
        Matrix& operator = (const data_t & A);
        //*
        template <typename data_t1, int size1>
        friend Matrix<data_t1, size1> operator + (Matrix<data_t1, size1>& A, Matrix<data_t1, size1>& B);
        template <typename data_t1, int size1>
        friend Matrix<data_t1, size1> operator * (Matrix<data_t1, size1>& A, Matrix<data_t1, size1>& B);
        template <typename data_t1, int size1>
        friend Matrix<data_t1, size1> operator - (Matrix<data_t1, size1>& A, Matrix<data_t1, size1>& B);
        
        template <typename data_t1, int size1>
        friend Matrix<data_t1, size1> operator + (Matrix<data_t1, size1>& A, data_t a);
        template <typename data_t1, int size1>
        friend Matrix<data_t1, size1> operator * (Matrix<data_t1, size1>& A, data_t a);
        template <typename data_t1, int size1>
        friend Matrix<data_t1, size1> operator - (Matrix<data_t1, size1>& A, data_t a);
        template <typename data_t1, int size1>
        friend Matrix<data_t1, size1> operator / (Matrix<data_t1, size1>& A, data_t a);
        template <typename data_t1, int size1>
        friend Matrix<data_t1, size1> operator * (float a, Matrix<data_t1, size1>& A);
        
        template <typename data_t1, int size1>
        friend Matrix<data_t1, size1>& operator ++ (Matrix<data_t1, size1>& A, int);
        template <typename data_t1, int size1>
        friend Matrix<data_t1, size1>& operator -- (Matrix<data_t1, size1>& A, int);
        template <typename data_t1, int size1>
        friend Matrix<data_t1, size1>& operator ++ (Matrix<data_t1, size1>& A);
        template <typename data_t1, int size1>
        friend Matrix<data_t1, size1>& operator -- (Matrix<data_t1, size1>& A);
        
        template <typename data_t1, int size1>
        friend const Matrix<data_t1, size1>& operator + (const Matrix<data_t1, size1>& A);
        template <typename data_t1, int size1>
        friend Matrix<data_t1, size1> operator - (Matrix<data_t1, size1>& A);
        
        Matrix operator += (Matrix& A);
        Matrix operator -= (Matrix& A);
        
        
        Matrix operator += (data_t a);
        Matrix operator -= (data_t a);
        Matrix operator *= (data_t a);
        Matrix operator /= (data_t a);
        
        bool operator == (Matrix& A);
        //*
        
    };
    
    template <typename data_t, int size>
    Matrix<data_t, size>::Matrix ()
    {
        size_ = size;
        if (size < 1) {
            ASSERT_MAT (size < 1)
        }
        
        data_ = new subMatrix<data_t, size> [size_];
        for (int i = 0; i < size_; i++) {
            data_[i].subMatrix2(size_);
        }
        
    }
    
    
    template <typename data_t, int size>
    Matrix<data_t, size>::Matrix (Matrix<data_t, size>& M):
    size_(M.size_)
    {
        data_ = new subMatrix<data_t, size> [size_];
        for (int i = 0; i < size_; i++) {
            data_[i].subMatrix2(size_);
        }
        for (int i = 0; i < size_; i++) {
            for (int j = 0; j < size_; j++) {
                (*this) [i] [j] = M[i][j];
            }
        }
        
        
    }
    
    
    template <typename data_t, int size>
    Matrix<data_t, size>::~Matrix () {
        delete [] data_;
    }
    
    
    template <typename data_t, int size>
    data_t Matrix<data_t, size>::get(int x, int y) const {
        
        return data_[x].get(y);
    }
    
    template <typename data_t, int size>
    data_t subMatrix<data_t, size>::get (int y) const {
        return data_[y];
    }
    
    
    template <typename data_t, int size>
    data_t& Matrix<data_t, size>::set(int x, int y) {
        
        return data_[x].set(y);
    }
    
    template <typename data_t, int size>
    data_t& subMatrix<data_t, size>::set (int y) {
        return data_[y];
    }
    
    
    
    template <typename data_t, int size>
    subMatrix<data_t, size>& Matrix<data_t, size>::operator [] (int i) {
        
        ASSERT_MAT((i>=0 && i<size_))
        
        return *(data_ + i);
    }
    
    template <typename data_t, int size>
    data_t& subMatrix<data_t, size>::operator [] (int i) {
        ASSERT_MAT((i>=0 && i<size_))
        return *(data_ + i * size_);
    }
    
    template <typename data_t, int size>
    std::ostream& operator<< (std::ostream &out, Matrix<data_t, size> &M)
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
    
    template <typename data_t, int size>
    std::istream& operator>> (std::istream &in, Matrix<data_t, size> &M)
    {
        
        for (int i = 0; i < M.size_; i++) {
            for (int j = 0; j < M.size_; j++) {
                in >> M [i] [j];
            }
        }
        
        return in;
    }
    
    
    template <typename data_t, int size>
    Matrix<data_t, size>& Matrix<data_t, size>::operator = (const Matrix<data_t, size> & A) {
        ASSERT_MAT(A.size_==(*this).size_)
        for (int i = 0; i < A.size_; i++) {
            for (int j = 0; j < A.size_; j++) {
                (*this) [i] [j] = A.data_[i].operator[](j);
            }
        }
        
        return *this;
    }
    
    template <typename data_t, int size>
    Matrix<data_t, size>& Matrix<data_t, size>::operator = (const data_t & A) {
        for (int i = 0; i < (*this).size_; i++) {
            for (int j = 0; j < (*this).size_; j++) {
                (*this) [i] [j] = A;
            }
        }
        return *this;
    }
    
    
    template <typename data_t, int size>
    Matrix<data_t, size> operator + (Matrix<data_t, size>& A, Matrix<data_t, size>& B)  {
        ASSERT_MAT(A.size_==B.size_)
        Matrix<data_t, size> M(A.size_);
        for (int i = 0; i < M.size_; i++) {
            for (int j = 0; j < M.size_; j++) {
                M [i] [j] = A [i] [j] + B [i] [j];
            }
        }
        return M;
    }
    
    template <typename data_t, int size>
    Matrix<data_t, size> operator - (Matrix<data_t, size>& A, Matrix<data_t, size>& B)  {
        ASSERT_MAT(A.size_==B.size_)
        Matrix<data_t, size> M(A.size_);
        for (int i = 0; i < M.size_; i++) {
            for (int j = 0; j < M.size_; j++) {
                M [i] [j] = A [i] [j] - B [i] [j];
            }
        }
        return M;
    }
    
    template <typename data_t, int size>
    Matrix<data_t, size> operator * (Matrix<data_t, size>& A, Matrix<data_t, size>& B) {
        ASSERT_MAT(A.size_==B.size_)
        Matrix<data_t, size> M(A.size_);
        for (int i = 0; i < M.size_; i++) {
            for (int j = 0; j < M.size_; j++) {
                for (int k = 0; k < M.size_; k++) {
                    M [i] [j] += A [i] [k] * B [k] [j];
                }
            }
        }
        return M;
    }
    
    
    
    template <typename data_t, int size>
    Matrix<data_t, size> operator + (Matrix<data_t, size>& A, data_t a) {
        Matrix<data_t, size> M(A.size_);
        for (int i = 0; i < M.size_; i++) {
            for (int j = 0; j < M.size_; j++) {
                M [i] [j] = A [i] [j] + a;
            }
        }
        return M;
    }
    
    template <typename data_t, int size>
    Matrix<data_t, size> operator * (Matrix<data_t, size>& A, data_t a) {
        Matrix<data_t, size> M(A.size_);
        for (int i = 0; i < M.size_; i++) {
            for (int j = 0; j < M.size_; j++) {
                M [i] [j] = A [i] [j] * a;
            }
        }
        return M;
    }
    
    template <typename data_t, int size>
    Matrix<data_t, size> operator - (Matrix<data_t, size>& A, data_t a) {
        Matrix<data_t, size> M(A.size_);
        for (int i = 0; i < M.size_; i++) {
            for (int j = 0; j < M.size_; j++) {
                M [i] [j] = A [i] [j] - a;
            }
        }
        return M;
    }
    
    template <typename data_t, int size>
    Matrix<data_t, size> operator / (Matrix<data_t, size>& A, data_t a) {
        Matrix<data_t, size> M(A.size_);
        for (int i = 0; i < M.size_; i++) {
            for (int j = 0; j < M.size_; j++) {
                M [i] [j] = A [i] [j] / a;
            }
        }
        return M;
    }
    
    template <typename data_t, int size>
    Matrix<data_t, size> operator * (data_t a, Matrix<data_t, size>& A) {
        Matrix<data_t, size> M(A.size_);
        for (int i = 0; i < M.size_; i++) {
            for (int j = 0; j < M.size_; j++) {
                M [i] [j] = A [i] [j] * a;
            }
        }
        return M;
    }
    
    template <typename data_t, int size>
    Matrix<data_t, size>& operator ++ (Matrix<data_t, size>& A, int)  {
        for (int i = 0; i < A.size_; i++) {
            for (int j = 0; j < A.size_; j++) {
                A [i] [j]++;
            }
        }
        return A;
    }
    template <typename data_t, int size>
    Matrix<data_t, size>& operator -- (Matrix<data_t, size>& A, int)  {
        for (int i = 0; i < A.size_; i++) {
            for (int j = 0; j < A.size_; j++) {
                A [i] [j]--;
            }
        }
        return A;
    }
    template <typename data_t, int size>
    Matrix<data_t, size>& operator ++ (Matrix<data_t, size>& A)  {
        for (int i = 0; i < A.size_; i++) {
            for (int j = 0; j < A.size_; j++) {
                A [i] [j]++;
            }
        }
        return A;
    }
    template <typename data_t, int size>
    Matrix<data_t, size>& operator -- (Matrix<data_t, size>& A)  {
        for (int i = 0; i < A.size_; i++) {
            for (int j = 0; j < A.size_; j++) {
                A [i] [j]--;
            }
        }
        return A;
    }
    
    template <typename data_t, int size>
    const Matrix<data_t, size>& operator + (const Matrix<data_t, size>& A) {
        return A;
    }
    template <typename data_t, int size>
    Matrix<data_t, size> operator - (Matrix<data_t, size>& A)  {
        Matrix<data_t, size> M(A.size_);
        for (int i = 0; i < M.size_; i++) {
            for (int j = 0; j < M.size_; j++) {
                M [i] [j] = -(A [i] [j]);
            }
        }
        return M;
    }
    
    template <typename data_t, int size>
    Matrix<data_t, size> Matrix<data_t, size>::operator += (Matrix<data_t, size>& A)  {
        ASSERT_MAT(A.size_==(*this).size_)
        for (int i = 0; i < A.size_; i++) {
            for (int j = 0; j < A.size_; j++) {
                (*this) [i] [j] += (A [i] [j]);
            }
        }
        return *this;
    }
    
    
    template <typename data_t, int size>
    Matrix<data_t, size> Matrix<data_t, size>::operator -= (Matrix<data_t, size>& A)  {
        ASSERT_MAT(A.size_==(*this).size_)
        for (int i = 0; i < A.size_; i++) {
            for (int j = 0; j < A.size_; j++) {
                (*this) [i] [j] -= (A [i] [j]);
            }
        }
        return *this;
    }
    
    template <typename data_t, int size>
    Matrix<data_t, size> Matrix<data_t, size>::operator -= (data_t a)  {
        for (int i = 0; i < (*this).size_; i++) {
            for (int j = 0; j < (*this).size_; j++) {
                (*this) [i] [j] -= a;
            }
        }
        return *this;
    }
    template <typename data_t, int size>
    Matrix<data_t, size> Matrix<data_t, size>::operator += (data_t a)  {
        for (int i = 0; i < (*this).size_; i++) {
            for (int j = 0; j < (*this).size_; j++) {
                (*this) [i] [j] += a;
            }
        }
        return *this;
    }
    template <typename data_t, int size>
    Matrix<data_t, size> Matrix<data_t, size>::operator *= (data_t a)  {
        for (int i = 0; i < (*this).size_; i++) {
            for (int j = 0; j < (*this).size_; j++) {
                (*this) [i] [j] *= a;
            }
        }
        return *this;
    }
    template <typename data_t, int size>
    Matrix<data_t, size> Matrix<data_t, size>::operator /= (data_t a)  {
        for (int i = 0; i < (*this).size_; i++) {
            for (int j = 0; j < (*this).size_; j++) {
                (*this) [i] [j] -= a;
            }
        }
        return *this;
    }
    
    
    template <typename data_t, int size>
    bool Matrix<data_t, size>::operator == (Matrix<data_t, size>& A)  {
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
