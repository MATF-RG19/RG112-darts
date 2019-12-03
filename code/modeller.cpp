#include "modeller.h"
#include <iostream>
#include "GL/glut.h"
#include <cstdlib>


void gl_material_color(int COLOUR){
	
	if(random_colour){
		COLOUR = rand() % 14;
	}
	
	if(pump_my_bitch_up){
		COLOUR = GOLD;
	}
	
	switch(COLOUR){
		case WHITE: ambient[0] = .9, ambient[1] = .9, ambient[2] = .9;
			diffuse[0] = 1, diffuse[1] = 1, diffuse[2] = 1;
			break;
		case BLACK: ambient[0] = 0, ambient[1] = 0, ambient[2] = 0;
			diffuse[0] = 0, diffuse[1] = 0, diffuse[2] = 0;
			break;
		case RED: ambient[0] = .8, ambient[1] = 0, ambient[2] = 0;
			diffuse[0] = 1, diffuse[1] = 0, diffuse[2] = 0;
			break;
		case GREEN: ambient[0] = 0, ambient[1] = .8, ambient[2] = 0;
			diffuse[0] = 0, diffuse[1] = 1, diffuse[2] = 0;
			break;
		case BLUE: ambient[0] = 0, ambient[1] = 0, ambient[2] = .8;
			diffuse[0] = 0, diffuse[1] = 0, diffuse[2] = 1;
			break;
		case PINK: ambient[0] = .9, ambient[1] = .3, ambient[2] = .6;
			diffuse[0] = 1, diffuse[1] = .4, diffuse[2] = .7;
			break;
		case BROWN: ambient[0] = .4, ambient[1] = .2, ambient[2] = .03;
			diffuse[0] = .5, diffuse[1] = .3, diffuse[2] = .07;
			break;
		case TEAL: ambient[0] = 0, ambient[1] = .4, ambient[2] = .4;
			diffuse[0] = 0, diffuse[1] = .5, diffuse[2] = .5;
			break;
		case ORANGE: ambient[0] = .9, ambient[1] = .22, ambient[2] = 0;
			diffuse[0] = 1, diffuse[1] = .27, diffuse[2] = 0;
			break;
		case MAROON: ambient[0] = .5, ambient[1] = 0, ambient[2] = 0;
			diffuse[0] = .6, diffuse[1] = 0, diffuse[2] = 0;
			break;
		case GOLD: ambient[0] = .8, ambient[1] = .8, ambient[2] = 0;
			diffuse[0] = .9, diffuse[1] = .9, diffuse[2] = 0;
			break;
		case YELLOW: ambient[0] = .9, ambient[1] = .9, ambient[2] = 0;
			diffuse[0] = 1, diffuse[1] = 1, diffuse[2] = 0;
			break;
		case VIOLET: ambient[0] = .3, ambient[1] = 0, ambient[2] = .3;
			diffuse[0] = .4, diffuse[1] = 0, diffuse[2] = .4;
			break;
		case GREY: ambient[0] = .3, ambient[1] = .3, ambient[2] = .3;
			diffuse[0] = .4, diffuse[1] = .4, diffuse[2] = .4;
			break;
		default:	ambient[0] = .7, ambient[1] = .7, ambient[2] = .7;
			diffuse[0] = .7, diffuse[1] = .7, diffuse[2] = .7;
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
	gl_material_color(TEAL);
	glTranslated(4, 0, 0);
	glRotatef(90, 0, 1, 0);
	gluCylinder(quad, 1, .6, 3, 40, 40);
	glPopMatrix();
	
	//left cylinder with different bases
	glPushMatrix();
	gl_material_color(TEAL);
	glTranslated(0, 0, 0);
	glRotatef(-90, 0, 1, 0);
	gluCylinder(quad, 1, .6, 3, 40, 40);
	glPopMatrix();
	
	//longest cylinder
	glPushMatrix();
	gl_material_color(WHITE);
	glTranslated(-8, 0, 0);
	glRotatef(90, 0, 1, 0);
	gluCylinder(quad, .6, .6, 5, 40, 40);
	glPopMatrix();
	
	//before arrow cylinder
	glPushMatrix();
	gl_material_color(WHITE);
	glTranslated(7, 0, 0);
	glRotatef(90, 0, 1, 0);
	gluCylinder(quad, .6, .3, 0.8, 40, 40);
	glPopMatrix();
	
	//arrow
	glPushMatrix();
	gl_material_color(GREY);
	glTranslated(7.8, 0, 0);
	glRotatef(90, 0, 1, 0);
	glutSolidCone(.3, 10, 30, 0);
	glPopMatrix();
	
	//before wings holder
	glPushMatrix();
	gl_material_color(TEAL);
	glTranslated(-8, 0, 0);
	glRotatef(-90, 0, 1, 0);
	gluCylinder(quad, .6, .45, 0.8, 40, 40);
	glPopMatrix();
	
	//wings holder
	glPushMatrix();
	gl_material_color(WHITE);
	glTranslated(-8.8, 0, 0);
	glRotatef(-90, 0, 1, 0);
	gluCylinder(quad, .45, .45, 3.5, 40, 40);
	glPopMatrix();
	
	
}

void draw_wing(){
	
	//shear
	GLfloat m[16] = {
			1.0, 0.0, 0.0, 0.0,
			-1, 1.0, 0.0, 0.0,
			0.0, 0.0, 1.0, 0.0,
			0.0, 0.0, 0.0, 1.0
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
	gl_material_color(TEAL);
	draw_wing();
	glPopMatrix();
	
	glPushMatrix();
	glRotatef(90, 1, 0, 0);
	glTranslatef(-11.4, 0, 0);
	gl_material_color(TEAL);
	draw_wing();
	glPopMatrix();
	
	glPushMatrix();
	glRotatef(180, 1, 0, 0);
	glTranslatef(-11.4, 0, 0);
	gl_material_color(TEAL);
	draw_wing();
	glPopMatrix();
	
	glPushMatrix();
	glRotatef(-90, 1, 0, 0);
	glTranslatef(-11.4, 0, 0);
	gl_material_color(TEAL);
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

void draw_planes(){
	
	//down
	glPushMatrix();
	gl_material_color(MAROON);
	glBegin(GL_QUADS);
	glVertex3f(100, -10, 100);
	glVertex3f(100, -10, -100);
	glVertex3f(-100, -10, -100);
	glVertex3f(-100, -10, 100);
	glEnd();
	glPopMatrix();
	
	//right
	glPushMatrix();
	gl_material_color(YELLOW);
	glBegin(GL_QUADS);
	glVertex3f(100, -10, 100);
	glVertex3f(100, -10, -100);
	glVertex3f(100, 60, -100);
	glVertex3f(100, 60, 100);
	glEnd();
	glPopMatrix();
	
	//front
	glPushMatrix();
	gl_material_color(GREEN);
	glBegin(GL_QUADS);
	glVertex3f(100, -10, -100);
	glVertex3f(-100, -10, -100);
	glVertex3f(-100, 60, -100);
	glVertex3f(100, 60, -100);
	glEnd();
	glPopMatrix();
	
	//left
	glPushMatrix();
	gl_material_color(YELLOW);
	glBegin(GL_QUADS);
	glVertex3f(-100, -10, -100);
	glVertex3f(-100, -10, 100);
	glVertex3f(-100, 60, 100);
	glVertex3f(-100, 60, -100);
	glEnd();
	glPopMatrix();
	
	//back
	glPushMatrix();
	gl_material_color(GREEN);
	glBegin(GL_QUADS);
	glVertex3f(-100, -10, 100);
	glVertex3f(100, -10, 100);
	glVertex3f(100, 60, 100);
	glVertex3f(-100, 60, 100);
	glEnd();
	glPopMatrix();
	
	//up
	glPushMatrix();
	gl_material_color(MAROON);
	glBegin(GL_QUADS);
	glVertex3f(100, 60, 100);
	glVertex3f(100, 60, -100);
	glVertex3f(-100, 60, -100);
	glVertex3f(-100, 60, 100);
	glEnd();
	glPopMatrix();
	
}