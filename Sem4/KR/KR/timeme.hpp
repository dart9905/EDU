//
//  timeme.hpp
//  KR
//
//  Created by macbook on 05/04/2019.
//  Copyright © 2019 macbook. All rights reserved.
//

#ifndef timeme_hpp
#define timeme_hpp

#include <iostream>

namespace tmm
{
    class timehhmm
    {
    protected:
        int mm_ = 0;
        int hh_ = 0;
        void mminhh();
        int inmm() const;
    public:
        timehhmm();
        timehhmm(int mm);
        timehhmm(int hh, int mm);
        timehhmm(const timehhmm& data);
        virtual ~timehhmm();
        
        
        virtual void set_mm(int mm);
        virtual int get_mm();
        
        virtual void set_hh(int hh);
        virtual int get_hh();
        
        virtual timehhmm& operator = (const timehhmm & arg);
        virtual timehhmm& operator = (const int & arg);
        
        
        friend timehhmm operator + (const timehhmm& A, const timehhmm& B);
        friend timehhmm operator - (const timehhmm& A, const timehhmm& B);
        
        friend timehhmm& operator ++ (timehhmm& A, int);
        friend timehhmm& operator -- (timehhmm& A, int);
        friend timehhmm& operator ++ (timehhmm& A);
        friend timehhmm& operator -- (timehhmm& A);
        
        friend std::ostream& operator<< (std::ostream &out, const timehhmm &A);
        friend std::istream& operator>> (std::istream &in, timehhmm &A);
        
    };
    
    class timehhmmss: virtual protected timehhmm
    {
    protected:
        int ss_ = 0;
        void ssinmm();
        virtual int inss() const;
    public:
        timehhmmss();
        timehhmmss(int ss);
        timehhmmss(int hh, int mm, int ss);
        timehhmmss(const timehhmmss& data);
        virtual ~timehhmmss();
        
        
        virtual void set_ss(int mm);
        virtual int get_ss();
        
        virtual timehhmmss& operator = (const timehhmmss & arg);
        virtual timehhmmss& operator = (const int & arg);
        
        
        friend timehhmmss operator + (const timehhmmss& A, const timehhmmss& B);
        friend timehhmmss operator - (const timehhmmss& A, const timehhmmss& B);
        
        friend timehhmmss& operator ++ (timehhmmss& A, int);
        friend timehhmmss& operator -- (timehhmmss& A, int);
        friend timehhmmss& operator ++ (timehhmmss& A);
        friend timehhmmss& operator -- (timehhmmss& A);
        
        friend std::ostream& operator<< (std::ostream &out, const timehhmmss &A);
        friend std::istream& operator>> (std::istream &in, timehhmmss &A);
        
    };
    
    
    class timedatahhmmss: virtual protected timehhmmss
    {
    protected:
        int data_;
        void hhindata();
        int inss() const;
    public:
        timedatahhmmss();
        timedatahhmmss(int ss);
        timedatahhmmss(int data, int hh, int mm, int ss);
        timedatahhmmss(const timedatahhmmss& data);
        virtual ~timedatahhmmss();
        
        void set_ss(int ss);
        int get_ss();
        void set_mm(int ss);
        int get_mm();
        void set_hh(int ss);
        int get_hh();
        virtual void set_data(int data);
        virtual int get_data();
        
        virtual timedatahhmmss& operator = (const timedatahhmmss & arg);
        virtual timedatahhmmss& operator = (const int & arg);
        
        
        friend timedatahhmmss operator + (const timedatahhmmss& A, const timedatahhmmss& B);
        friend timedatahhmmss operator - (const timedatahhmmss& A, const timedatahhmmss& B);
        
        friend timedatahhmmss& operator ++ (timedatahhmmss& A, int);
        friend timedatahhmmss& operator -- (timedatahhmmss& A, int);
        friend timedatahhmmss& operator ++ (timedatahhmmss& A);
        friend timedatahhmmss& operator -- (timedatahhmmss& A);
        
        friend std::ostream& operator<< (std::ostream &out, const timedatahhmmss &A);
        friend std::istream& operator>> (std::istream &in, timedatahhmmss &A);
        
    };
    
    
    class timedatahhmm: virtual protected timehhmm
    {
    protected:
        int data_;
        void hhindata();
        int inmm() const;
    public:
        timedatahhmm();
        timedatahhmm(int mm);
        timedatahhmm(int data, int hh, int mm);
        timedatahhmm(const timedatahhmm& data);
        virtual ~timedatahhmm();

        void set_mm(int ss);
        int get_mm();
        void set_hh(int ss);
        int get_hh();
        virtual void set_data(int data);
        virtual int get_data();
        
        virtual timedatahhmm& operator = (const timedatahhmm & arg);
        virtual timedatahhmm& operator = (const int & arg);
        
        
        friend timedatahhmm operator + (const timedatahhmm& A, const timedatahhmm& B);
        friend timedatahhmm operator - (const timedatahhmm& A, const timedatahhmm& B);
        
        friend timedatahhmm& operator ++ (timedatahhmm& A, int);
        friend timedatahhmm& operator -- (timedatahhmm& A, int);
        friend timedatahhmm& operator ++ (timedatahhmm& A);
        friend timedatahhmm& operator -- (timedatahhmm& A);
        
        friend std::ostream& operator<< (std::ostream &out, const timedatahhmm &A);
        friend std::istream& operator>> (std::istream &in, timedatahhmm &A);
        
    };
}
#endif /* timeme_hpp */
