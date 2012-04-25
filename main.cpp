/* 
 * File:   main.cpp
 * Author: wagner
 *
 * Created on 24 de Abril de 2012, 15:17
 */

#include <cstdlib>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include <AntTweakBar.h>

#include "callbacks.h"
#include "util.h"
#include "camera/float3.h"
#include "camera/Camera.h"

Window win = Window(800,600);


// opengl camera
Camera camera;

GLPrimitive primitive = WIRED;

// opengl light settings
GLfloat lightDir[] = {0.5, -0.5, 0.2, 0};
GLfloat lightDiffuse[] = {0.5, 0.55, 0.5, 1.0f};
GLfloat lightAmbient[] = {0.1, 0.1, 0.1, 1.0f};

// surface settings
double limit = 10.0;
int numStep = 10;
vec3d axis(0,1,0);

// mesh
Mesh mesh;
char filename[255] = "tests/plane.obj";


int main(int argc, char** argv) {
        
    TwBar *bar; // Pointer to the tweak bar
    
    // Initialize glut/glew/Anttweakbar/etc...
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH );
    glutInitWindowPosition(100,100);
    glutInitWindowSize(win.x, win.y);
    win.id = glutCreateWindow("Sweeps");

    GLenum glewStatus = glewInit();
    if (glewStatus != GLEW_OK){
      std::cerr << "[ERROR] "<< glewGetErrorString(glewStatus)<<std::endl;
    }
    TwInit(TW_OPENGL, NULL);
        
    glutDisplayFunc(renderScene);
    glutReshapeFunc(reshape);
    
    glutKeyboardFunc(keyboardFunc);
    glutSpecialFunc(specialKeys);
    glutMouseFunc((GLUTmousebuttonfun)TwEventMouseButtonGLUT);
    glutMotionFunc((GLUTmousemotionfun)TwEventMouseMotionGLUT);
    glutPassiveMotionFunc((GLUTmousemotionfun)TwEventMouseMotionGLUT);

    bar = TwNewBar("TweakBar");        
    twGUI(bar);
        
    initialize();

    atexit(terminate);
    glutMainLoop();
    return 0;
}