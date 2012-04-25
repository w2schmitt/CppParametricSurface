/* 
 * File:   Mesh.h
 * Author: wagner
 *
 * Created on 24 de Abril de 2012, 15:20
 */

#ifndef MESH_H
#define	MESH_H

#include <iostream>
#include <GL/glut.h>
#include <vector>
#include <fstream>
#include <boost/tokenizer.hpp>
#include "vector.hpp"
#include "util.h"

class Mesh {
public:
    bool isValid;
    Mesh();
    Mesh(const Mesh& orig);
    void draw(GLenum);
    void drawSurface(GLenum primitive, vec3d axis, float limit, int numSteps);
    void loadMeshOBJ(std::istream& in);
    virtual ~Mesh();
private:
    std::vector<Face> mesh;
    void clear();
};

#endif	/* MESH_H */

