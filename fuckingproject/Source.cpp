#include <iostream>
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>
using namespace std;

//Point class for taking the points
class Point
{
public:
    float x, y, z;
    void setxyz(float x2, float y2, float z2)
    {
        x = x2;
        y = y2;
        z = z2;
    }
    void setxy(float x2, float y2)
    {
        x = x2;
        y = y2;
    }
    //operator overloading for '=' sign
    const Point& operator=(const Point& rPoint)
    {
        x = rPoint.x;
        y = rPoint.y;
        z = rPoint.z;
        return *this;
    }

};

//define global variable
Point abc[4];
Point G[51];
int SCREEN_HEIGHT = 500;
int keyframe = 4;
int points = 0;
//define cube point and cube angle

//factorial
int factorial(int n)
{
    if (n <= 1)
        return(1);
    else
        n = n * factorial(n - 1);
    return n;
}
//tartib k az n
float binomial_coff(int n, float k)
{
    float ans;
    ans = (float)(factorial(n) / (factorial((int)k) * 1.0 * factorial(n - (int)k)));
    return ans;
}
//Calculate the bezier point [generalized]
Point drawBezierGeneralized(Point PT[], float t) {
    Point P;
    P.x = 0;
    P.y = 0;
    P.z = 0;
    for (int i = 0; i < keyframe; i++)
    {
        P.x = P.x + binomial_coff((keyframe - 1), (float)i) * pow(t, (float)i) * pow((1 - t), (keyframe - 1 - i)) * PT[i].x;
        P.y = P.y + binomial_coff((keyframe - 1), (float)i) * pow(t, (float)i) * pow((1 - t), (keyframe - 1 - i)) * PT[i].y;
        P.z = P.z + binomial_coff((keyframe - 1), (float)i) * pow(t, (float)i) * pow((1 - t), (keyframe - 1 - i)) * PT[i].z;
    }
    return P;
}
//estimating the angle between a normalize point and cube point
float estimateAngle(Point PT[], Point cube, int i) {
    float adotb = (PT[i].x * cube.x) + (PT[i].y * cube.y) + (PT[i].z * cube.z);
    float a = sqrt(pow(PT[i].x, 2) + pow(PT[i].y, 2) + pow(PT[i].z, 2));
    float b = sqrt(pow(cube.x, 2) + pow(cube.y, 2) + pow(cube.z, 2));

    return acosf(adotb / (a * b));
}
//define the init
void myInit() {
    glClearColor(.0, .0, .0, 0.0);
    glColor3f(0.0, 0.0, 0.0);
    glPointSize(3);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 640.0, 0.0, 500.0);
}
//drawing function
void draw() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //first cube
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, 3.0f);
    glColor3f(1, 1, 1);
    glScalef(0.8f, 1.6f, 0.4f);
    glutSolidCube(.4);
    glPopMatrix();
    //flush
    glFlush();
}
//on mouse click function
void myMouse(int button, int state, int x, int y) {
    // If left button was clicked
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        abc[0].setxyz(-0.6, 0.0, 0.0);
        abc[1].setxyz(0.0, 10.0, 0.0);
        abc[2].setxyz(0.4, 10.0, 20.0);
        abc[3].setxyz(0.4, 0.0, 0.0);


        glColor3f(0.2, 1.0, 0.0);
        int i = 0;
        Point p1 = abc[0];
        for (float t = 0.0; t <= 1.0; t += 0.02f)
        {
            Point p2 = drawBezierGeneralized(abc, t);
            cout << p2.x << ",  " << p2.y << ", " << p2.z << endl;
            cout << endl;
            G[i] = p2;
            i++;
        }
        glColor3f(0.0, 0.0, 0.0);
    }
}
//reshaping
void reshape(int w, int h) {
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(atan(tan(50.0 * 3.14159 / 360.0) / 1.0) * 360.0 / 3.141593, 1.0, 3.0, 7.0);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        gluLookAt(5.0, 3.0, 5.0,
            0.0, 0.0, 0.0,
            0.0, 1.0, 0.0);
}
//define the variable speed
void keyboard(unsigned char key, int x, int y)
{

    switch (key) {
    case '1':
        glutPostRedisplay();
        break;

    case '2':
        glutPostRedisplay();
        break;

    case '3':

        glutPostRedisplay();
        break;

    case '4':

        glutPostRedisplay();
        break;

    case '5':

        glutPostRedisplay();
        break;
    case '6':

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
    glutInitWindowSize(640, 500);
    glutInitWindowPosition(100, 150);
    glutCreateWindow("Bezier Curve");

    myInit();
    glutMouseFunc(myMouse);
    glutDisplayFunc(draw);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutMainLoop();

    return 0;
}