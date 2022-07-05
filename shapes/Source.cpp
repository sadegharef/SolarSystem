//defineing the library
#include <iostream>
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>
using namespace std;
//defining the angle
float firstcube = 0;
float secendcube = 0;
float lastcube = 0;
//drawing function using the stack
void draw() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPushMatrix();//making the first cube 
    glTranslatef(-0.8f, 0.0f, 0.0f);//set the location
    glColor3f(1, 1, 1);//set color
    glScalef(1.f, 2.0f, .5f);//set scale that make it horizontal Rectangle cube
    glutSolidCube(.4);// set the len of cube
    glPushMatrix();//make the secend cube
    glRotatef(firstcube, 0, 0, 1);//set the rotation
    glTranslatef(0.4f, 0.0f, 0.0f);//set the distance from first cube
    glScalef(1.0f, .5f, 1.f);// set the scale that make it vertical rectangle cube
    glColor3f(0, 0, 1);// set the color
    glutSolidCube(.4);// set len of cube
    glPushMatrix();// make the third cube
    glRotatef(secendcube, 0, 0, 1);//set the rotation
    glTranslatef(0.35f, 0.0f, 0.0f);// distance from secend cube
    glColor3f(0, 1, 0);//color
    glutSolidCube(.3);// the len of cube
    glPushMatrix();// make the last cube
    glRotatef(lastcube,0,0,1);// set the rotation
    glTranslatef(.25f, 0.0f, 0.0f);// distance from third cube
    glColor3f(1, 0, 0);// color
    glutSolidCube(.2);// set the len of cube
    glPopMatrix();// pop the last cube
    glPopMatrix();// pop the third cube
    glPopMatrix();// pop the secend cube
    glPopMatrix();// pop the first cube
    //flush
    glFlush();
}
//reshaping( this part obtain from the web https://www.khronos.org/opengl/wiki/Viewing_and_Transformations#How_does_the_camera_work_in_OpenGL.3F )
void reshape(int w, int h) {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(atan(tan(50.0 * 3.14159 / 360.0) / 1.0) * 360.0 / 3.141593, 1.0, 3.0, 7.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(2.0, 2.0, 2.0,// camera position
        0.0, 0.0, 0.0,//where camera look
        0.0, 1.0, 0.0);// up vector
}
//define the animation rules
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
    //help for keboard fuctions
    cout << "Help:\n w: blue cube move up \n s: blue cube move down \n i: green cube move up \n"; 
    cout << " k: green cube move down\n 8: red cube move up\n 2: red cube move down ";
    glutDisplayFunc(draw);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutMainLoop();

    return 0;
}