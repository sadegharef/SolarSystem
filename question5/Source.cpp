#include <iostream>
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>
using namespace std;
//defining the angle
float firstcube = 0;
float secendcube = 0;
float lastcube = 0;
//drawing function
void draw() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPushMatrix();
    glTranslatef(-0.8f, 0.0f, 0.0f);
    glColor3f(1, 1, 1);
    glScalef(1.f, 2.0f, .5f);
    glutSolidCube(.4);
    glPushMatrix();
    glRotatef(firstcube, 0, 0, 1);
    glTranslatef(0.4f, 0.0f, 0.0f);
    glScalef(1.0f, .5f, 1.f);
    glColor3f(0, 0, 1);
    glutSolidCube(.4);
    glPushMatrix();
    glRotatef(secendcube, 0, 0, 1);
    glTranslatef(0.35f, 0.0f, 0.0f);
    glColor3f(0, 1, 0);
    glutSolidCube(.3);
    glPushMatrix();
    glRotatef(lastcube,0,0,1);
    glTranslatef(.25f, 0.0f, 0.0f);
    glColor3f(1, 0, 0);
    glutSolidCube(.2);
    glPopMatrix();
    glPopMatrix();
    glPopMatrix();
    glPopMatrix();
    //flush
    glFlush();
}
//reshaping
void reshape(int w, int h) {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(atan(tan(50.0 * 3.14159 / 360.0) / 1.0) * 360.0 / 3.141593, 1.0, 3.0, 7.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(2.0, 2.0, 2.0,
        0.0, 0.0, 0.0,
        0.0, 1.0, 0.0);
}
//define the variable speed
void keyboard(unsigned char key, int x, int y)
{

    switch (key) {
    case 'w':
        firstcube++;
        glutPostRedisplay();
        break;

    case 's': 
        firstcube--;
        glutPostRedisplay();
        break;

    case 'i':
        secendcube++;
        glutPostRedisplay();
        break;

    case 'k':
        secendcube--;
        glutPostRedisplay();
        break;

    case '8': 
        lastcube++;
        glutPostRedisplay();
        break;
    case '2':
        lastcube--;
        glutPostRedisplay();
        break;

    default:
        break;
    }
}
//main
int main(int argc, char* argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(640, 640);
    glutInitWindowPosition(540,200);
    glutCreateWindow("Bezier Curve");
    
    //myInit();
    cout << "Help:\n w: blue cube move up \n s: blue cube move down \n i: green cube move up \n"; 
    cout << " k: green cube move down\n 8: red cube move up\n 2: red cube move down ";
    glutDisplayFunc(draw);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutMainLoop();

    return 0;
}