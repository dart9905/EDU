//
//  fract.cpp
//  KR
//
//  Created by macbook on 05/04/2019.
//  Copyright © 2019 macbook. All rights reserved.
//

#include "fract.hpp"


namespace frc
{
    template <typename data_t>
    class fract
    {
        data_t A_;
        data_t B_;
        data_t C_;
        
    public:
        
        fract();
        fract(data_t A, data_t B, data_t C);
        fract(const fract& A);
        
        ~fract();
        
        void set_A(data_t A);
        data_t get_A();
        
        void set_B(data_t A);
        data_t get_B();
        
        void set_C(data_t A);
        data_t get_C();
        
        
        fract&   operator = (const fract & arg);
        
        template <typename data_t1>
        friend fract<data_t1> operator + (const fract<data_t1>& A, const fract<data_t1>& B);
        
        template <typename data_t1>
        friend fract  operator * (const fract<data_t1>& A, const fract<data_t1>& B);
        
        template <typename data_t1>
        friend fract<data_t1> operator - (const fract<data_t1>& A, const fract<data_t1>& B);
        
        template <typename data_t1>
        friend fract<data_t1> operator / (const fract<data_t1>& A, const fract<data_t1>& B);
        
        
        template <typename data_t1>
        friend fract<data_t1>& operator ++ (fract<data_t1>& A, int);
        template <typename data_t1>
        friend fract<data_t1>& operator -- (fract<data_t1>& A, int);
        template <typename data_t1>
        friend fract<data_t1>& operator ++ (fract<data_t1>& A);
        template <typename data_t1>
        friend fract<data_t1>& operator -- (fract<data_t1>& A);
        
        template <typename data_t1>
        friend const fract<data_t1>& operator + (const fract<data_t1>& A);
        template <typename data_t1>
        friend fract<data_t1> operator - (const fract<data_t1>& A);
        
        fract operator += (const fract& A);
        fract operator -= (const fract& A);
        
        
        fract operator += (data_t a);
        fract operator -= (data_t a);
        fract operator *= (data_t a);
        fract operator /= (data_t a);
        
        
        
        template <typename data_t1>
        friend std::ostream& operator<< (std::ostream &out, const fract<data_t1> &A);
        template <typename data_t1>
        friend std::istream& operator>> (std::istream &in, fract<data_t1> &A);//*/
    };
    
    
    template <typename data_t>
    fract<data_t>::fract()
    {}
    
    template <typename data_t>
    fract<data_t>::fract(data_t A, data_t B, data_t C)
    {
        if (B == 0)
            throw 1;// деление на ноль
        A_ = A;
        B_ = B;
        C_ = C;
    }
    
    template <typename data_t>
    fract<data_t>::fract(const fract& A)
    {
        A_ = A.A_;
        B_ = A.B_;
        C_ = A.C_;
    }
    
    template <typename data_t>
    fract<data_t>:: ~fract() {
        A_ = 0;
        B_ = 0;
        C_ = 0;
    }
    
    
    template <typename data_t>
    void fract<data_t>::set_A(data_t A) {
        A_ = A;
    }
    template <typename data_t>
    void fract<data_t>::set_B(data_t A) {
        if (A == 0) {
            throw 1;
        }
        B_ = A;
    }
    template <typename data_t>
    void fract<data_t>::set_C(data_t A) {
        C_ = A;
    }
    
    template <typename data_t>
    data_t fract<data_t>::get_A () {
        return A_;
    }
    
    template <typename data_t>
    data_t fract<data_t>::get_B() {
        return B_;
    }
    template <typename data_t>
    data_t fract<data_t>::get_C() {
        return C_;
    }

    
    
    
    template <typename data_t>
    fract<data_t>& fract<data_t>::operator = (const fract& arg) {
        A_ = arg.A_;
        B_ = arg.B_;
        C_ = arg.C_;
        return *this;
    }
    
    
    
    template <typename data_t>
    fract<data_t> operator + (const fract<data_t>& A, const fract<data_t>& B)  {
        
        return fract<data_t>(A.A_ * B.B_ + B.A_ * A.B_, A.B_ * B.B_, A.C_ + B.C_);
    }
    
    template <typename data_t>
    fract<data_t> operator * (const fract<data_t>& A, const fract<data_t>& B) {
        return fract<data_t>((A.C_ * A.B_ + A.A_) * (B.C_ * B.B_ + B.A_), A.B_ * B.B_,0);
    }
    
    template <typename data_t>
    fract<data_t> operator - (const fract<data_t>& A, const fract<data_t>& B)  {
        return fract<data_t>(A.A_ * B.B_ - B.A_ * A.B_, A.B_ * B.B_, A.C_ - B.C_);
    }
    
    
    template <typename data_t>
    fract<data_t> operator / (const fract<data_t>& A, const fract<data_t>& B) {
        if (B.B_ != 0) {
            if (B.C_ * B.B_ + B.A_ == 0) {
                throw 1;
            }
        } else
            if (B.C_ == 0) {
                throw 1;
            }
        return fract<data_t>((A.C_ * A.B_ + A.A_) * B.B_, A.B_ * (B.C_ * B.B_ + B.A_),0);
    }
    
    
    template <typename data_t>
    fract<data_t>& operator ++ ( fract<data_t>& A, int) {
        A.C_++;
        return A;
    }
    
    template <typename data_t>
    fract<data_t>& operator ++ ( fract<data_t>& A) {
        A.C_++;
        return A;
    }
    template <typename data_t>
    fract<data_t>& operator -- ( fract<data_t>& A, int) {
        A.C_--;
        return A;
    }
    
    template <typename data_t>
    fract<data_t>& operator -- ( fract<data_t>& A) {
        A.C_--;
        return A;
    }
    
    
    template <typename data_t>
    fract<data_t> operator - ( const fract<data_t>& A) {
        
        fract<data_t> c(A);
        c.C_ = - c.C_;
        return c;
    }
    
    template <typename data_t>
    fract<data_t> operator + ( const fract<data_t>& A) {
        return A;
    }
    
    template <typename data_t>
    std::ostream& operator<< (std::ostream &out, const fract<data_t> &A)
    {
        out << A.C_<< " " << A.A_ << "/" << A.B_;
        
        return out;
    }
    
    template <typename data_t>
    std::istream& operator>> (std::istream &in, fract<data_t> &A)
    {
        
        in >> A.C_ >> A.A_ >> A.B_;
        
        return in;
    }
    //*/
}
