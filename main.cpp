#ifdef _WIN32
#include <Windows.h>
#endif

#include <GL/glut.h>
#include "car.h"
#include "scene.h"
#include"menu.h"

// Set up variables
bool stop = true;
double time = 0;
float startTime = 40; // Time for displaying starting screen
float timeLoop = 27; // Time counter for changing the camera position
int rLoops, yLoops;	 // car loops
float carLoc1[3], carLoc2[3]; // car position

// Set up clases
Scene background;
Menu menu(startTime, timeLoop);
Car car1(1), car2(2);

GLint screenWidth = 400, screenHeight = 300;


void timer(int v) {
		glutPostRedisplay();
		glutTimerFunc(700 / 60, timer, v);
	time += 0.1;
}

void init() {

	// Set up lighting
	glClearColor(0.0, 0.0, 0.0, 0.0);
	GLfloat white[] = { 0.9, 0.9, 0.70, 1.0 };
	GLfloat direction[] = { 1.0, 1.0, 1.0, 0.0 };

	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, white);
	glMaterialf(GL_FRONT, GL_SHININESS, 20);

	glLightfv(GL_LIGHT0, GL_AMBIENT_AND_DIFFUSE, white); 
	glLightfv(GL_LIGHT0, GL_POSITION, direction); 

	glShadeModel(GL_SMOOTH);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_COLOR_MATERIAL);

	// Get vertex of background and cars
	car1.calculateVertex();
	car2.calculateVertex();
	background.calculateVertex();
	timer(0);
}


void display() {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3f(1.0, 1.0, 1.0);

	// Update positions and number of loops 
	if (stop == false) {
		car1.calculatePosition();
		car2.calculatePosition();
	}
	car1.getPosition(carLoc1);
	car2.getPosition(carLoc2);
	car1.getLoops(&rLoops);
	car2.getLoops(&yLoops);

	// Set up views
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, (float)screenWidth / (float)screenHeight, 0.001f, 50.0f);
	menu.cameraSettings(time, carLoc1, carLoc2);

	//Render cars and background
	glEnable(GL_DEPTH_TEST);
	if (time >= startTime) {
		background.render();
		car1.render();
		car2.render();
	}
	menu.counter(time, rLoops, yLoops, &stop);
	glDisable(GL_DEPTH_TEST);

	glFlush();
	glutSwapBuffers();
}

void reshape(GLint w, GLint h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, GLfloat(w) / GLfloat(h), 0.01, 50.0);
	glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowPosition(80, 80);
	glutInitWindowSize(700, 500);
	glutCreateWindow("Scalextric Race ");
	glutDisplayFunc(display);
	init();
	glutMainLoop();
}
