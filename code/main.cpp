#include <iostream>
#include <cmath>
#include "GL/glut.h"
#include "modeller.cpp"
#include "cameraAndLightning.cpp"


static void on_display();
static void on_reshape(int width, int height);
static void on_keyboard(unsigned char key, int x, int y);
static void glut_initialization(int* argc, char** argv);
static void gl_initialization();



//flag for switching shading technique with one button
static bool shadeFlag = true;



int main(int argc, char** argv){

	glut_initialization(&argc, argv);

	gl_initialization();

	exit(EXIT_SUCCESS);
}

static void glut_initialization(int* argc, char** argv){

	glutInit(argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH | GLUT_MULTISAMPLE);
	glutInitWindowPosition(200, 100);
	glutInitWindowSize(1000, 600);
	glutCreateWindow("Darts");

	glutKeyboardFunc(on_keyboard);
	glutDisplayFunc(on_display);
	glutReshapeFunc(on_reshape);

}


static void gl_initialization(){

	glEnable(GL_DEPTH_TEST);
	
	//enables MSAA
	glEnable(GL_MULTISAMPLE);
	glLineWidth(1);

	glClearColor(0, 0, 0, 0);

	glutMainLoop();

}

static void on_keyboard(unsigned char key, int x, int y){ /*TODO: restrict camera movement so it can't go out of the playground*/

	switch(key){
		case 27: exit(EXIT_SUCCESS); break;
		case 'v': case 'V':
			glShadeModel(shadeFlag? GL_SMOOTH : GL_FLAT);
			shadeFlag = !shadeFlag;
			glutPostRedisplay();
			break;
		case 'r': case 'R':
			random_colour = !random_colour;
			srand(time(NULL));
			glutPostRedisplay();
			break;
		case 'g': case 'G':
			pump_my_bitch_up = !pump_my_bitch_up;
			glutPostRedisplay();
			break;
		case 'a': case 'A':
			camAngle -= 0.05;
			xVec = sin(camAngle);
			zVec = -cos(camAngle);
			glutPostRedisplay();
			break;
		case 'd': case 'D':
			camAngle += 0.05;
			xVec = sin(camAngle);
			zVec = -cos(camAngle);
			glutPostRedisplay();
			break;
		case 'w': case 'W':
			x += xVec * camSpeed;
			z += zVec * camSpeed;
			glutPostRedisplay();
			break;
		case 's': case 'S':
			x -= xVec * camSpeed;
			z -= zVec * camSpeed;
			glutPostRedisplay();
			break;
		default: break;
	}

}


static void on_reshape(int width, int height){

	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, (double)width / (double)height, 1, 300);

}

static void on_display(){

	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	//initial position of the camera
	set_eye(x, y, z, xVec, yVec, zVec);
	gl_lighting();
	
	draw_cartesian();

	draw_dart_base();
	draw_wings();
	
	draw_planes();

	glutSwapBuffers();

}
