#include "GL/glut.h"
#include "ui.h"
#include <iostream>
#include <cstdio>

void change_string_content(){
	sprintf(dart_num_text, "NUMBER OF DARTS: %i", dart_num);
	sprintf(score_text, "SCORE: %i", score);
	sprintf(time_left_text, "TIME LEFT: %.3lf", time_left);
}

void draw_string(double x, double y, char* string){
	glRasterPos2d(x, y);
	
	for(char* c = string; *c != '\0'; c++){
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
	}
	
}

void draw_ui(){
	glPushMatrix();
		glDisable(GL_DEPTH_TEST);
		glMatrixMode (GL_PROJECTION);
		glLoadIdentity();
			glOrtho(-100, 100, -100, -100, 1, 300);
			
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
	
		glDisable(GL_LIGHTING);
		glColor3f(0, 0, 0);
		change_string_content();
		draw_string(.6, -.1, time_left_text);
		draw_string(.6, 0, dart_num_text);
		draw_string(.6, -.2, score_text);
		glEnable(GL_LIGHTING);
		
		glEnable(GL_DEPTH_TEST);
	
		double width = glutGet(GLUT_WINDOW_WIDTH);
		double height = glutGet(GLUT_WINDOW_HEIGHT);
	
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
			gluPerspective(60, (double)width / (double)height , 1, 300);
	
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
			gluLookAt(x, y, z, x + xVec, y, z + zVec, 0, 1, 0);
		
	glPopMatrix();
	
}