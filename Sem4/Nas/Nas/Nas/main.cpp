//
//  main.cpp
//  Nas
//
//  Created by macbook on 15/03/2019.
//  Copyright © 2019 macbook. All rights reserved.
//

#include <iostream>
#include <string>

class Person {
protected:
    std::string Name_;
    std::string SName_;
public:
    Person ():
    Name_("nikto"),
    SName_("nikak")
    {}
    
    Person (std::string Name, std::string sName):
    Name_(Name),
    SName_(sName)
    {}
    
    std::string getName() {
        return Name_;
    }
    std::string getSName() {
        return SName_;
    }
    
    void setName(std::string Name) {
        Name_ = Name;
    }
    void setSName(std::string SName) {
        SName_ = SName;
    }
    
    
};

class Prep: public Person {
    int nexui_ = 0;
public:
    Prep ():
    Person(),
    nexui_(0)
    {}
    
    Prep (std::string Name, std::string sName, int nexui):
    Person(Name, sName),
    nexui_(nexui)
    {}
    
    int getnexui() {
        return nexui_;
    }
    
    void setnexui(int A) {
        nexui_ = A;
    }
    
    
};
class Student: public Person {
    int level_ = 0;
public:
    Student ():
    Person(),
    level_(0)
    {}
    
    Student (std::string Name, std::string sName, int level):
    Person(Name, sName),
    level_(level)
    {}
    
    int getlevel() {
        return level_;
    }
    
    void setlevel(int A) {
        level_ = A;
    }
    
    
};

int main(int argc, const char * argv[]) {
    Student Kek ("Voik", "LOL", 11);
    // insert code here...
    std::cout << "Hello, World!\n" << Kek.getName();
    return 0;
}
