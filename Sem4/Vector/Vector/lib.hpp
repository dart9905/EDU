//
//  lib.hpp
//  Vector
//
//  Created by macbook on 08/02/2019.
//  Copyright © 2019 macbook. All rights reserved.
//

class Vector
{
private:
    float x, y, z;
    float C = 7;
    
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
};
