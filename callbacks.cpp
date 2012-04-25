/* 
 * File:   callbacks.cpp
 * Author: wagner
 *
 * Created on 24 de Abril de 2012, 16:11
 */

#include <GL/glut.h>
//#include <GL/glew.h>

#include "callbacks.h"

void initialize(){
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    
    // Enable lighting
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);
    
    glDisable(GL_BLEND);
    glDisable(GL_CULL_FACE);
    
    glShadeModel(GL_FLAT);    
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lightAmbient);
    
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
    glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
    
}


void keyboardFunc(unsigned char key, int x, int y){
    
    if (TwEventKeyboardGLUT(key,x,y)) return;
    
    if (key=='Q' || key=='q' || key==KEY_SCAPE){
        std::cout << "Program terminated by the user.\n";
        exit(0);
    }					
					
    TwEventKeyboardGLUT(key,x,y);
}

void specialKeys(int key, int x, int y){
    
    if (key == GLUT_KEY_LEFT) camera.lookLefRigObj(-0.050 ); //camera.MoveFrente(0.025);
    if (key == GLUT_KEY_RIGHT) camera.lookLefRigObj(0.050 ); //camera.MoveFrente(-0.025);
    if (key == GLUT_KEY_UP) camera.MoveFrente(0.050);
    if (key == GLUT_KEY_DOWN) camera.MoveFrente(-0.050);
}

void renderScene(){
    
    glEnable(GL_LIGHTING);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    glLightfv(GL_LIGHT0, GL_POSITION, lightDir);
    
    camera.update();	
    camera.lookAt();
    
   
    
    

    mesh.drawSurface((primitive==true) ? GL_TRIANGLES : GL_LINE_LOOP , axis, limit, numStep);
    
    glDisable(GL_LIGHTING);
    drawAxis();  
    
    TwDraw();
    
    glutSwapBuffers();
    glutPostRedisplay();
}

void reshape(int w, int h){
    // Prevent a divide by zero, when window is too short
    // (you cant make a window of zero width).
    if(h == 0) h = 1; 

    // Use the Projection Matrix
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // Set the viewport to be the entire window
    glViewport(0, 0, w, h);
    
    // Send the new window size to AntTweakBar
    TwWindowSize(w, h);

    camera.setPerspec(45, (double)w/h, 0.5, 1000);

    // Get Back to the Modelview
    glMatrixMode(GL_MODELVIEW); 
}


void drawAxis(){
    glBegin(GL_LINES);
    glColor3f(1,0,0);
    glVertex3f(0,0,0); glVertex3f(1000,0,0);
    glEnd();
    glColor3f(0,1,0);
    glBegin(GL_LINES);
    glVertex3f(0,0,0); glVertex3f(0,1000,0);
    glEnd();
    glColor3f(0,0,1);
    glBegin(GL_LINES);
    glVertex3f(0,0,0); glVertex3f(0,0,1000);
    glEnd();   
}



void twGUI(TwBar *bar){
    
    TwDefine(" TweakBar size='195 400' color='96 216 224' "); // change default tweak bar size and color
    
    TwAddVarRW(bar, "Model", TW_TYPE_CSSTRING(255), &filename, "group='Rendering'");
    TwAddButton(bar,"Load", loadModel, NULL, "group='Rendering'");
    TwAddVarRW(bar, "Render", TW_TYPE_BOOLCPP, &primitive, "key='w' true='SOLID' false='WIRED' group='Rendering'");
   
    TwAddSeparator(bar,NULL,NULL);
    
    TwAddVarRW(bar, "Step", TW_TYPE_INT32, &numStep, "step=1 keyincr='+' keydecr='-' min=2 max=30 group='Settings'");
    TwAddVarRW(bar, "Limit", TW_TYPE_DOUBLE, &limit, "min=1 max=40 group='Settings'");
    TwAddVarRW(bar, "Axis Dir", TW_TYPE_DIR3D, &axis, "opened=true group='Settings'");
    
    
    /*
    //TwDefine(" GLOBAL help='' "); // Message added to the help bar.
    TwDefine(" TweakBar size='195 400' color='96 216 224' "); // change default tweak bar size and color
     
    TwAddButton(bar, "separator1", NULL, NULL, " label='Point or Tangent' group='Curve Config' ");
         
    TwAddVarRW(bar, "p1type", TW_TYPE_BOOLCPP, paramCurve.basis.p_or_t,"true='Point' false='Tangent' label='p1' group='Curve Config'");
    TwAddVarRW(bar, "p2type", TW_TYPE_BOOLCPP, paramCurve.basis.p_or_t+1,"true='Point' false='Tangent' label='p2' group='Curve Config'");
    TwAddVarRW(bar, "p3type", TW_TYPE_BOOLCPP, paramCurve.basis.p_or_t+2,"true='Point' false='Tangent' label='p3' group='Curve Config'");
    TwAddVarRW(bar, "p4type", TW_TYPE_BOOLCPP, paramCurve.basis.p_or_t+3,"true='Point' false='Tangent' label='p4' group='Curve Config'");
    
    TwAddButton(bar, "separator2", NULL, NULL, " label='Set Values' group='Curve Config' ");
    
    TwAddVarRW(bar, "p1val", TW_TYPE_FLOAT, paramCurve.basis.coef,"min=0 max=1 step=0.05 label='p1' group='Curve Config'");
    TwAddVarRW(bar, "p2val", TW_TYPE_FLOAT, paramCurve.basis.coef+1,"min=0 max=1 step=0.05 label='p2' group='Curve Config'");
    TwAddVarRW(bar, "p3val", TW_TYPE_FLOAT, paramCurve.basis.coef+2,"min=0 max=1 step=0.05 label='p3' group='Curve Config'");
    TwAddVarRW(bar, "p4val", TW_TYPE_FLOAT, paramCurve.basis.coef+3,"min=0 max=1 step=0.05 label='p4' group='Curve Config'");

    TwAddButton(bar, "separator3", NULL, NULL, " label='Fix/Unfix Points' group='Curve Config' ");
    
    TwAddVarRW(bar, "p1fix", TW_TYPE_BOOLCPP, paramCurve.basis.fixed,"true='locked' false='free' label='p1' group='Curve Config'");
    TwAddVarRW(bar, "p2fix", TW_TYPE_BOOLCPP, paramCurve.basis.fixed+1,"true='locked' false='free' label='p2' group='Curve Config'");
    TwAddVarRW(bar, "p3fix", TW_TYPE_BOOLCPP, paramCurve.basis.fixed+2,"true='locked' false='free' label='p3' group='Curve Config'");
    TwAddVarRW(bar, "p4fix", TW_TYPE_BOOLCPP, paramCurve.basis.fixed+3,"true='locked' false='free' label='p4' group='Curve Config'");
    
    TwAddVarRO(bar,"Determinant",TW_TYPE_DOUBLE, &(paramCurve.determinant) , "group='Settings'");
    TwAddVarCB(bar, "seg", TW_TYPE_INT32, customCurve::setNumberOfSegments,customCurve::getNumberOfSegments, &paramCurve,"min=2 max=100 step=2 keyincr='+' keydecr='-' label='Segments' group='Settings'");
    
    TwAddSeparator(bar,NULL,NULL);
    TwAddButton(bar,"update", updateBasis, (void*)&paramCurve.basis, "label='Update Values'");
    
    TwAddSeparator(bar,NULL,NULL);   
    
    TwAddButton(bar,"remove", removeUserPoint, NULL, "label='Remove Last Point' key='d'");
    TwAddButton(bar,"reset", resetCurve, NULL, "label='Reset All' key='x'");
    */
}

void loadModel(void*){
    
    std::ifstream file(filename);
    mesh.loadMeshOBJ(file);
}

int terminate(void){    
    TwTerminate();
}


