#ifndef _MODELLER_CPP_
#define _MODELLER_CPP_
#include "modeller.h"
#include <iostream>
#include "GL/glut.h"
#include <cstdlib>

void initial_colour(){
	for(int i = 0; i < 4; i++){
		colour_picker[i] = WHITE;
	}
	for(int i = 4; i < 11; i++){
		colour_picker[i] = TEAL;
	}
	colour_picker[11] = GREY;
}

void gl_material_color(int COLOUR){
	
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

void draw_dart(){
	glPushMatrix();
	//dart vector is normal to the center of the dartboard
	glTranslatef(0, 31.1, 42.7);
	glRotatef(90, 0, 1, 0);
	glScalef(0.7, 0.7, 0.7);
	draw_dart_base();
	draw_wings();
	glPopMatrix();
}

void draw_dart_base(){

	//middle cylinder
	glPushMatrix();
	gl_material_color(colour_picker[0]);
	glRotatef(90, 0, 1, 0);
	gluCylinder(quad, 1, 1, 4, 40, 10);
	glPopMatrix();
	
	//right cylinder with different bases
	glPushMatrix();
	gl_material_color(colour_picker[4]);
	glTranslated(4, 0, 0);
	glRotatef(90, 0, 1, 0);
	gluCylinder(quad, 1, .6, 3, 40, 40);
	glPopMatrix();
	
	//left cylinder with different bases
	glPushMatrix();
	gl_material_color(colour_picker[5]);
	glTranslated(0, 0, 0);
	glRotatef(-90, 0, 1, 0);
	gluCylinder(quad, 1, .6, 3, 40, 40);
	glPopMatrix();
	
	//longest cylinder
	glPushMatrix();
	gl_material_color(colour_picker[1]);
	glTranslated(-8, 0, 0);
	glRotatef(90, 0, 1, 0);
	gluCylinder(quad, .6, .6, 5, 40, 40);
	glPopMatrix();
	
	//before arrow cylinder
	glPushMatrix();
	gl_material_color(colour_picker[2]);
	glTranslated(7, 0, 0);
	glRotatef(90, 0, 1, 0);
	gluCylinder(quad, .6, .3, 0.8, 40, 40);
	glPopMatrix();
	
	//arrow
	glPushMatrix();
	gl_material_color(colour_picker[11]);
	glTranslated(7.8, 0, 0);
	glRotatef(90, 0, 1, 0);
	glutSolidCone(.3, 10, 30, 0);
	glPopMatrix();
	
	//before wings holder
	glPushMatrix();
	gl_material_color(colour_picker[6]);
	glTranslated(-8, 0, 0);
	glRotatef(-90, 0, 1, 0);
	gluCylinder(quad, .6, .45, 0.8, 40, 40);
	glPopMatrix();
	
	//wings holder
	glPushMatrix();
	gl_material_color(colour_picker[3]);
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
	gl_material_color(colour_picker[7]);
	draw_wing();
	glPopMatrix();
	
	glPushMatrix();
	glRotatef(90, 1, 0, 0);
	glTranslatef(-11.4, 0, 0);
	gl_material_color(colour_picker[8]);
	draw_wing();
	glPopMatrix();
	
	glPushMatrix();
	glRotatef(180, 1, 0, 0);
	glTranslatef(-11.4, 0, 0);
	gl_material_color(colour_picker[9]);
	draw_wing();
	glPopMatrix();
	
	glPushMatrix();
	glRotatef(-90, 1, 0, 0);
	glTranslatef(-11.4, 0, 0);
	gl_material_color(colour_picker[10]);
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
	
	glDisable(GL_LIGHTING);
	
	//down
	glPushMatrix();
	glColor3f(0, .5, .1);
	glBegin(GL_QUADS);
	glVertex3f(92, -10, 130);
	glVertex3f(92, -10, -130);
	glVertex3f(-92, -10, -130);
	glVertex3f(-92, -10, 130);
	glEnd();
	glPopMatrix();
	
	//right
	glPushMatrix();
	glColor3f(.5, .5, 0);
	glBegin(GL_QUADS);
	glVertex3f(92, -10, 130);
	glVertex3f(92, -10, -130);
	glVertex3f(92, 50, -130);
	glVertex3f(92, 50, 130);
	glEnd();
	glPopMatrix();
	
	//front
	glPushMatrix();
	glColor3f(.5, .1, 0);
	glBegin(GL_QUADS);
	glVertex3f(92, -10, -130);
	glVertex3f(-92, -10, -130);
	glVertex3f(-92, 50, -130);
	glVertex3f(92, 50, -130);
	glEnd();
	glPopMatrix();
	
	//left
	glPushMatrix();
	glColor3f(.5, .5, 0);
	glBegin(GL_QUADS);
	glVertex3f(-92, -10, -130);
	glVertex3f(-92, -10, 130);
	glVertex3f(-92, 50, 130);
	glVertex3f(-92, 50, -130);
	glEnd();
	glPopMatrix();
	
	//back
	glPushMatrix();
	glColor3f(.5, .1, 0);
	glBegin(GL_QUADS);
	glVertex3f(-92, -10, 130);
	glVertex3f(92, -10, 130);
	glVertex3f(92, 50, 130);
	glVertex3f(-92, 50, 130);
	glEnd();
	glPopMatrix();
	
	//up
	glPushMatrix();
	glColor3f(0, .5, .1);
	glBegin(GL_QUADS);
	glVertex3f(92, 50, 130);
	glVertex3f(92, 50, -130);
	glVertex3f(-92, 50, -130);
	glVertex3f(-92, 50, 130);
	glEnd();
	glPopMatrix();
	
	glEnable(GL_LIGHTING);
	
}

void draw_dartboard(){
	glPushMatrix();
	//sets the dartboard to be centered and forward
	glTranslatef(0, -10, -127.2);
	glScalef(1.4, 1.4, 1.4);
	draw_dartboard_base();
	draw_dartboard_main();
	glPopMatrix();
}

void draw_dartboard_base(){
	
	glPushMatrix();
	//lowest cuboid
	glPushMatrix();
	glScalef(1, .6, .4);
	gl_material_color(GREY);
	glutSolidCube(10);
	glPopMatrix();
	
	//lower pyramid
	glPushMatrix();
	gl_material_color(GREY);
	glBegin(GL_POLYGON);
	glVertex3f(-5, 3, 2);
	glVertex3f(5, 3, 2);
	glVertex3f(3, 6, 1);
	glVertex3f(-3, 6, 1);
	glEnd();
	
	glBegin(GL_POLYGON);
	glVertex3f(5, 3, 2);
	glVertex3f(5, 3, -2);
	glVertex3f(3, 6, -1);
	glVertex3f(3, 6, 1);
	glEnd();
	
	glBegin(GL_POLYGON);
	glVertex3f(5, 3, -2);
	glVertex3f(-5, 3, -2);
	glVertex3f(-3, 6, -1);
	glVertex3f(3, 6, -1);
	glEnd();
	
	glBegin(GL_POLYGON);
	glVertex3f(-5, 3, -2);
	glVertex3f(-5, 3, 2);
	glVertex3f(-3, 6, 1);
	glVertex3f(-3, 6, -1);
	glEnd();
	glPopMatrix();
	
	//middle cylinder
	glPushMatrix();
	gl_material_color(WHITE);
	
	glBegin(GL_POLYGON);
	glVertex3f(3, 6, 1);
	glVertex3f(3, 6, -1);
	glVertex3f(3, 21, -1);
	glVertex3f(3, 21, 1);
	glEnd();
	
	glBegin(GL_POLYGON);
	glVertex3f(3, 6, -1);
	glVertex3f(-3, 6, -1);
	glVertex3f(-3, 21, -1);
	glVertex3f(3, 21, -1);
	glEnd();
	
	glBegin(GL_POLYGON);
	glVertex3f(-3, 6, -1);
	glVertex3f(-3, 6, 1);
	glVertex3f(-3, 21, 1);
	glVertex3f(-3, 21, -1);
	glEnd();
	
	glBegin(GL_POLYGON);
	glVertex3f(-3, 6, 1);
	glVertex3f(3, 6, 1);
	glVertex3f(3, 21, 1);
	glVertex3f(-3, 21, 1);
	glEnd();
	
	glPopMatrix();
	
	//upper pyramid
	glPushMatrix();
	gl_material_color(GREY);
	
	glBegin(GL_POLYGON);
	glVertex3f(3, 21, 1);
	glVertex3f(3, 21, -1);
	glVertex3f(1.8, 23.5, -.7);
	glVertex3f(1.8, 23.5, .7);
	glEnd();
	
	glBegin(GL_POLYGON);
	glVertex3f(3, 21, -1);
	glVertex3f(-3, 21, -1);
	glVertex3f(-1.8, 23.5, -.7);
	glVertex3f(1.8, 23.5, -.7);
	glEnd();
	
	glBegin(GL_POLYGON);
	glVertex3f(-3, 21, -1);
	glVertex3f(3, 21, 1);
	glVertex3f(1.8, 23.5, .7);
	glVertex3f(-1.8, 23.5, -.7);
	glEnd();
	
	glBegin(GL_POLYGON);
	glVertex3f(-3, 21, 1);
	glVertex3f(3, 21, 1);
	glVertex3f(1.8, 23.5, .7);
	glVertex3f(-1.8, 23.5, .7);
	glEnd();
	
	glPopMatrix();
	
	glPopMatrix();
}

void draw_dartboard_main(){
	
	glPushMatrix();
	glTranslated(0, 29.8, .4);
	gl_material_color(BLACK);
	
	gluDisk(quad, 0, 6.4, 20, 7);
	glPopMatrix();

}
#endif