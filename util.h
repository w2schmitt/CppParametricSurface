/* 
 * File:   util.h
 * Author: wagner
 *
 * Created on 24 de Abril de 2012, 15:28
 */

#ifndef UTIL_H
#define	UTIL_H

#include <GL/glut.h>
#include "vector.hpp"
#include <vector>



typedef bool GLPrimitive;

struct Triangle{
    vec3d a,b,c, na, nb, nc;    
};

struct Face{
    std::vector<vec3d> v;  
    std::vector<vec3d> n;
};


struct Window {
    Window(int _x, int _y) : x(_x), y(_y){}  
    GLuint id;
    int x,y;
};

#endif	/* UTIL_H */

