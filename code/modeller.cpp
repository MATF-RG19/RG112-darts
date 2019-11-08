#include <iostream>
#include "GL/glut.h"


//defines for colors used in gl_material_color function
#define BLACK 0
#define WHITE 1
#define RED 2
#define GREEN 3
#define BLUE 4
#define YELLOW 5
#define ORANGE 6
#define BROWN 7
#define PINK 8
#define TEAL 9
#define MAROON 10
#define GOLD 11

//initialization of vectors for diffuse and ambient material coloring
GLfloat ambient[] = {1, 1, 1, 1};
GLfloat diffuse[] = {1, 1, 1, 1};
//initializing quad for cylinder
GLUquadric *quad = gluNewQuadric();

//draws cartesian coordinate system
void draw_cartesian();
//draws one wing for the dart
void draw_wing();
//drawsa all 4 wings of a dart
void draw_wings();
//draws base of the dart w/out wings
void draw_dart_base();
//sets the color of the particular primitive
void gl_material_color(int COLOUR);

void gl_material_color(int COLOUR){
	
	switch(COLOUR){
		case WHITE: ambient[0] = 1, ambient[1] = 1, ambient[2] = 1;
			diffuse[0] = 1, diffuse[1] = 1, diffuse[2] = 1;
			break;
		case BLACK: ambient[0] = 0, ambient[1] = 0, ambient[2] = 0;
			diffuse[0] = 0, diffuse[1] = 0, diffuse[2] = 0;
			break;
		case RED: ambient[0] = 1, ambient[1] = 0, ambient[2] = 0;
			diffuse[0] = 1, diffuse[1] = 0, diffuse[2] = 0;
			break;
		case GREEN: ambient[0] = 0, ambient[1] = 1, ambient[2] = 0;
			diffuse[0] = 0, diffuse[1] = 1, diffuse[2] = 0;
			break;
		case BLUE: ambient[0] = 0, ambient[1] = 0, ambient[2] = 1;
			diffuse[0] = 0, diffuse[1] = 0, diffuse[2] = 1;
			break;
		case PINK: ambient[0] = 1, ambient[1] = .4, ambient[2] = .7;
			diffuse[0] = 1, diffuse[1] = .4, diffuse[2] = .7;
			break;
		case BROWN: ambient[0] = .5, ambient[1] = .3, ambient[2] = .07;
			diffuse[0] = .5, diffuse[1] = .3, diffuse[2] = .07;
			break;
		case TEAL: ambient[0] = 0, ambient[1] = 0, ambient[2] = 0;
			diffuse[0] = 0, diffuse[1] = 0, diffuse[2] = 0;
			break;
		case ORANGE: ambient[0] = 1, ambient[1] = .27, ambient[2] = 0;
			diffuse[0] = 1, diffuse[1] = .27, diffuse[2] = 0;
			break;
		case MAROON: ambient[0] = .6, ambient[1] = 0, ambient[2] = 0;
			diffuse[0] = .6, diffuse[1] = 0, diffuse[2] = 0;
			break;
		case GOLD: ambient[0] = 1, ambient[1] = 1, ambient[2] = 0;
			diffuse[0] = .9, diffuse[1] = .9, diffuse[2] = 0;
			break;
		case YELLOW: ambient[0] = 1, ambient[1] = 1, ambient[2] = 0;
			diffuse[0] = 1, diffuse[1] = 1, diffuse[2] = 0;
			break;
		default:	ambient[0] = 1, ambient[1] = 1, ambient[2] = 1;
			diffuse[0] = 1, diffuse[1] = 1, diffuse[2] = 1;
			break;
	}
	
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);
	
	
}

void draw_dart_base(){
	
	//middle cylinder
	glPushMatrix();
	gl_material_color(WHITE);
	glRotatef(90, 0, 1, 0);
	gluCylinder(quad, 1, 1, 4, 40, 10);
	glPopMatrix();
	
	//right cylinder with different bases
	glPushMatrix();
	gl_material_color(RED);
	glTranslated(4, 0, 0);
	glRotatef(90, 0, 1, 0);
	gluCylinder(quad, 1, .6, 3, 40, 40);
	glPopMatrix();
	
	//right cylinder with different bases
	glPushMatrix();
	gl_material_color(ORANGE);
	glTranslated(0, 0, 0);
	glRotatef(-90, 0, 1, 0);
	gluCylinder(quad, 1, .6, 3, 40, 40);
	glPopMatrix();
	
	//longest cylinder
	glPushMatrix();
	gl_material_color(GREEN);
	glTranslated(-8, 0, 0);
	glRotatef(90, 0, 1, 0);
	gluCylinder(quad, .6, .6, 5, 40, 40);
	glPopMatrix();
	
	//beffore arrow cylinder
	glPushMatrix();
	gl_material_color(BLACK);
	glTranslated(7, 0, 0);
	glRotatef(90, 0, 1, 0);
	gluCylinder(quad, .6, .3, 0.8, 40, 40);
	glPopMatrix();
	
	//arrow
	glPushMatrix();
	gl_material_color(GOLD);
	glTranslated(7.8, 0, 0);
	glRotatef(90, 0, 1, 0);
	glutSolidCone(.3, 10, 30, 0);
	glPopMatrix();
	
	//before wings holder
	glPushMatrix();
	gl_material_color(WHITE);
	glTranslated(-8, 0, 0);
	glRotatef(-90, 0, 1, 0);
	gluCylinder(quad, .6, .45, 0.8, 40, 40);
	glPopMatrix();
	
	//wings holder
	glPushMatrix();
	gl_material_color(RED);
	glTranslated(-8.8, 0, 0);
	glRotatef(-90, 0, 1, 0);
	gluCylinder(quad, .45, .45, 3.5, 40, 40);
	glPopMatrix();
}

void draw_wing(){
	
	//shear
	GLfloat m[16] = {
			1.0f, 0.0f, 0.0f, 0.0f,
			-1, 1.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
	};
	glMultMatrixf(m);
	
	glBegin(GL_POLYGON);
	glVertex3f(0, 0, 0);
	glVertex3f(3.5, 0, 0);
	glVertex3f(3.5, 0, .1);
	glVertex3f(0, 0, .1);
	glEnd();
	
	glBegin(GL_POLYGON);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 3.5, 0);
	glVertex3f(0, 3.5, .1);
	glVertex3f(0, 0, .1);
	glEnd();
	
	glBegin(GL_POLYGON);
	glVertex3f(0, 0, 0);
	glVertex3f(3.5, 0, 0);
	glVertex3f(3.5, 3.5, 0);
	glVertex3f(0, 3.5, 0);
	glEnd();
	
	glBegin(GL_POLYGON);
	glVertex3f(3.5, 0, 0);
	glVertex3f(3.5, 0, .1);
	glVertex3f(3.5, 3.5, 0);
	glVertex3f(3.5, 3.5, .1);
	glEnd();
	
	glBegin(GL_POLYGON);
	glVertex3f(3.5, 0, .1);
	glVertex3f(0, 0, .1);
	glVertex3f(0, 3.5, .1);
	glVertex3f(3.5, 3.5, .1);
	glEnd();
	
	glBegin(GL_POLYGON);
	glVertex3f(0, 3.5, 0);
	glVertex3f(3.5, 3.5, 0);
	glVertex3f(3.5, 3.5, .1);
	glVertex3f(0, 3.5, .1);
	glEnd();
	
}

void draw_wings(){
	
	glPushMatrix();
	glTranslatef(-11.4, 0, 0);
	gl_material_color(WHITE);
	draw_wing();
	glPopMatrix();
	
	glPushMatrix();
	glRotatef(90, 1, 0, 0);
	glTranslatef(-11.4, 0, 0);
	gl_material_color(WHITE);
	draw_wing();
	glPopMatrix();
	
	glPushMatrix();
	glRotatef(180, 1, 0, 0);
	glTranslatef(-11.4, 0, 0);
	gl_material_color(WHITE);
	draw_wing();
	glPopMatrix();
	
	glPushMatrix();
	glRotatef(-90, 1, 0, 0);
	glTranslatef(-11.4, 0, 0);
	gl_material_color(WHITE);
	draw_wing();
	glPopMatrix();
	
}

void draw_cartesian(){
	
	glDisable(GL_LIGHTING);
	
	glColor3f(1, 0, 0);
	glBegin(GL_LINES);
	glVertex3f(0, 0, 0);
	glVertex3f(100, 0, 0);
	glEnd();
	
	glColor3f(0, 1, 0);
	glBegin(GL_LINES);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 100, 0);
	glEnd();
	
	glColor3f(0, 0, 1);
	glBegin(GL_LINES);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, 100);
	glEnd();
	
	glEnable(GL_LIGHTING);
	
}