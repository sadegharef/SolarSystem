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
angleMoon = 0.0, 
angleEarth = 0.0, 
angleSun = 0.0,
anglePlanet2 = 0.0;
//define the scale of the veiw
GLfloat sx = 0.2, sy = 0.2, sz = 0.2;

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
//design the belt
/*void orbit()
{
    glColor3f(0.5, 0.5, 0.5);


    int i = 0;
    for (i = 0; i < 8; i++) {
        glPushMatrix();
        if (i == 5)
        {
            glRotatef(45, 1.0, 0.0, 0.0);
        }
        else
        {
            glRotatef(63, 1.0, 0.0, 0.0);
        }
        //glScalef(sc[i], sc[i], sc[i]);
        glBegin(GL_POINTS);
        double ang1 = 0.0;
        int i = 0;
        for (i = 0; i < 300; i++)
        {
            glVertex2d(cos(ang1), sin(ang1));
            ang1 += ang;
        }
        glEnd();
        glPopMatrix();
    }
}*/

void draw(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    background();
    //orbit();
    glLoadIdentity();
    glPushMatrix();
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);
    glPushMatrix();
    glColor3f(0.7, 0.5, 0.0);
    //glScalef(sx, sy, sz);
    glLightfv(GL_LIGHT7, GL_POSITION, qPos);
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, yellow);
    glutSolidSphere(1, 50, 50);
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, black);
    glPopMatrix();

    //glScalef(0.2, 0.2, 0.2);
    
    glPushMatrix();
    glRotatef(angleEarth, 0.0, 1.0, -0.5);
    glTranslatef(2.5, 0.0, 0.0);
    glColor3f(0.0, 0.1, 0.7);
    //glScalef(0.23, 0.23, 0.23);
    glutSolidSphere(1, 50, 50);
    glPushMatrix();
    glRotatef(angleMoon, 0.0, 0.1, 0.05);
    glTranslatef(1.3, 0.0, 0.0);
    glColor3f(1.0, 1.0, 1.0);
    //glScalef(0.5, 0.5, 0.5);
    glutSolidSphere(0.5, 50, 50);
    glPopMatrix();//moon made
    glPopMatrix();//earth made
    glPopMatrix();
    glFlush();
}


void update(int value) {

    if ((angleMoon >= 0 && angleMoon < 180))
    {
        sx -= 0.0003; sy -= 0.0003; sz -= 0.0003;
    }
    else
    { 
        sx += 0.0003; sy += 0.0003; sz += 0.0003;
    }


    angleMoon += 2;
    if (angleMoon > 360) {
        angleMoon -= 360;
    }
    angleEarth += 0.7;
    if (angleEarth > 360) {
        angleEarth -= 360;
    }

    glutPostRedisplay();
    glutTimerFunc(20, update, 0);
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
    glutTimerFunc(25, update, 0);
    glutMainLoop();
    return 0;
}