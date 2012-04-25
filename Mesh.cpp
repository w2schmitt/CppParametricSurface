/* 
 * File:   Mesh.cpp
 * Author: wagner
 * 
 * Created on 24 de Abril de 2012, 15:20
 */

#include <GL/glew.h>

#include "Mesh.h"

Mesh::Mesh() {
    isValid = false;
}

Mesh::Mesh(const Mesh& orig) {
}

Mesh::~Mesh() {
}

void Mesh::clear() {
    for (unsigned i=0; i<mesh.size(); ++i){
        mesh[i].v.clear();
        mesh[i].n.clear();
    }
    mesh.clear();    
}

void Mesh::loadMeshOBJ(std::istream& in){
    if (isValid)
        clear();
    
    std::clog << "Loading OBJ file" << std::endl;

    std::string line;

    std::vector<vec3d> vertices;
    std::vector<vec3d> normals;

    for(;;) {
        if (!getline(in, line))
                break;
        if (line == "")
                continue;

    switch (line[0]) {
        case 'v':
            if (line[1] == ' ') {
                    vec3d p;
                    if (sscanf(line.c_str()+2, "%lf %lf %lf", &p.x, &p.y, &p.z) != 3)
                            throw std::string("Error reading vertex at line " + line);

                    vertices.push_back(p);

            } else if (line[1] == 'n') {
                    vec3d n;
                    if (sscanf(line.c_str()+3, "%lf %lf %lf", &n.x, &n.y, &n.z) != 3)
                            throw std::string("Error reading normal at line " + line);

                    normals.push_back(n);
            }
            break;

        case 'f':
        {
            std::string content = line.substr(2);
            boost::char_separator<char> sep(" ");
            boost::tokenizer<boost::char_separator<char> > tok(content, sep);
            //int a=-2, b=-2, c=-2, na=-2, nb=-2, nc=-2;
            Face face;
            for (boost::tokenizer<boost::char_separator<char> >::iterator i=tok.begin(); i!=tok.end(); ++i) {
                    int v=-1, n=-1;
                    if (sscanf(i->c_str(), "%d//%d", &v, &n) != 2 &&
                        sscanf(i->c_str(), "%d/%*d/%d", &v, &n) != 2 &&
                        sscanf(i->c_str(), "%d/%*d", &v) != 1 ){
                    throw std::string("Error reading face at line " + line);
                    }

                    face.v.push_back(vertices.at(v-1));
                    if (n>0) 
                        face.v.push_back(normals.at(n-1));
            }
            mesh.push_back(face);
            break;
        }
    }
  }
  isValid = true;
  std::clog << "Loaded " << mesh.size() << " faces" << std::endl;        
}

void Mesh::drawSurface(GLenum primitive, vec3d axis, float limit, int numSteps){
    if (!isValid) return;
    
    std::vector<Face> surface;
    double inc = limit/(numSteps-1);
    axis.normalize();
    
    for (unsigned u=0; u < mesh.size(); ++u){
        surface.clear();
        surface.push_back(mesh[u]);
        for (unsigned i = 1; i < numSteps; ++i){
            Face f;
            for (unsigned j=0; j< mesh[u].v.size(); ++j ){
                // translate all vertices
                f.v.push_back(surface[i-1].v[j] + axis*inc);
            }
            surface.push_back(f);        
        }

        // draw surface
        glColor3f(1,1,1);

        GLfloat gray[] = {1.0f, 0.5f, 0.5f, 1.0f};
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, gray);
        glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);

        for (unsigned i=0; i < surface.size()-1; ++i){
            Face *f0 = &surface[i];
            Face *f1 = &surface[i+1];

            unsigned size = f0->v.size();

            glBegin(primitive);        
            for (unsigned j=0; j < size; ++j){
                unsigned c1 = j;
                unsigned c2 = (j+1)%size;
                vec3d n1 = cross(f0->v[c2] - f0->v[c1], f1->v[c1] - f0->v[c1]);
                vec3d n2 = cross(f1->v[c2] - f0->v[c2], f1->v[c1] - f0->v[c2]);
                n1.normalize();
                n2.normalize();

                // Tri 1
                glNormal3f(n1.x, n1.y, n1.z);
                glVertex3f(f0->v[c1].x, f0->v[c1].y, f0->v[c1].z); 
                glVertex3f(f0->v[c2].x, f0->v[c2].y, f0->v[c2].z);
                glVertex3f(f1->v[c1].x, f1->v[c1].y, f1->v[c1].z);

                // Tri 2
                glNormal3f(n2.x, n2.y, n2.z);
                glVertex3f(f0->v[c2].x, f0->v[c2].y, f0->v[c2].z); 
                glVertex3f(f1->v[c2].x, f1->v[c2].y, f1->v[c2].z);
                glVertex3f(f1->v[c1].x, f1->v[c1].y, f1->v[c1].z);             
            }
            glEnd();
        }
    }
}

void Mesh::draw(GLenum primitive){
    if (!isValid) return;
    glColor3f(1,1,1);
    
    for (unsigned i=0; i < mesh.size(); ++i){
        Face *f = &mesh[i];
        
        glBegin(primitive);        
        for (unsigned j; j < f->v.size(); ++j){
             glVertex3f(f->v[j].x, f->v[j].y, f->v[j].z); 
             //glNormal3f(t->a.x, t->a.y, t->a.z);   
        }
        glEnd();
    }
}

