#ifndef _UI_H_
#define _UI_H_

#define MAX_SIZE (1024)

//idea for UI drawing taken from RG34 project on the same GitHub repo

char dart_num_text[MAX_SIZE], score_text[MAX_SIZE],  time_left_text[MAX_SIZE], dart_power_text[MAX_SIZE], pointer[2], rand_text[MAX_SIZE];
int dart_num = 3, score = 0;
double pointer_x = 0, pointer_y = 0;
double time_left = 12;
//the last two are used for optimization (cutting down on excess calculations)
double window_width, window_height, window_width_half, window_height_half;

void draw_string(double x, double y, char* string);
//function exists because sprintf needed a place to live :(
void change_string_content();
//used to track where the dart hit on the dart-board
void score_tracker(double x, double y);

#endif