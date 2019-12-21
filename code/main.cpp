#include <iostream>
#include <cmath>
#include "GL/glut.h"
#include "timer.cpp"
#include "modeller.cpp"
#include "image.cpp"
#include <cstring>
#include <string>
#include "ui.cpp"


static void on_display();
static void on_reshape(int width, int height);
static void on_keyboard(unsigned char key, int x, int y);
static void on_mouse(int button, int state, int x, int y);
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
	glutMouseFunc(on_mouse);

}


static void gl_initialization(){

	glEnable(GL_DEPTH_TEST);
	srand(time(NULL));
	
	//defines type of transparency
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	//sets pixel storage method for UI
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	
	//enables MSAA
	glEnable(GL_MULTISAMPLE);
	//glEnable(GL_COLOR_MATERIAL); this could be used to colour objects instead of altering amb and diff light part
	glLineWidth(1);

	glClearColor(0, 0, 0, 0);
	
	init_textures();
	
	set_texture(FLOOR, 0);
	set_texture(LEFT_WALL, 1);
	set_texture(RIGHT_WALL, 2);
	set_texture(CEILING, 3);
	set_texture(FRONT, 4);
	set_texture(BACK, 5);
	set_transparent_texture(DARTBOARD, 6);
	
	unbind_texture();
	
	initial_colour();
	
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
			if(random_colour) {
				for (int i = 0; i < 12; i++) {
					colour_picker[i] = rand() % 14;
				}
			}
			else{
				initial_colour();
			}
			glutPostRedisplay();
			break;
		case 'g': case 'G':
			pump_my_bitch_up = !pump_my_bitch_up;
			if(pump_my_bitch_up) {
			for (int i = 0; i < 12; i++) {
				colour_picker[i] = GOLD;
			}
			}
			else{
				initial_colour();
			}
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
			z -= camSpeed;
			glutPostRedisplay();
			break;
		case 's': case 'S':
			z += camSpeed;
			glutPostRedisplay();
			break;
		case 'f': case 'F':
			inspect_animation();
			break;
		default: break;
	}

}

static void on_mouse(int button, int state, int x, int y){
	if(button == GLUT_LEFT_BUTTON && state == GLUT_UP && can_throw){
		if(dart_num && time_left) {
			throw_animation();
			dart_num -= 1;
		}
	}
	
	//resets the game
	if(button == GLUT_RIGHT_BUTTON && state == GLUT_UP){
		dart_num = 3;
		time_left = 12;
		score = 0;
		throw_active = false;
		can_throw = true;
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
	
	//draw_cartesian();
	
	glPushMatrix();
		glTranslatef(0, 0, -dart_throw_vector_speed);
		draw_dart();
	glPopMatrix();
	
	//draw_planes();
	
	draw_dartboard();
	
	draw_textures();
	
	draw_ui();

	glutSwapBuffers();

}
