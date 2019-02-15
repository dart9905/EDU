//
//  lib.hpp
//  Vector
//
//  Created by macbook on 08/02/2019.
//  Copyright © 2019 macbook. All rights reserved.
//

namespace MatA {
    class Vector
    {
        friend double ABS(Vector A);
    private:
        float x, y, z;
        
    public:
        
        Vector();
        Vector(float A);
        Vector(float X, float Y, float Z);
        
        ~Vector();
        
        void set_x(float X);
        float get_x();
        
        void set_y(float Y);
        float get_y();
        
        void set_z(float Z);
        float get_z();
        
        Vector operator + (Vector B);
        double operator * (Vector B);
        Vector operator - (Vector B);
        Vector operator ^ (Vector B);
        
        Vector operator + (double a);
        Vector operator * (double a);
        Vector operator - (double a);
        Vector operator / (double a);
        
    };

}
