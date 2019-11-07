#include <iostream>
#include "GL/glut.h"

static void on_display();
static void on_reshape(int width, int height);
static void on_keyboard(unsigned char key, int x, int y);
static void glut_initialization(int* argc, char** argv);
static void gl_initialization();
//set_eye's arguments are the same as gluLookAt's first 6 arguments
static void set_eye(int x, int y, int z, int xl, int yl, int zl);
static void gl_lighting();

bool shadeFlag = true;

int main(int argc, char** argv){

	glut_initialization(&argc, argv);

	gl_initialization();


	exit(EXIT_SUCCESS);
}

static void glut_initialization(int* argc, char** argv){

	glutInit(argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowPosition(200, 100);
	glutInitWindowSize(1000, 600);
	glutCreateWindow("Darts");

	glutKeyboardFunc(on_keyboard);
	glutDisplayFunc(on_display);
	glutReshapeFunc(on_reshape);

}

static void gl_initialization(){

	glEnable(GL_DEPTH_TEST);

	glClearColor(.1, .1, .1, 0);

	glutMainLoop();

}

static void on_keyboard(unsigned char key, int x, int y){

	switch(key){
		case 27: exit(EXIT_SUCCESS); break;
		case 'v': case 'V':
			glShadeModel(shadeFlag? GL_SMOOTH : GL_FLAT);
			shadeFlag = !shadeFlag;
			glutPostRedisplay();
			break;
		default: break;
	}

}

static void set_eye(int x, int y, int z, int xl, int yl, int zl){

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(x, y, z, xl, yl, zl, 0, 1, 0);

}

static void gl_lighting(){

	GLfloat light1Pos[] = {10, 10, 10, 0};
	GLfloat light1Amb[] = {.6, .6, .6, 1};
	GLfloat light1Diff[] = {.8, .8, .8, 1};
	GLfloat light1Spe[] = {1, 1, 1, 1};

	GLfloat mat1Amb[] = {1, 1, 1, 1};
	GLfloat mat1Diff[] = {1, 1, 1, 1};
	GLfloat mat1Spe[] = {1, 1, 1, 1};

	GLfloat shininess = 20;

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light1Amb);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light1Diff);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light1Spe);

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat1Amb);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat1Diff);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat1Spe);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess);

}

static void on_reshape(int width, int height){

	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, (double)width / (double)height, 1, 50);

}

static void on_display(){

	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	set_eye(5, 5, 10, 5, 5, 1);
	gl_lighting();




	glutSwapBuffers();

}
