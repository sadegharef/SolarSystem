#include <iostream>
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>
using namespace std;
//Point class for taking the points
class Point
{
public:
    GLfloat x, y, z;
    void setxyz(GLfloat x2, GLfloat y2, GLfloat z2)
    {
        x = x2;
        y = y2;
        z = z2;
    }
    void setxy(GLfloat x2, GLfloat y2)
    {
        x = x2;
        y = y2;
    }
};
//define global variable
Point keyFrame[4];
Point bezierpoint[102];
GLfloat G[102][2];
int keyframe = 4;
//factorial
int factorial(int n)
{
    if (n <= 1)
        return(1);
    else
        n = n * factorial(n - 1);
    return n;
}
//tarkib k az n
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
//array of distance
GLfloat distance(Point a, Point b) {
    return sqrtf(pow(b.x - a.x, 2) + pow(b.y - a.y, 2) + pow(b.z - a.z, 2));
}
//init keyframe
void makeKeyFrames() {
    //init the keyframes
    keyFrame[0].setxyz(0.0, 0.0, 3.0);
    keyFrame[1].setxyz(2.0, -2.5, 2.0);
    keyFrame[2].setxyz(0.0, 3.0, -3.0);
    keyFrame[3].setxyz(3.0, 0.0, 0.0);
}
//make the arclenght table
void makearclen() {
    makeKeyFrames();
    bezierpoint[0] = keyFrame[0];// init the first bezier point
    G[0][0] = 0.0;//init firt element of arc lenght array
    G[0][1] = 0.0;
    int i = 1;
    //init the bezier points and arc len array
    for (float t = 0.0f; t <= 1.0f; t += 0.01f)
    {
        Point p2 = drawBezierGeneralized(keyFrame, t);
        cout << p2.x << ",  " << p2.y << ", " << p2.z << endl;
        cout << endl;
        bezierpoint[i] = p2;// get the bezier point
        G[i][0] = t;
        G[i][1] = G[i - 1][1] + distance(bezierpoint[i], bezierpoint[i - 1]);//get the arc length array
        i++;
    }
    //normalize the arc length array
    for (int k = 0; k < 102; k++)
    {
        G[k][1] = G[k][1] / G[101][1];
        cout << G[k][1] << endl;
    }
}
//define the init
void myInit() {

    glClearColor(.0, .0, .0, 0.0);
    glColor3f(0.0, 0.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    makearclen();

}
//drawing function
int points = 0;
void draw() {

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //first cube
    glPushMatrix();
    glTranslatef(bezierpoint[points].x, bezierpoint[points].y, bezierpoint[points].z);
    glColor3f(1, 1, 1);
    glScalef(0.8f, 1.6f, 0.4f);
    glutSolidCube(.4);
    glPopMatrix();
    //flush
    glFlush();
}
//define constant speed
void timer1(int v) {
    // Updata movement parameters
    if (points == 101)
        return;
    points++;
    glutPostRedisplay();
    glutTimerFunc(100, timer1, 0);
}
//define the varible speed
int acc = 0;
int minuss = 0;
void timer2(int v) {
    // Updata movement parameters
    if (acc <= 10) {
        points += acc;
        acc++;
    }else
        if (acc > 10 && acc < 30) {
            points++;
            acc++;
        }else
            if(acc>=30 && acc<40){
                points -= minuss;
                acc++;
                minuss++;
            }      
    glutPostRedisplay();
    glutTimerFunc(100, timer2, 0);
}
//on mouse click function
void myMouse(int button, int state, int x, int y) {
    // If left button was clicked for constant speed
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        glutTimerFunc(100, timer1, 0);
    }
    // If right button was clicked for varible speed
    if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {

        glutTimerFunc(100, timer2, 0);
    }
}
//reshaping
void reshape(int w, int h) {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(atan(tan(50.0 * 3.14159 / 360.0) / 1.0) * 360.0 / 3.141593, 1.0, 3.0, 7.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(5.0, 2.0, 5.0,
        0.0, 0.0, 0.0,
        0.0, 1.0, 0.0);
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
    glutMainLoop();

    return 0;
}