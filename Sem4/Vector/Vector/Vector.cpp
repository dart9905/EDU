//
//  Vector.cpp
//
//  Created by macbook on 22/03/2019.
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
#include "Vector.hpp"
#include "iostream"

namespace MatA {
    
    
    template <typename data_t, int size>
    class Vector
    {
        friend float ABS(const Vector& A);
        data_t data_ [size] = {NULL};
        int size_ = size;
        
    public:
        
        Vector();
        Vector(data_t A);
        Vector(data_t* data, int datasize);
        Vector(const Vector& A);
        
        ~Vector();
        
        void set(int i, data_t X);
        float get(int i);
        
        
        float& operator [] (int i);
        Vector&   operator = (const Vector & arg);
        Vector&   operator = (const data_t & arg);
        
        template <typename data_t1, int size1>
        friend Vector<data_t1, size1> operator + (const Vector<data_t1, size1>& A, const Vector<data_t1, size1>& B);
        
        template <typename data_t1, int size1>
        friend data_t1  operator * (const Vector<data_t1, size1>& A, const Vector<data_t1, size1>& B);
        
        template <typename data_t1, int size1>
        friend Vector<data_t1, size1> operator - (const Vector<data_t1, size1>& A, const Vector<data_t1, size1>& B);
        
        template <typename data_t1, int size1>
        friend Vector<data_t1, size1> operator ^ (const Vector<data_t1, size1>& A, const Vector<data_t1, size1>& B);
        
        template <typename data_t1, int size1>
        friend Vector<data_t1, size1> operator + (const Vector<data_t1, size1>& A, data_t1 a);
        template <typename data_t1, int size1>
        friend Vector<data_t1, size1> operator * (const Vector<data_t1, size1>& A, data_t1 a);
        template <typename data_t1, int size1>
        friend Vector<data_t1, size1> operator - (const Vector<data_t1, size1>& A, data_t1 a);
        template <typename data_t1, int size1>
        friend Vector<data_t1, size1> operator / (const Vector<data_t1, size1>& A, data_t1 a);
        template <typename data_t1, int size1>
        friend Vector<data_t1, size1> operator * (data_t a, const Vector<data_t1, size1>& A);
        
        template <typename data_t1, int size1>
        friend Vector<data_t1, size1>& operator ++ (Vector<data_t1, size1>& A, int);
        template <typename data_t1, int size1>
        friend Vector<data_t1, size1>& operator -- (Vector<data_t1, size1>& A, int);
        template <typename data_t1, int size1>
        friend Vector<data_t1, size1>& operator ++ (Vector<data_t1, size1>& A);
        template <typename data_t1, int size1>
        friend Vector<data_t1, size1>& operator -- (Vector<data_t1, size1>& A);
        
        template <typename data_t1, int size1>
        friend const Vector<data_t1, size1>& operator + (const Vector<data_t1, size1>& A);
        template <typename data_t1, int size1>
        friend Vector<data_t1, size1> operator - (const Vector<data_t1, size1>& A);
        
        Vector operator += (const Vector& A);
        Vector operator -= (const Vector& A);
        
        
        Vector operator += (data_t a);
        Vector operator -= (data_t a);
        Vector operator *= (data_t a);
        Vector operator /= (data_t a);
        
        bool operator == (const Vector& A);
        bool operator != (const Vector& A);
        bool operator >= (const Vector& A);
        bool operator <= (const Vector& A);
        bool operator >  (const Vector& A);
        bool operator <  (const Vector& A);
        
        
        
        template <typename data_t1, int size1>
        friend std::ostream& operator<< (std::ostream &out, const Vector<data_t1, size1> &A);
        template <typename data_t1, int size1>
        friend std::istream& operator>> (std::istream &in, Vector<data_t1, size1> &A);//*/
    };
    
    template <typename data_t, int size>
    float ABS (const Vector<data_t, size>& A) {
        return sqrt(A.x_ * A.x_ + A.y_ * A.y_ + A.z_ * A.z_);
    }
    template <typename data_t, int size>
    Vector<data_t, size>::Vector()
    {
        if (size_ != size)
            throw 12;// ошибка несовпадения размера
        //ASSERT_MAT(size_ == size)
    }
    
    template <typename data_t, int size>
    Vector<data_t, size>::Vector(data_t A)
    {
        if (size_ != size)
            throw 12;// ошибка несовпадения размера
        //ASSERT_MAT(size_ == size)
        for (int i = 0; i < size_; i++) {
            data_[i] = A;
        }
    }
    
    template <typename data_t, int size>
    Vector<data_t, size>::Vector(data_t* data, int datasize)
    {
        if (size_ != size)
            throw 12;// ошибка несовпадения размера
        //ASSERT_MAT(size_ == size)
        if (size_ != datasize)
            throw 11;// ошибка несовпадения размера
        //ASSERT_MAT(size_ == datasize)
        for (int i = 0; i < size_; i++) {
            data_[i] = data [i];
        }
    }
    
    template <typename data_t, int size>
    Vector<data_t, size>::Vector(const Vector& A)
    {
        if (size_ != size)
            throw 12;// ошибка несовпадения размера
        //ASSERT_MAT(size_ == size)
        if (size_ != A.size_)
            throw 10;// ошибка разных размеров векторов
        //ASSERT_MAT(size_ == A.size_)
        for (int i = 0; i < size_; i++) {
            data_[i] = A.data_ [i];
        }
    }
    
    template <typename data_t, int size>
    Vector<data_t, size>::~Vector() {
        for (int i = 0; i < size_; i++) {
            data_[i] = NULL;
        }
        size_ = 0;
    }
    
    
    template <typename data_t, int size>
    void Vector<data_t, size>::set(int i, data_t X) {
        if (size_ != size)
            throw 12;// ошибка несовпадения размера
        //ASSERT_MAT(size_ == size)
        if ((i >= size_) || (i < 0))
            throw 9;// ошибка выхода за массив
        //ASSERT_MAT((i < size_) && (i >= 0))
        data_[i] = X;
    }
    
    template <typename data_t, int size>
    float Vector<data_t, size>::get(int i) {
        if (size_ != size)
            throw 12;// ошибка несовпадения размера
        //ASSERT_MAT(size_ == size)
        if ((i >= size_) || (i < 0))
            throw 9;// ошибка выхода за массив
        //ASSERT_MAT((i < size_) && (i >= 0))
        return data_[i];
    }
    
    
    
    template <typename data_t, int size>
    float& Vector<data_t, size>::operator [] (int i) {
        if (size_ != size)
            throw 12;// ошибка несовпадения размера
        //ASSERT_MAT(size_ == size)
        if ((i >= size_) || (i < 0))
            throw 9;// ошибка выхода за массив
        //ASSERT_MAT((i < size_) && (i >= 0))
        return data_[i];
    }
    
    
    
    template <typename data_t, int size>
    Vector<data_t, size>& Vector<data_t, size>::operator = (const Vector& arg) {
        if (size_ != size)
            throw 12;// ошибка несовпадения размера
        //ASSERT_MAT(size_ == size)
        if (size_ != arg.size_)
            throw 10;// ошибка разных размеров векторов
        //ASSERT_MAT(size_ == arg.size_)
        for (int i = 0; i < size_; i++) {
            data_[i] = arg.data_ [i];
        }
        return *this;
    }
    
    template <typename data_t, int size>
    Vector<data_t, size>& Vector<data_t, size>::operator = (const data_t & arg) {
        if (size_ != size)
            throw 12;// ошибка несовпадения размера
        //ASSERT_MAT(size_ == size)
        for (int i = 0; i < size_; i++) {
            data_[i] = arg[i];
        }
        return *this;
    }
    
    
    
    
    template <typename data_t, int size>
    Vector<data_t, size> operator + (const Vector<data_t, size>& A, const Vector<data_t, size>& B)  {
        //Vector<data_t, size>(A.x_ + B.x_, A.y_ + B.y_, A.z_ + B.z_);
        
        Vector<data_t, size> c;
        for (int i = 0; i < size; i++) {
            c.data_[i] = A.data_[i] + B.data_[i];
        }
        return c;
        
    }
    
    template <typename data_t, int size>
    data_t operator * (const Vector<data_t, size>& A, const Vector<data_t, size>& B) {
        data_t c;
        for (int i = 0; i < size; i++) {
            c += A.data_[i] * B.data_[i];
        }
        return c;
    }
    
    template <typename data_t, int size>
    Vector<data_t, size> operator - (const Vector<data_t, size>& A, const Vector<data_t, size>& B)  {
        
        Vector<data_t, size> c;
        for (int i = 0; i < size; i++) {
            c.data_[i] = A.data_[i] - B.data_[i];
        }
        return c;
    }
    
    template <typename data_t, int size>
    Vector<data_t, size> operator ^ (const Vector<data_t, size>& A, const Vector<data_t, size>& B) {
        
        if (size > 3)
            throw 8;
        //ASSERT_MAT(size <= 3)
        
        
        Vector<data_t, size> c;
        
        c.data_[0] = A.data_[1] * B.data_[2] - A.data_[2] * B.data_[1];
        c.data_[1] = -A.data_[0] * B.data_[2] + A.data_[2] * B.data_[0];
        c.data_[2] = A.data_[0] * B.data_[1] - A.data_[1] * B.data_[0];
        
        return c;
    }
    
    template <typename data_t, int size>
    Vector<data_t, size> operator + (const Vector<data_t, size>& A, data_t a) {
        
        Vector<data_t, size> c;
        for (int i = 0; i < size; i++) {
            c.data_[i] = A.data_[i] + a;
        }
        return c;
    }
    
    template <typename data_t, int size>
    Vector<data_t, size> operator * (const Vector<data_t, size>& A, data_t a) {
        
        Vector<data_t, size> c;
        for (int i = 0; i < size; i++) {
            c.data_[i] = A.data_[i] * a;
        }
        return c;
    }
    
    
    template <typename data_t, int size>
    Vector<data_t, size> operator * (float a, const Vector<data_t, size>& A) {
        
        Vector<data_t, size> c;
        for (int i = 0; i < size; i++) {
            c.data_[i] = A.data_[i] * a;
        }
        return c;
    }
    
    template <typename data_t, int size>
    Vector<data_t, size> operator - (const Vector<data_t, size>& A, data_t a) {
        Vector<data_t, size> c;
        for (int i = 0; i < size; i++) {
            c.data_[i] = A.data_[i] - a;
        }
        return c;
    }
    
    template <typename data_t, int size>
    Vector<data_t, size> operator / (const Vector<data_t, size>& A, data_t a) {
        if (a == 0) {
            throw 7;
        }
        Vector<data_t, size> c;
        for (int i = 0; i < size; i++) {
            c.data_[i] = A.data_[i] / a;
        }
        return c;
    }
    
    
    template <typename data_t, int size>
    Vector<data_t, size>& operator ++ ( Vector<data_t, size>& A, int) {
        
        for (int i = 0; i < size; i++) {
            A.data_[i]++;
        }
        return A;
    }
    
    template <typename data_t, int size>
    Vector<data_t, size>& operator ++ ( Vector<data_t, size>& A) {
        for (int i = 0; i < size; i++) {
            A.data_[i]++;
        }
        return A;
    }
    template <typename data_t, int size>
    Vector<data_t, size>& operator -- ( Vector<data_t, size>& A, int) {
        for (int i = 0; i < size; i++) {
            A.data_[i]--;
        }
        return A;
    }
    template <typename data_t, int size>
    Vector<data_t, size>& operator -- ( Vector<data_t, size>& A) {
        for (int i = 0; i < size; i++) {
            A.data_[i]--;
        }
        return A;
    }
    
    
    template <typename data_t, int size>
    Vector<data_t, size> operator - ( const Vector<data_t, size>& A) {
        
        Vector<data_t, size> c;
        for (int i = 0; i < size; i++) {
            c.data_[i] = -A.data_[i];
        }
        return c;
    }
    
    template <typename data_t, int size>
    const Vector<data_t, size>& operator + ( const Vector<data_t, size>& A) {
        return A;
    }
    
    
    
    
    template <typename data_t, int size>
    Vector<data_t, size> Vector<data_t, size>::operator += (const Vector<data_t, size>& A) {
        for (int i = 0; i < size; i++) {
            data_[i] += A.data_[i];
        }
        return *this;
    }
    template <typename data_t, int size>
    Vector<data_t, size> Vector<data_t, size>::operator -= (const Vector<data_t, size>& A) {
        for (int i = 0; i < size; i++) {
            data_[i] -= A.data_[i];
        }
        return *this;
    }
    
    
    template <typename data_t, int size>
    Vector<data_t, size> Vector<data_t, size>::operator += (data_t a) {
        for (int i = 0; i < size; i++) {
            data_[i] += a;
        }
        return *this;
    }
    template <typename data_t, int size>
    Vector<data_t, size> Vector<data_t, size>::operator -= (data_t a) {
        for (int i = 0; i < size; i++) {
            data_[i] -= a;
        }
        return *this;
    }
    template <typename data_t, int size>
    Vector<data_t, size> Vector<data_t, size>::operator *= (data_t a) {
        for (int i = 0; i < size; i++) {
            data_[i] *= a;
        }
        return *this;
    }
    template <typename data_t, int size>
    Vector<data_t, size> Vector<data_t, size>::operator /= (data_t a) {
        if (a == 0) {
            throw 7;
        }
        for (int i = 0; i < size; i++) {
            data_[i] /= a;
        }
        return *this;
    }
    
    template <typename data_t, int size>
    bool Vector<data_t, size>::operator == (const Vector<data_t, size>& A) {
        if (ABS(A) == ABS(*this))
            return true;
        return false;
    }
    template <typename data_t, int size>
    bool Vector<data_t, size>::operator != (const Vector<data_t, size>& A) {
        if (ABS(A) != ABS(*this))
            return true;
        return false;
    }
    template <typename data_t, int size>
    bool Vector<data_t, size>::operator >= (const Vector<data_t, size>& A) {
        if (ABS(*this) >= ABS(A))
            return true;
        return false;
    }
    template <typename data_t, int size>
    bool Vector<data_t, size>::operator <= (const Vector<data_t, size>& A) {
        if (ABS(*this) <= ABS(A))
            return true;
        return false;
    }
    template <typename data_t, int size>
    bool Vector<data_t, size>::operator > (const Vector<data_t, size>& A) {
        if (ABS(*this) > ABS(A))
            return true;
        return false;
    }
    template <typename data_t, int size>
    bool Vector<data_t, size>::operator < (const Vector<data_t, size>& A) {
        if (ABS(*this) < ABS(A))
            return true;
        return false;
    }
    
    
    template <typename data_t, int size>
    std::ostream& operator<< (std::ostream &out, const Vector<data_t, size> &A)
    {
        out << "Vector3D(";
        for (int i = 0; i < size - 1; i++) {
            out << A.data_[i] << ", ";
        }
        
        out << A.data_[size - 1] << ")";
        
        return out;
    }
    
    template <typename data_t, int size>
    std::istream& operator>> (std::istream &in, Vector<data_t, size> &A)
    {
        
        for (int i = 0; i < size; i++) {
            in >> A.data_[i];
        }
        
        return in;
    }
     //*/
}
#undef ASSERT_MAT_S
#undef ASSERT_MAT
