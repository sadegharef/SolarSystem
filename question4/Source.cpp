#include<gl/glut.h>
#include <cmath>

// Rotation angles
static GLfloat sun_theta = 0;
static GLfloat earth_theta = 0;
static GLfloat earth_theta_2 = 0;
static GLfloat moon_theta = 0;
static GLfloat moon_theta_2 = 0;
static GLfloat moon_theta_3 = 0;
static GLfloat p2_theta = 0;
static GLfloat p2_theta_2 = 0;

void init() {
	glClearColor(0, 0, 0, 0);
	glShadeModel(GL_FLAT);

	GLfloat light0_position[] = { -1.0, 1.0, 1.0, 0 }; // Light_0 position
	glLightfv(GL_LIGHT0, GL_POSITION, light0_position); // Define Light_0 

	glEnable(GL_LIGHTING); // Enable Lighting
	glEnable(GL_LIGHT0); // Enable Light_0
	glEnable(GL_DEPTH_TEST); // Enable Depth
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Sun
	glPushMatrix();
	glRotatef(sun_theta, 0, 1, 0); // Rotation around itself, around y axis
	//glutWireSphere(5, 20, 16);
	glutSolidSphere(5, 20, 16); // Define Sphere, r=5
	glPopMatrix();

	// Earth
	glPushMatrix();
	glRotatef(earth_theta_2, 0, 1, 0); // Rotation around the sun, around y axis
	glTranslated(12, 0, 0); // Move away from sun
	glRotatef(earth_theta, 0, 1, 0); // Roatation around itself, around y axis
	//glutWireSphere(3, 20, 16);
	glutSolidSphere(3, 20, 16); // Define Sphere, r=3
	glPopMatrix();

	// Moon
	glPushMatrix();
	glRotatef(moon_theta_3, 0, 1, 0); // Roatation around sun (with earth), around y axis
	glTranslated(12, 0, 0); // Move near earth
	glRotatef(moon_theta_2, 1, 0, 0); // Roatation around earth, around z axis
	glTranslated(0, 5, 0); // Move away from sun
	glRotatef(moon_theta, 1, 0, 0); // Rotation around itself, around x axis
	//glutWireSphere(1, 20, 16);
	glutSolidSphere(0.5, 20, 16); // Define Sphere, r=0.5
	glPopMatrix();

	// Planet 2
	glPushMatrix();
	//glRotatef(earth_theta_2, 0, 1, 0); // Rotation around the sun, around y axis
	glTranslatef(8 * cos(p2_theta_2), 0, 6 * sin(p2_theta_2)); // Rotation in oval path, it's cordinates of object in each time update.
	//glTranslated(5, 0, 0); // Move away from sun
	glRotatef(p2_theta, 0, 1, 0); // Roatation around itself, around y axis
	//glutWireSphere(3, 20, 16);
	glutSolidSphere(1, 20, 16); // Define Sphere, r=1
	glPopMatrix();

	glutSwapBuffers();
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

void timer(int v) {
	// Updata movement parameters
	sun_theta += 1;
	earth_theta += 3;
	earth_theta_2 += 1;
	moon_theta += 1;
	moon_theta_2 += 3;
	moon_theta_3 += 1;
	p2_theta += 3;
	p2_theta_2 += 0.3;

	glutPostRedisplay();
	glutTimerFunc(100, timer, 0);
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("SolarSystem");
	init();
	glutDisplayFunc(display); // Scene
	glutReshapeFunc(reshape); // Projection
	glutTimerFunc(100, timer, 0); // Timer, call each 100 ms
	glutMainLoop();
	return 0;
}