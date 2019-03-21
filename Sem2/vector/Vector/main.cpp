//
//  main.cpp
//  Vector
//
//  Created by macbook on 01.04.2018.
//  Copyright © 2018 macbook. All rights reserved.
//

#include <iostream>



#include <OpenGL/OpenGL.h>
#include <GLUT/GLUT.h>

#include <cassert>
#include <math.h>
#include <initializer_list>
#include <iterator>
#include "../resources/Vector.cpp"

void Graphics () {
    vectormy<int> a (3);
    vectormy<int> c = {0,5,1,5,4,1};
    a = c;
    //std::cout << a << std::endl;
    
    int max = 0;
    for (int i = 0; i < a.size(); i++)
        if (a [i] > max)
            max = a [i];
    
    glLineWidth(2);
    glBegin(GL_LINE_STRIP);
    glColor3f(1.0, 0.0, 0.0);
    for (double i = 0; i < a.size() - 1; i += 0.001) {
        glVertex2f(i * (740 - 150) / (a.size() - 1) + 150, a [i] * (500 - 100) / max + 100);
    }
    glEnd();
    
    glPointSize(10);
    glBegin(GL_POINTS);
    glColor3f(0.0, 0.5, 0.0);
    for (int i = 0; i <= a.size() - 1; i++) {
        glVertex2f(i * (740 - 150) / (a.size() - 1) + 150, a [i] * (500 - 100) / max + 100);
    }
    glEnd();
}

void reshape(int w, int h)
{
    glViewport(0, 0, w, h);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, w, 0, h);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void display()
{
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);
    
    glLineWidth(3);
    glBegin(GL_LINE_STRIP);
    glColor3f(0.0, 0.0, 0.0);
    glVertex2i(150, 500);
    glVertex2i(150, 100);
    glVertex2i(740, 100);
    glEnd();
    Graphics ();
    
    
    glutSwapBuffers();
}

int main(int argc, char * argv[]) {
    vectormy<bool> bol;
    bol [0] = true;
    bol [1] = false;
    
    
    //printf("%i%i%i\n%i%i%i\n",A[0],A[1],A[2],B[0],B[1],B[2]);
    
    
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA);
    
    glutInitWindowSize(900, 556);
    glutCreateWindow("Window1");
    
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    
    glutMainLoop();
    return 0;
}



