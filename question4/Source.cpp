//include the librarys
#include<stdio.h>
#include<stdlib.h>
#include <GL/glut.h>
#include<math.h>
#include<time.h>
#include<windows.h>
// define the pi number
#define PI 3.14
//define the sphere angles
float
angleMoon_earth = 0.0,
angleMoon_itself = 0.0,
angleEarth_sun = 0.0,
angleEarth_itself = 0.0,
angleSun = 0.0,
anglePlanet2 = 0.0,
anglePlanet2_sun = 0.0;

//define the colors
GLfloat black[] = { 0.0f,0.0f,0.0f,1.0f };
GLfloat white[] = { 1.0f,1.0f,1.0f,1.0f };
GLfloat blue[] = { 0.0f,0.0f,0.9f,1.0f };
GLfloat er[] = { 0.0f,5.0f,0.9f,1.0f };
GLfloat yellow[] = { 0.7f,0.2f,0.0f,1.0f };
GLfloat qAmb[] = { 0.1,0.1,0.1,1.0 };
GLfloat qDif[] = { 1.0,1.0,1.0,1.0 };
GLfloat qSpec[] = { .50,.50,.50,.10 };
GLfloat qPos[] = { 0,0,0,0.1 };

//define the belt orbit of planet
//GLfloat sc[8] = { 0.295 , 0.40,0.50, 0.60,0.80,1.0,1.05,1.13 };
//double ang = 2 * PI / 300;//for normal planet
//double angular = 2 * PI / 50;// the belt of uranus


void initLighting()
{
    //glMaterialfv(GL_FRONT,GL_AMBIENT,yellow);
    //glMaterialfv(GL_FRONT,GL_SPECULAR,yellow);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT7);

    glLightfv(GL_LIGHT7, GL_AMBIENT, qAmb);
    glLightfv(GL_LIGHT7, GL_DIFFUSE, qDif);
    glLightfv(GL_LIGHT7, GL_SPECULAR, qSpec);
    //glMaterialfv(GL_FRONT,GL_DIFFUSE,yellow);
}
void myinit()
{
    glClearColor(0.0, 0.0, 0.0, 0.0); //backgroundcolor is green
    //gluOrtho2D(0,699,0,699);
    glPointSize(1.0);
    glLineWidth(2.0);

}

void background()
{
    glBegin(GL_QUADS);
    glColor3f(0.0, 0.00, 0.00);
    glVertex3f(-01.00, 01.00, 1);
    glColor3f(.20, 0.0, 0.70);
    glVertex3f(01.00, 1.00, 1);
    glColor3f(0, 0.0, 0.0);
    glVertex3f(1.00, -1.00, 1);
    glColor3f(.70, .10, .20);
    glVertex3f(-1.00, -1.00, 1);
    glEnd();
}

void draw(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    background();
    
    glLoadIdentity();
    
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);
    glScalef(0.05, 0.05, 0.05);
    

    //making sun
    glPushMatrix();
    glColor3f(6.0, 3.0, 0.0);
    glRotatef(angleSun, 0.0, 1.0, 0.0);
    glutSolidSphere(5, 20, 20);
    glPopMatrix();

    //making planet2
    glPushMatrix();
    glColor3f(0, 3.0, 3.0);
    glRotatef(anglePlanet2_sun, 0.0, 1.0, 0.0);
    glTranslatef(10 * cos(anglePlanet2_sun), 0, 8 * sin(anglePlanet2_sun));
    glRotatef(anglePlanet2, 0.0, 1.0, 0.0);
    glutSolidSphere(2, 20, 20);
    glPopMatrix();

    
    glPushMatrix();
    glRotatef(angleEarth_sun, 0.0, 1.0, 0.0);
    glTranslatef(15, 0.0, 0.0);
    glRotatef(angleEarth_itself, 0.0, 1.0, 0.0);
    glColor3f(0.0, 0.1, 0.7);
    glutSolidSphere(3, 20, 30);
    glPushMatrix();
    glRotatef(angleMoon_earth, 0.0, 0.0, 1.0);
    glTranslatef(0.0, 0.0, 5.0);
    glRotatef(angleMoon_itself, 0.0, 1.0, 0.0);//rotate around itself
    glColor3f(1.0, 1.0, 1.0);
    glutSolidSphere(0.5, 20, 30);
    glPopMatrix();
    glPopMatrix();
    
    //lighting
    glLightfv(GL_LIGHT7, GL_POSITION, qPos);
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, yellow);
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, black);


    glFlush();
}



void update(int value) {

    angleSun += 1;
    angleEarth_sun += 1;
    angleEarth_itself += 3;
    angleMoon_itself += 1;
    angleMoon_earth += 3;
    anglePlanet2 += 3;
    anglePlanet2_sun -= 0.01;
   
    glutPostRedisplay();
    glutTimerFunc(50, update, 0);
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(700, 700);
    glutCreateWindow("Solar System");
    initLighting();
    myinit();
    glutDisplayFunc(draw);
    glutTimerFunc(50, update, 0);
    glutMainLoop();
    return 0;
}