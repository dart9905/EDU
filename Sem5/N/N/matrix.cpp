//
//  matrix.cpp
//  Sys
//  Khromov Alexey
//  Created by macbook on 28/09/2019.
//  Copyright © 2019 macbook. All rights reserved.
//

#define ASSERT_MAT( expression ) \
if (expression) {\
\
} else {\
FILE *files = fopen ("LogFiles.txt", "at");\
\
fprintf(files, "==========ASSERT_MATRIX=========\n\n");\
fprintf(files, "ERROR:\nAssertion failed: %s\n   in file %s;\n   in line %i.\n", #expression, __FILE__, __LINE__);\
fprintf(files, "\n===========================\n\n");\
\
fclose(files);\
assert (expression);\
}


#include <cassert>
#include "iostream"

#include "matrix.hpp"




template <typename data_t>
class Vector;

template <typename data_t>
class subMatrix {
    int size_;
    data_t* data_;
public:
    
    subMatrix (int size)
    {
        size_ = size;
        data_ = new data_t [size_] {};
        ASSERT_MAT(data_ != NULL)
        
    }
    ~subMatrix()
    {
        delete [] data_;
    }
    
    data_t get (int y) const;
    data_t& set (int y);
    
    data_t& operator [] (int i);
    
};




template <typename data_t>
class Matrix {
    int size_;
    
    subMatrix<data_t>** data_;
    
public:
    Matrix ();
    Matrix (int size);
    Matrix (Matrix& M);
    ~Matrix ();
    
    int getsize() {
        return size_;
    }
    
    Matrix<data_t> T ();
    
    
    data_t det(int size = -1);
    bool nondegeneracy();
    bool positive();
    bool symmetry();
    
    int SubMatrixDet(int ni, int nj, Matrix<data_t> &M, int size = -1);
     
    
    subMatrix<data_t>& operator [] (int i);
    

    int BufToMatrix (char* buf);
    
    template <typename data_t1>
    friend std::ostream& operator<< (std::ostream &out, Matrix<data_t1> &M);
    template <typename data_t1>
    friend std::istream& operator>> (std::istream &in, Matrix<data_t1> &M);
    
    Matrix& operator = (const Matrix& A);
    Matrix& operator = (data_t x);
    //*
    template <typename data_t1>
    friend Matrix<data_t1> operator + (Matrix<data_t1>& A, Matrix<data_t1>& B);
    template <typename data_t1>
    friend Matrix<data_t1> operator * (Matrix<data_t1>& A, Matrix<data_t1>& B);
    template <typename data_t1>
    friend Matrix<data_t1> operator - (Matrix<data_t1>& A, Matrix<data_t1>& B);
    
    template <typename data_t1>
    friend Matrix<data_t1> operator * (Matrix<data_t1>& A, data_t a);
    template <typename data_t1>
    friend Matrix<data_t1> operator / (Matrix<data_t1>& A, data_t a);
    template <typename data_t1>
    friend Matrix<data_t1> operator * (float a, Matrix<data_t1>& A);
    
    
    template <typename data_t1>
    friend const Matrix<data_t1>& operator + (const Matrix<data_t1>& A);
    template <typename data_t1>
    friend Matrix<data_t1> operator - (Matrix<data_t1>& A);
    
    Matrix operator += (Matrix& A);
    Matrix operator -= (Matrix& A);
    
    Matrix operator *= (data_t a);
    
    bool operator == (const Matrix& A);
    bool operator != (const Matrix& A);
    
    template <typename data_t1>
    friend bool operator == (Matrix<data_t1>& A, Matrix<data_t1>& B);
    
    template <typename data_t1>
    friend Vector <data_t1> operator * (Matrix<data_t1>& A, Vector<data_t1>& B);
    //*
    
};


template <typename data_t>
Matrix<data_t>::Matrix ():
size_(1)
{
    data_ = new subMatrix<data_t>* [size_];
    ASSERT_MAT(data_ != NULL)
    for (int i = 0; i < size_; i++) {
        data_ [i] = new subMatrix<data_t> (size_);
        
        ASSERT_MAT(data_[i] != NULL)
    }
    
}


template <typename data_t>
Matrix<data_t>::Matrix (int size):
size_(size)
{
    if (size_ < 1) {
        ASSERT_MAT (size_ < 1)
    }
    
    data_ = new subMatrix<data_t>* [size_];
    ASSERT_MAT(data_ != NULL)
    for (int i = 0; i < size_; i++) {
        data_ [i] = new subMatrix<data_t> (size_);
        ASSERT_MAT(data_ != NULL)
    }
    
}


template <typename data_t>
Matrix<data_t>::Matrix (Matrix<data_t>& M):
size_(M.size_)
{
    if (size_ < 1) {
        ASSERT_MAT (size_ < 1)
    }
    
    data_ = new subMatrix<data_t>* [size_];
    ASSERT_MAT(data_ != NULL)
    for (int i = 0; i < size_; i++) {
        data_ [i] = new subMatrix<data_t> (size_);
        ASSERT_MAT(data_ != NULL)
    }
    
    for (int i = 0; i < size_; i++) {
        for (int j = 0; j < size_; j++) {
            (*this) [i] [j] = M[i][j];
        }
    }
}


template <typename data_t>
Matrix<data_t>::~Matrix () {
    delete [] data_;
}

/*
 2
 -1  -10
 -10  -1
 
 
 */
template <typename data_t>
int Matrix<data_t>::BufToMatrix (char* buf) {
    
    for (int i = 0, k = 1, h = 1, s = 0; i < size_; i++) {
        for (int j = 0; j < size_; j++, h = 1, s = 0) {
            for (; (buf [k] == ' ') || ((buf [k] == '\n')); k++);
            ASSERT_MAT(buf[k] != '\0')
            if (buf [k] == '-') {
                k++;
                h = -1;
            }
            ASSERT_MAT(buf[k] != '\0')
            for (; (buf [k] != ' ') && (buf [k] != '\n') && (buf [k] != '\0'); k++) {
                s = s * 10 + (buf [k] - '0');
            }
            (*this) [i] [j] = h * s;
            
        }
    }
    return 0;
}


template <typename data_t>
int Matrix<data_t>::SubMatrixDet(int ni, int nj, Matrix<data_t> &M, int size) {
    
    
    if (size == -1) {
        size = size_;
    }
    
    ASSERT_MAT(size > 0)
    
    for (int i = 0, g = 0; i < size - 1; i++, g++) {
        if (g == nj)
            g++;
        for (int j = 0, h = 0; j < size - 1; j++, h++) {
            
            if (h == ni)
                h++;
            M [i] [j] = ((*this) [g] [h]);
        }
    }
    return 0;
}


template <typename data_t>
data_t Matrix<data_t>::det (int size) {
    
    if (size == -1) {
        size = size_;
    }
    
    ASSERT_MAT(size > 0)
    
    if (size == 1)
        return ((*this) [0] [0]);
    
    data_t D = 0;
    Matrix<data_t>* M;
    M = new Matrix<data_t> (size - 1);
    ASSERT_MAT(data_ != NULL)
    
    
    for (int i = 0, j = 1; i < size; i++, j *= -1) {
        if ((*this) [0] [i] != 0) {
            SubMatrixDet(i,0,  *M, size);
            D += ((*this) [0] [i]) * M->det() * j;
        }
    }
    
    
    delete M;
    
    return D;
}

//*
template <typename data_t>
bool Matrix<data_t>::nondegeneracy() {
    
    if (this->det() == 0) {
        return false;
    }
    
    Matrix<data_t>* M;
    M = new Matrix<data_t> (size_ - 1);
    ASSERT_MAT(data_ != NULL)
    
    
    for (int i = 0; i < size_; i++) {
        SubMatrixDet(i,i,  *M);
        if (M->det() == 0) {
            delete M;
            return false;
        }
    }

    delete M;
    
    return true;
}

template <typename data_t>
bool Matrix<data_t>::positive() {
    
    if (this->det() <= 0) {
        return false;
    }
    
    if (size_ == 1) {
        return true;
    }
    
    Matrix<data_t>* M;
    M = new Matrix<data_t> (size_ - 1);
    ASSERT_MAT(data_ != NULL)
    
    SubMatrixDet(size_ - 1, size_ - 1,  *M);
    
    if (!(M->positive())) {
        delete M;
        return false;
    }

    delete M;
    
    return true;
}


template <typename data_t>
bool Matrix<data_t>::symmetry() {
    
    for (int i = 0; i < size_ - 1; i++) {
        for (int j = i + 1; j < size_; j++) {
            if ((*this) [i] [j] != (*this) [j] [i])
                return false;
        }
    }
    
    return true;
}

//*/

template <typename data_t>
subMatrix<data_t>& Matrix<data_t>::operator [] (int i) {
    
    ASSERT_MAT((i>=0 && i<size_))
    
    return *(data_[i]);
}

template <typename data_t>
data_t& subMatrix<data_t>::operator [] (int i) {
    ASSERT_MAT((i>=0 && i<size_))
    return data_[i];
}


template <typename data_t>
std::ostream& operator<< (std::ostream &out, Matrix<data_t> &M)
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
        
template <typename data_t>
std::istream& operator>> (std::istream &in, Matrix<data_t> &M)
{
    
    for (int i = 0; i < M.size_; i++) {
        for (int j = 0; j < M.size_; j++) {
            in >> M [i] [j];
        }
    }
    
    return in;
}


template <typename data_t>
Matrix<data_t>& Matrix<data_t>::operator = (const Matrix<data_t> & A) {
        
    ASSERT_MAT(A.size_ == (*this).size_)
        
    for (int i = 0; i < A.size_; i++) {
        for (int j = 0; j < A.size_; j++) {
        (*this) [i] [j] = A.data_[i]->operator[](j);
        //A.data_[i].operator[](j);
        }
    }
    
    return *this;
}

template <typename data_t>
Matrix<data_t>& Matrix<data_t>::operator = (data_t x) {
    
    for (int i = 0; i < size_; i++) {
        for (int j = 0; j < size_; j++) {
        (*this) [i] [j] = x;
        //A.data_[i].operator[](j);
        }
    }
    
    return *this;
}


template <typename data_t>
Matrix<data_t> operator + (Matrix<data_t>& A, Matrix<data_t>& B)  {
    ASSERT_MAT((A.size_ == B.size_))
        
    Matrix<data_t> M(A.size_);
    for (int i = 0; i < M.size_; i++) {
        for (int j = 0; j < M.size_; j++) {
            M [i] [j] = A [i] [j] + B [i] [j];
        }
    }
    return M;
}

template <typename data_t>
Matrix<data_t> operator - (Matrix<data_t>& A, Matrix<data_t>& B)  {
    
    Matrix<data_t> M(A.size_);
    for (int i = 0; i < M.size_; i++) {
        for (int j = 0; j < M.size_; j++) {
            M [i] [j] = A [i] [j] - B [i] [j];
        }
    }
    return M;
}


        
        
template <typename data_t>
Matrix<data_t> operator * (Matrix<data_t>& A, Matrix<data_t>& B) {
    ASSERT_MAT(A.size_==B.size_)
    Matrix<data_t> M (A.size_);
    for (int i = 0; i < M.size_; i++) {
        for (int j = 0; j < M.size_; j++) {
            for (int k = 0; k < M.size_; k++) {
                M [i] [j] += A [i] [k] * B [k] [j];
            }
        }
    }
    return M;
}

template <typename data_t>
Matrix<data_t> operator * (Matrix<data_t>& A, data_t a) {
    Matrix<data_t> M (A.size_);
    for (int i = 0; i < M.size_; i++) {
        for (int j = 0; j < M.size_; j++) {
            M [i] [j] = A [i] [j] * a;
        }
    }
    return M;
}

template <typename data_t>
Matrix<data_t> operator / (Matrix<data_t>& A, data_t a) {
    Matrix<data_t> M (A.size_);
    for (int i = 0; i < M.size_; i++) {
        for (int j = 0; j < M.size_; j++) {
            M [i] [j] = A [i] [j] / a;
        }
    }
    return M;
}

template <typename data_t>
Matrix<data_t> operator * (data_t a, Matrix<data_t>& A) {
    Matrix<data_t> M (A.size_);
    for (int i = 0; i < M.size_; i++) {
        for (int j = 0; j < M.size_; j++) {
            M [i] [j] = A [i] [j] * a;
        }
    }
    return M;
}

template <typename data_t>
const Matrix<data_t>& operator + (const Matrix<data_t>& A) {
    return A;
}
template <typename data_t>
Matrix<data_t> operator - (Matrix<data_t>& A)  {
    Matrix<data_t> M (A.size_);
    for (int i = 0; i < M.size_; i++) {
        for (int j = 0; j < M.size_; j++) {
            M [i] [j] = -(A [i] [j]);
        }
    }
    return M;
}

template <typename data_t>
Matrix<data_t> Matrix<data_t>::operator += (Matrix<data_t>& A)  {
    ASSERT_MAT(A.size_==(*this).size_)
    for (int i = 0; i < A.size_; i++) {
        for (int j = 0; j < A.size_; j++) {
            (*this) [i] [j] += (A [i] [j]);
        }
    }
    return *this;
}


template <typename data_t>
Matrix<data_t> Matrix<data_t>::operator -= (Matrix<data_t>& A)  {
    ASSERT_MAT(A.size_==(*this).size_)
    for (int i = 0; i < A.size_; i++) {
        for (int j = 0; j < A.size_; j++) {
            (*this) [i] [j] -= (A [i] [j]);
        }
    }
    return *this;
}

template <typename data_t>
Matrix<data_t> Matrix<data_t>::operator *= (data_t a)  {
    for (int i = 0; i < (*this).size_; i++) {
        for (int j = 0; j < (*this).size_; j++) {
            (*this) [i] [j] *= a;
        }
    }
    return *this;
}
        
template <typename data_t>
bool operator == (Matrix<data_t>& A, Matrix<data_t>& B) {
    ASSERT_MAT(A.size_==B.size_)
    for (int i = 0; i < A.size_; i++) {
        for (int j = 0; j < A.size_; j++) {
            if (B [i] [j] != (A [i] [j]))
                return false;
        }
    }
    return true;
}


template <typename data_t>
bool Matrix<data_t>::operator != (const Matrix<data_t>& A)  {
    ASSERT_MAT(A.size_==(*this).size_)
    if ((*this) == A) {
        return false;
    }
    return true;
}

template <typename data_t>
bool Matrix<data_t>::operator == (const Matrix<data_t>& A)  {
    ASSERT_MAT(A.size_==(*this).size_)
    for (int i = 0; i < A.size_; i++) {
        for (int j = 0; j < A.size_; j++) {
            if ((*this) [i] [j] != A.data_[i]->operator[](j))
                return false;
        }
    }
    return true;
}
            


                
                

template <typename data_t>
Matrix<data_t> Matrix<data_t>::T () {
    Matrix<data_t> M (size_);
    for (int i = 0; i < M.size_; i++) {
        for (int j = 0; j < M.size_; j++) {
            M [i] [j] = (*this) [j] [i];
        }
    }
    return M;
}

#undef ASSERT_MAT
