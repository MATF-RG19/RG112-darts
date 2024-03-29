#include "GL/glut.h"
#include "../include/ui.h"
#include <cstdio>
#include "timer.cpp"

void change_string_content(){
	sprintf(dart_num_text, "NUMBER OF DARTS: %i", dart_num);
	sprintf(score_text, "SCORE: %i", score);
	sprintf(time_left_text, "TIME LEFT: %.3lf", time_left);
	sprintf(dart_power_text, "POWER: %.1lf", dart_throw_power - 2);
	sprintf(pointer, "+");
	if(randomize) {
		sprintf(rand_text, "RANDOMIZATION: ON");
	}
	else{
		sprintf(rand_text, "RANDOMIZATION: OFF");
	}
}

void draw_string(double x, double y, char* string){
	glRasterPos2d(x, y);

	for(char* c = string; *c != '\0'; c++){
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
	}

}

void draw_ui(){
	//stops UI from being drawn when in inspect mode
	if(!inspect_active) {
		glPushMatrix();
		glDisable(GL_DEPTH_TEST);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(0, window_width, window_height, 0, 0, 157);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		glDisable(GL_LIGHTING);
		glColor3f(1, .35, .8);

		if(time_left <= 0.02){
			if(score) {
				draw_string(window_width * .548, window_height * .80, score_text);
			}
			else {
				draw_string(window_width * .497, window_height * .8, "YOU'RE TOO SLOW.. IDIOT!");
				can_throw = false;
			}
		}
		else if(dart_num <= 0){
			if(score) {
				draw_string(window_width * .548, window_height * .80, score_text);
			}
			else {
				draw_string(window_width * .527, window_height * .8, "NO MORE DARTS, MATE");
			}
		}
		else{
			change_string_content();
			draw_string(pointer_x, pointer_y, pointer);
			draw_string(window_width * .548, window_height * .80, dart_num_text);
			draw_string(window_width * .548, window_height * .85, dart_power_text);
			draw_string(window_width * .548, window_height * .90, time_left_text);
			draw_string(window_width * .548, window_height * .95, score_text);
			draw_string(window_width * .2, window_height * .87, rand_text);
		}
		glEnable(GL_LIGHTING);

		glEnable(GL_DEPTH_TEST);

		double width = glutGet(GLUT_WINDOW_WIDTH);
		double height = glutGet(GLUT_WINDOW_HEIGHT);

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(60, (double) width / (double) height, 1, 300);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		gluLookAt(x, y, z, x + xVec, y, z + zVec, 0, 1, 0);

		glPopMatrix();
	}

}

void score_tracker(double x, double y){
	//the dart-board coordinates when camera in the default position
	if(pointer_x >= .45 * window_width && pointer_x <= .565 * window_width && pointer_y >= .233 * window_height && pointer_y <= .466 * window_height) {
		score += 50;
	}
	else{
		score += 0;
	}
}