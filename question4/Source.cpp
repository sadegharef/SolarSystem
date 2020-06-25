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
angleMoon_sun = 0.0,
angleEarth_sun = 0.0,
angleEarth_itself = 0.0,
angleSun = 0.0,
anglePlanet2 = 0.0,
anglePlanet2_sun = 0.0;

//define the colors and gradient color for depth
GLfloat black[] = { 0.0f, 0.0f, 0.0f, 0.1f };
GLfloat white[] = { 0.0f, 1.0f, 1.0f, 1.0f };
GLfloat blue[] = { 0.0f, 0.0f, 0.9f, 1.0f };
GLfloat er[] = { 0.0f, 5.0f, 0.9f, 1.0f };
GLfloat yellow[] = { 1.0f, 1.2f, 0.0f, 1.1f };
GLfloat qAmb[] = { 0.1f, 0.1f, 0.1f, 0.5f };
GLfloat qDif[] = { 1.0f, 1.0f, 1.0f, 0.5f };
GLfloat qSpec[] = { .50f, .50f, .50f, 0.1f };
GLfloat qPos[] = { 0.0f, 0.0f, 0.0f, 8.0f };

//define the belt orbit of planet **fail**
//GLfloat sc[8] = { 0.295 , 0.40,0.50, 0.60,0.80,1.0,1.05,1.13 };
//double ang = 2 * PI / 300;//for normal planet
//double angular = 2 * PI / 50;// the belt of uranus


void initLighting()
{
    
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT7);
    //eanble lighting for depth and showing the light of sun
    glLightfv(GL_LIGHT7, GL_AMBIENT, qAmb);
    glLightfv(GL_LIGHT7, GL_DIFFUSE, qDif);
    glLightfv(GL_LIGHT7, GL_SPECULAR, qSpec);
    
}
void myinit()
{
    glClearColor(0, 0, 0, 0);
    glShadeModel(GL_FLAT);

    GLfloat light7_position[] = { -1.0, 1.0, 1.0, 0 }; // Light_7 position
    glLightfv(GL_LIGHT7, GL_POSITION, light7_position); // Define Light_7 

    glEnable(GL_LIGHTING); // Enable Lighting
    glEnable(GL_LIGHT7); // Enable Light_0
    glEnable(GL_DEPTH_TEST); // Enable Depth

}


void draw(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    //glLoadIdentity();//load objects
    //glScalef(0.05, 0.05, 0.05);// scale the matrix that can be seen on screen
    glEnable(GL_DEPTH_TEST);//enable depth
    glEnable(GL_COLOR_MATERIAL);//enable color
    
    

    //making sun
    glPushMatrix();
    glColor3f(10.0, 10.0, 0.0);//color
    glRotatef(angleSun, 0.0, 1.0, 0.0);//rotation around itself
    glutSolidSphere(5, 20, 20);//make with r=5
    glPopMatrix();
    //making planet2
    glPushMatrix();
    glColor3f(1.0, 1.0, 0.5);//color
    glRotatef(anglePlanet2_sun, 0.0, 1.0, 0.0);//rotation around the sun
    glTranslatef(10 * cos(anglePlanet2_sun), 0, 8 * sin(anglePlanet2_sun));// make the rotation path an Ellipse
    glRotatef(anglePlanet2, 0.0, 1.0, 0.0);//rotaton around itself
    glutSolidSphere(2, 20, 20);// make sphere with r=2
    glPopMatrix();
    //make earth
    glPushMatrix();
    glColor3f(.0, 0.3, 0.7);//color
    glRotatef(angleEarth_sun, 0.0, 1.0, 0.0);//rotation around the sun
    glTranslatef(15, 0.0, 0.0);// the circle path
    glRotatef(angleEarth_itself, 0.0, 1.0, 0.0);//rotation around itself
    glutSolidSphere(3, 20, 30);//make with r=3
    glPopMatrix();
    //make moon
    glPushMatrix();
    glColor3f(1.0, 1.0, 1.0);//color
    glRotatef(angleMoon_sun, 0.0, 1.0, 0.0);//rotation around sun
    glTranslatef(15, 0, 0);// distance from sun
    glRotatef(angleMoon_earth, 1.0, 0.0, -0.5);//around the earth
    glTranslatef(0.0, 5.0, 0.0);//distance from earth
    glRotatef(angleSun, 0.0, 1.0, 0.0);//rotate around itself
    glutSolidSphere(0.5, 20, 30);
    glPopMatrix();
    //lighting for light of the sun and showing the depth
    glLightfv(GL_LIGHT7, GL_POSITION, qPos);
    glMaterialfv(GL_FRONT_AND_BACK, GL_COLOR_INDEXES, yellow);
    glMaterialfv(GL_FRONT_AND_BACK, GL_COLOR_INDEXES, black);
    
    glFlush();
}



void timer(int value) {
    //changing an angle to set the speed of rotation
    angleSun += 1;
    angleEarth_sun += 1;
    angleEarth_itself += 3;
    angleMoon_sun += 1;
    angleMoon_earth += 3;
    anglePlanet2 += 3;
    anglePlanet2_sun -= 0.03;
    glutPostRedisplay();
    glutTimerFunc(30, timer, 0);
}
void reshape(int w, int h) {
    // Projection
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(90, 1, 1.0, 40.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    //glTranslatef(x, y, z);
    gluLookAt(0.0, 20.0, 10.0, // Camera position
        0.0, 0.0, 0.0, // Point the Camera looks at
        0.0, 1.0, 0.0); // Up-vector
}
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(0, 0);//set window position
    glutInitWindowSize(1080, 1080);//set window size
    glutCreateWindow("Solar System");//creating a window
    initLighting();// init light
    myinit();
    glutDisplayFunc(draw);//draw the objects
    glutTimerFunc(30, timer, 0);// timer
    glutReshapeFunc(reshape); // Projection
    glutMainLoop();
    return 0;
}