/*
 * File:   main_stepByStep.cpp
 * Author: polpe
 *
 * Created on February 10, 2014, 3:24 PM
 */

#include <cstdlib>
#include <iostream>
#include <vector>

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include "env.hpp"


//Vonal vector
std::vector<Svonal> vonalak;
//Tárolja h le van e nyomva
bool blent;
bool jlent;
//Kövi vastagsága
unsigned int vastag;


//Ablakméret:
int wH=400;
int wW=400;

Skoord* getClosestPoint(Skoord* c)
{
    double mint = *vonalak[0].getA()|*c;
    double mini = 0;
    bool   mina = true;
    for (int i = 0; i < vonalak.size(); ++i)
    {
        double tav = *vonalak[i].getA()|*c;
        if (tav<mint) {mint=tav; mini=i; mina=true;}
        tav = *vonalak[i].getB()|*c;
        if (tav<mint) {mint=tav; mini=i; mina=false;}
    }

}


//Ide írj, ha van saját inicializálási feladat
void SajatInit() {
    vastag = 2;
}


//Újrarajzolás
void ReDraw( ) {
    glClearColor(0.0, 0.0, 0.0, 0);
    glClear(GL_COLOR_BUFFER_BIT);

    for (int i = 0; i < vonalak.size(); ++i)
    {
        glLineWidth(vonalak[i].meret);
        glColor3d(vonalak[i].szin.rr/255.0, vonalak[i].szin.gg/255.0, vonalak[i].szin.bb/255.0);
        glBegin(GL_LINES);
            glVertex2d(vonalak[i].getA()->x, vonalak[i].getA()->y);
            glVertex2d(vonalak[i].getB()->x, vonalak[i].getB()->y);
        glEnd( );
    }


    glFlush( );
}





//Egér mozgára aktiválódik, kurzorpozíció koordinátáit kapja bemenetnek
void Motion(int x, int y) {
    if (blent)
    {
        vonalak[vonalak.size()-1].setB(Skoord(x,y));
        glutPostRedisplay();
    }
    
}


void MouseFunction(int button, int state, int x,int y)
{

    //bal gomb lenyomására
    if (button == GLUT_LEFT_BUTTON) {
        if  (state == GLUT_DOWN) { //le
            vonalak.push_back( Svonal( new Skoord(x,y), new Skoord(x,y),vastag,Sszin(rand()%256,rand()%256,rand()%256)) );
            blent=true;
        } else { //fel
            //vonalak[vonalak.size()-1].setB(Skoord(x,y));
            blent=false;
        }
    }

    //jobb gomb lenyomására/felengedésére (lásd 2.2 feladat)
    if (button == GLUT_RIGHT_BUTTON) {
        if  (state == GLUT_DOWN) { //le
            jlent=true;
        } else { //fel
            jlent=false;
        }
    }

    //A képernyő újrarajzolása (azaz redraw hívása)
    glutPostRedisplay();
}



void Keyboard(unsigned char key, int x, int y) {

    switch(key) {
        case 'c':
            vonalak.clear();
            break;
         case 'z':
            vonalak.pop_back();
            break;
        case 27:
            exit(0);
            break;
       default:
            break;
    }
    if (key>48 and key<60) vastag=key-48;
    //A képernyő újrarajzolása (azaz redraw hívása)
    glutPostRedisplay();
}



//--------------------------
//  Keret (nem kell módosítani)

//Inicializálás
void Init(){
    glViewport(0, 0, wW, wH);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity( );
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity( );
    gluOrtho2D(0.0, wW, wH, 0.0);
    SajatInit();
}

//Ablak átméretezésekor a teljes képet skálázza
void reshape(int w, int h) {
    glViewport(0,0,(GLsizei)w,(GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, wW, wH, 0.0);
    wW=w;
    wH=h;
}

int main(int argc, char* argv[])
{
    wW=400;
    wH=400;
    glutInitWindowSize(wW, wH);
    glutInitWindowPosition(100, 100);
    glutInit(&argc, argv);
    glutInitDisplayMode( GLUT_RGB );
    glutCreateWindow("DrawLine");
    Init();

    glutKeyboardFunc( Keyboard );
    glutDisplayFunc( ReDraw );
    glutMouseFunc(MouseFunction);
    glutMotionFunc(Motion);
    glutReshapeFunc(reshape);
    glutMainLoop();
}

