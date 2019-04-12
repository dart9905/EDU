//
//  timeme.cpp
//  KR
//
//  Created by macbook on 05/04/2019.
//  Copyright © 2019 macbook. All rights reserved.
//

#include "timeme.hpp"

namespace tmm {
    
    timehhmm::timehhmm()
    {}
    
    timehhmm::timehhmm(int mm):
    mm_(mm)
    {
        if (mm_ < 0)
            throw 0;// отрицательно время
        mminhh();
    }
    
    timehhmm::timehhmm(int hh, int mm):
    hh_(hh),
    mm_(mm)
    {
        if (mm_ < 0)
            throw 0;// отрицательно время
        if (hh_ < 0)
            throw 0;// отрицательно время
        mminhh();
    }
    
    timehhmm::timehhmm(const timehhmm& data):
    mm_(data.mm_),
    hh_(data.hh_)
    {
        mminhh();
    }
    timehhmm::~timehhmm()
    {
        mm_ = 0;
        hh_ = 0;
    }
    
    
    void timehhmm::mminhh()
    {
        hh_ += (mm_ / 60);
        mm_ = mm_ - (mm_ / 60) * 60;
    }
    
    int timehhmm::inmm() const
    {
        return mm_ + hh_ * 60;
    }
    
    
    
    void timehhmm::set_mm(int mm)
    {
        if (mm < 0)
            throw 0;// отрицательно время
        mm_ = mm;
        mminhh();
    }
    int timehhmm::get_mm()
    {
        return mm_;
    }
    
    void timehhmm::set_hh(int hh)
    {
        if (hh < 0)
            throw 0;// отрицательно время
        hh_ = hh;
    }
    int timehhmm::get_hh()
    {
        return hh_;
    }
    
    timehhmm& timehhmm::operator = (const timehhmm & arg)
    {
        this->mm_ = arg.mm_;
        this->hh_ = arg.hh_;
        return *this;
    }
    timehhmm& timehhmm::operator = (const int & arg)
    {
        if (arg < 0)
            throw 0;// отрицательно время
        this->mm_ = arg;
        this->mminhh();
        return *this;
    }
    
    
    timehhmm operator + (const timehhmm& A, const timehhmm& B)
    {
        return timehhmm (A.hh_ + B.hh_, A.mm_ + B.mm_);
    }
    
    timehhmm operator - (const timehhmm& A, const timehhmm& B)
    {
        return timehhmm (A.timehhmm::inmm() - B.timehhmm::inmm());
    }
    
    
    
    timehhmm& operator ++ ( timehhmm& A, int)
    {
        A.mm_++;
        A.mminhh();
        return A;
    }
    timehhmm& operator ++ ( timehhmm& A)
    {
        A.mm_++;
        A.mminhh();
        return A;
    }
    timehhmm& operator -- ( timehhmm& A, int)
    {
        A.mm_--;
        if (A.mm_ < 0) {
            A.hh_--;
            A.mm_ = 59;
        }
        if (A.hh_ < 0)
            throw 0;// отрицательно время
        A.mminhh();
        return A;
    }
    timehhmm& operator -- ( timehhmm& A)
    {
        A.mm_--;
        if (A.mm_ < 0) {
            A.hh_--;
            A.mm_ = 59;
        }
        if (A.hh_ < 0)
            throw 0;// отрицательно время
        A.mminhh();
        return A;
    }
    
    
    std::ostream& operator<< (std::ostream &out, const timehhmm &A)
    {
        if (A.hh_ < 10) {
            out << "0" <<A.hh_ << ":";
        } else
            out << A.hh_ << ":";
        
        if (A.mm_ < 10) {
            out << "0" << A.mm_;
        } else
            out << A.mm_;
        
        return out;
    }
    
    std::istream& operator>> (std::istream &in, timehhmm &A)
    {
        in >> A.hh_;
        in >> A.mm_;
        A.mminhh();
        return in;
    }
    
    
    
    
    timehhmmss::timehhmmss()
    {}
    
    timehhmmss::timehhmmss(int ss):
    ss_(ss)
    {
        if (ss_ < 0)
            throw 0;// отрицательно время
        ssinmm();
        mminhh();
    }
    
    timehhmmss::timehhmmss(int hh, int mm, int ss):
    ss_(ss)
    {
        mm_ = mm;
        hh_ = hh;
        if (ss_ < 0)
            throw 0;// отрицательно время
        if (mm_ < 0)
            throw 0;// отрицательно время
        if (hh_ < 0)
            throw 0;// отрицательно время
        ssinmm();
        mminhh();
    }
    
    timehhmmss::timehhmmss(const timehhmmss& data):
    ss_(data.ss_)
    {
        mm_ = data.mm_;
        hh_ = data.hh_;
        
        ssinmm();
        mminhh();
    }
    
    timehhmmss::~timehhmmss()
    {
        ss_ = 0;
        mm_ = 0;
        hh_ = 0;
    }
    
    
    void timehhmmss::ssinmm()
    {
        mm_ += (ss_ / 60);
        ss_ = ss_ - (ss_ / 60) * 60;
    }
    
    int timehhmmss::inss() const
    {
        return (mm_ + hh_ * 60) * 60 + ss_;
    }
    
    
    
    void timehhmmss::set_ss(int ss)
    {
        if (ss < 0)
            throw 0;// отрицательно время
        ss_ = ss;
        ssinmm();
        mminhh();
    }
    int timehhmmss::get_ss()
    {
        return ss_;
    }
    
    timehhmmss& timehhmmss::operator = (const timehhmmss & arg)
    {
        this->ss_ = arg.ss_;
        this->mm_ = arg.mm_;
        this->hh_ = arg.hh_;
        return *this;
    }
    timehhmmss& timehhmmss::operator = (const int & arg)
    {
        if (arg < 0)
            throw 0;// отрицательно время
        this->ss_ = arg;
        this->ssinmm();
        this->mminhh();
        return *this;
    }
    
    
    timehhmmss operator + (const timehhmmss& A, const timehhmmss& B)
    {
        return timehhmmss (A.hh_ + B.hh_, A.mm_ + B.mm_, A.ss_ + B.ss_);
    }
    
    timehhmmss operator - (const timehhmmss& A, const timehhmmss& B)
    {
        return timehhmmss (A.timehhmmss::inss() - B.timehhmmss::inss());
    }
    
    
    
    timehhmmss& operator ++ ( timehhmmss& A, int)
    {
        A.ss_++;
        A.ssinmm();
        A.mminhh();
        return A;
    }
    timehhmmss& operator ++ ( timehhmmss& A)
    {
        A.ss_++;
        A.ssinmm();
        A.mminhh();
        return A;
    }
    timehhmmss& operator -- ( timehhmmss& A, int)
    {
        A.ss_--;
        if (A.ss_ < 0) {
            A.mm_--;
            A.ss_ = 59;
        }
        A.ssinmm();
        if (A.mm_ < 0) {
            A.hh_--;
            A.mm_ = 59;
        }
        A.mminhh();
        if (A.hh_ < 0)
            throw 0;// отрицательно время
        
        return A;
    }
    
    timehhmmss& operator -- ( timehhmmss& A)
    {
        A.ss_--;
        if (A.ss_ < 0) {
            A.mm_--;
            A.ss_ = 59;
        }
        A.ssinmm();
        if (A.mm_ < 0) {
            A.hh_--;
            A.mm_ = 59;
        }
        A.mminhh();
        if (A.hh_ < 0)
            throw 0;// отрицательно время
        
        return A;
        
        return A;
    }
    
    
    std::ostream& operator<< (std::ostream &out, const timehhmmss &A)
    {
        if (A.hh_ < 10) {
            out << "0" <<A.hh_ << ":";
        } else
            out << A.hh_ << ":";
        
        if (A.mm_ < 10) {
            out << "0" << A.mm_ << ":";
        } else
            out << A.mm_ << ":";
        
        if (A.ss_ < 10) {
            out << "0" << A.ss_;
        } else
            out << A.ss_;
        
        return out;
    }
    
    std::istream& operator>> (std::istream &in, timehhmmss &A)
    {
        in >> A.hh_;
        in >> A.mm_;
        in >> A.ss_;
        A.ssinmm();
        A.mminhh();
        return in;
    }
    
    
    timedatahhmmss::timedatahhmmss()
    {}
    
    timedatahhmmss::timedatahhmmss(int ss)
    {
        ss_ = ss;
        if (ss_ < 0)
            throw 0;// отрицательно время
        ssinmm();
        mminhh();
        hhindata();
    }
    
    timedatahhmmss::timedatahhmmss(int data, int hh, int mm, int ss)
    {
        ss_ = ss;
        mm_ = mm;
        hh_ = hh;
        data_ = data;
        if (ss_ < 0)
            throw 0;// отрицательно время
        if (mm_ < 0)
            throw 0;// отрицательно время
        if (hh_ < 0)
            throw 0;// отрицательно время
        if (data_ < 0)
            throw 0;// отрицательно время
        ssinmm();
        mminhh();
        hhindata();
    }
    
    timedatahhmmss::timedatahhmmss(const timedatahhmmss& data)
    {
        ss_     = data.ss_;
        mm_     = data.mm_;
        hh_     = data.hh_;
        data_   = data.data_;
        
        ssinmm();
        mminhh();
        hhindata();
    }
    
    timedatahhmmss::~timedatahhmmss()
    {
        ss_ = 0;
        mm_ = 0;
        hh_ = 0;
        data_ = 0;
    }
    
    
    void timedatahhmmss::hhindata()
    {
        data_ += (hh_ / 24);
        hh_ = hh_ - (hh_ / 24) * 24;
    }
    
    int timedatahhmmss::inss() const
    {
        return (mm_ + (data_ * 24 + hh_) * 60) * 60 + ss_;
    }
    
    void timedatahhmmss::set_ss(int ss)
    {
        if (ss < 0)
            throw 0;// отрицательно время
        ss_ = ss;
        ssinmm();
        mminhh();
        hhindata();
    }
    int timedatahhmmss::get_ss()
    {
        return ss_;
    }
    
    void timedatahhmmss::set_mm(int mm)
    {
        if (mm < 0)
            throw 0;// отрицательно время
        mm_ = mm;
        mminhh();
        hhindata();
    }
    int timedatahhmmss::get_mm()
    {
        return mm_;
    }
    
    void timedatahhmmss::set_hh(int hh)
    {
        if (hh < 0)
            throw 0;// отрицательно время
        hh_ = hh;
        hhindata();
    }
    int timedatahhmmss::get_hh()
    {
        return hh_;
    }
    
    void timedatahhmmss::set_data(int data)
    {
        if (data < 0)
            throw 0;// отрицательно время
        data_ = data;
    }
    
    int timedatahhmmss::get_data()
    {
        return data_;
    }
    
    
    timedatahhmmss& timedatahhmmss::operator = (const timedatahhmmss & arg)
    {
        this->ss_ = arg.ss_;
        this->mm_ = arg.mm_;
        this->hh_ = arg.hh_;
        this->data_ = arg.data_;
        return *this;
    }
    timedatahhmmss& timedatahhmmss::operator = (const int & arg)
    {
        if (arg < 0)
            throw 0;// отрицательно время
        this->ss_ = arg;
        this->ssinmm();
        this->mminhh();
        this->hhindata();
        return *this;
    }
    
    
    timedatahhmmss operator + (const timedatahhmmss& A, const timedatahhmmss& B)
    {
        return timedatahhmmss (A.data_ + B.data_, A.hh_ + B.hh_, A.mm_ + B.mm_, A.ss_ + B.ss_);
    }
    
    timedatahhmmss operator - (const timedatahhmmss& A, const timedatahhmmss& B)
    {
        return timedatahhmmss (A.timedatahhmmss::inss() - B.timedatahhmmss::inss());
    }
    
    
    
    timedatahhmmss& operator ++ ( timedatahhmmss& A, int)
    {
        A.ss_++;
        A.ssinmm();
        A.mminhh();
        A.hhindata();
        return A;
    }
    timedatahhmmss& operator ++ ( timedatahhmmss& A)
    {
        A.ss_++;
        A.ssinmm();
        A.mminhh();
        A.hhindata();
        return A;
    }
    timedatahhmmss& operator -- ( timedatahhmmss& A, int)
    {
        A.ss_--;
        if (A.ss_ < 0) {
            A.mm_--;
            A.ss_ = 59;
        }
        A.ssinmm();
        if (A.mm_ < 0) {
            A.hh_--;
            A.mm_ = 59;
        }
        A.mminhh();
        if (A.hh_ < 0) {
            A.data_--;
            A.hh_ = 23;
        }
        if (A.data_ < 0)
            throw 0;// отрицательно время
            
        
        
        return A;
    }
    
    timedatahhmmss& operator -- ( timedatahhmmss& A)
    {
        A.ss_--;
        if (A.ss_ < 0) {
            A.mm_--;
            A.ss_ = 59;
        }
        A.ssinmm();
        if (A.mm_ < 0) {
            A.hh_--;
            A.mm_ = 59;
        }
        A.mminhh();
        if (A.hh_ < 0) {
            A.data_--;
            A.mm_ = 24;
        }
        if (A.data_ < 0)
            throw 0;// отрицательно время
        
        return A;
    }
    
    
    std::ostream& operator<< (std::ostream &out, const timedatahhmmss &A)
    {
        out << A.data_ << " ";
        
        if (A.hh_ < 10) {
            out << "0" <<A.hh_ << ":";
        } else
            out << A.hh_ << ":";
        
        if (A.mm_ < 10) {
            out << "0" << A.mm_ << ":";
        } else
            out << A.mm_ << ":";
        
        if (A.ss_ < 10) {
            out << "0" << A.ss_;
        } else
            out << A.ss_;
        
        return out;
    }
    
    std::istream& operator>> (std::istream &in, timedatahhmmss &A)
    {
        in >> A.data_;
        in >> A.hh_;
        in >> A.mm_;
        in >> A.ss_;
        A.ssinmm();
        A.mminhh();
        A.hhindata();
        return in;
    }
    
    
    
    
    
    timedatahhmm::timedatahhmm()
    {}
    
    timedatahhmm::timedatahhmm(int mm)
    {
        mm_ = mm;
        if (mm_ < 0)
            throw 0;// отрицательно время
        mminhh();
        hhindata();
    }
    
    timedatahhmm::timedatahhmm(int data, int hh, int mm)
    {
        mm_ = mm;
        hh_ = hh;
        data_ = data;
        if (mm_ < 0)
            throw 0;// отрицательно время
        if (hh_ < 0)
            throw 0;// отрицательно время
        if (data_ < 0)
            throw 0;// отрицательно время
        mminhh();
        hhindata();
    }
    
    timedatahhmm::timedatahhmm(const timedatahhmm& data)
    {
        mm_     = data.mm_;
        hh_     = data.hh_;
        data_   = data.data_;
        
        mminhh();
        hhindata();
    }
    
    timedatahhmm::~timedatahhmm()
    {
        mm_ = 0;
        hh_ = 0;
        data_ = 0;
    }
    
    
    void timedatahhmm::hhindata()
    {
        data_ += (hh_ / 24);
        hh_ = hh_ - (hh_ / 24) * 24;
    }
    
    int timedatahhmm::inmm() const
    {
        return mm_ + (data_ * 24 + hh_) * 60;
    }
    
    void timedatahhmm::set_mm(int mm)
    {
        if (mm < 0)
            throw 0;// отрицательно время
        mm_ = mm;
        mminhh();
        hhindata();
    }
    int timedatahhmm::get_mm()
    {
        return mm_;
    }
    
    void timedatahhmm::set_hh(int hh)
    {
        if (hh < 0)
            throw 0;// отрицательно время
        hh_ = hh;
        hhindata();
    }
    int timedatahhmm::get_hh()
    {
        return hh_;
    }
    
    void timedatahhmm::set_data(int data)
    {
        if (data < 0)
            throw 0;// отрицательно время
        data_ = data;
    }
    
    int timedatahhmm::get_data()
    {
        return data_;
    }
    
    
    timedatahhmm& timedatahhmm::operator = (const timedatahhmm & arg)
    {
        this->mm_ = arg.mm_;
        this->hh_ = arg.hh_;
        this->data_ = arg.data_;
        return *this;
    }
    timedatahhmm& timedatahhmm::operator = (const int & arg)
    {
        if (arg < 0)
            throw 0;// отрицательно время
        this->mm_ = arg;
        this->mminhh();
        this->hhindata();
        return *this;
    }
    
    
    timedatahhmm operator + (const timedatahhmm& A, const timedatahhmm& B)
    {
        return timedatahhmm (A.data_ + B.data_, A.hh_ + B.hh_, A.mm_ + B.mm_);
    }
    
    timedatahhmm operator - (const timedatahhmm& A, const timedatahhmm& B)
    {
        return timedatahhmm (A.timedatahhmm::inmm() - B.timedatahhmm::inmm());
    }
    
    
    
    timedatahhmm& operator ++ ( timedatahhmm& A, int)
    {
        A.mm_++;
        A.mminhh();
        A.hhindata();
        return A;
    }
    timedatahhmm& operator ++ ( timedatahhmm& A)
    {
        A.mm_++;
        A.mminhh();
        A.hhindata();
        return A;
    }
    timedatahhmm& operator -- ( timedatahhmm& A, int)
    {
        A.mm_--;
        if (A.mm_ < 0) {
            A.hh_--;
            A.mm_ = 59;
        }
        A.mminhh();
        if (A.hh_ < 0) {
            A.data_--;
            A.hh_ = 23;
        }
        if (A.data_ < 0)
            throw 0;// отрицательно время
        
        
        
        return A;
    }
    
    timedatahhmm& operator -- ( timedatahhmm& A)
    {
        A.mm_--;
        if (A.mm_ < 0) {
            A.hh_--;
            A.mm_ = 59;
        }
        A.mminhh();
        if (A.hh_ < 0) {
            A.data_--;
            A.mm_ = 24;
        }
        if (A.data_ < 0)
            throw 0;// отрицательно время
        
        return A;
    }
    
    
    std::ostream& operator<< (std::ostream &out, const timedatahhmm &A)
    {
        out << A.data_ << " ";
        
        if (A.hh_ < 10) {
            out << "0" <<A.hh_ << ":";
        } else
            out << A.hh_ << ":";
        
        if (A.mm_ < 10) {
            out << "0" << A.mm_;
        } else
            out << A.mm_;
        
        return out;
    }
    
    std::istream& operator>> (std::istream &in, timedatahhmm &A)
    {
        in >> A.data_;
        in >> A.hh_;
        in >> A.mm_;
        A.mminhh();
        A.hhindata();
        return in;
    }
    
}
