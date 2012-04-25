/* 
 * File:   callbacks.h
 * Author: wagner
 *
 * Created on 24 de Abril de 2012, 15:55
 */

#ifndef CALLBACKS_H
#define	CALLBACKS_H

#define KEY_SCAPE 27
#define WIRED false;
#define SOLID true;

#include <iostream>
#include <GL/glut.h>
#include <AntTweakBar.h>

#include "Mesh.h"
#include "camera/float3.h"
#include "camera/Camera.h"
#include "util.h"

extern Mesh mesh;
extern Camera camera;
extern GLfloat lightDir[];
extern GLfloat lightDiffuse[];
extern GLfloat lightAmbient[];

extern double limit;
extern int numStep;
extern vec3d axis;
extern GLPrimitive primitive;

extern char filename[255];

void initialize();
void renderScene();
void keyboardFunc(unsigned char key, int x, int y);
void specialKeys(int key, int x, int y);
void reshape(int w, int h);
void twGUI(TwBar *bar);

void drawAxis();
void loadModel(void*);
int terminate(void);


#endif	/* CALLBACKS_H */

