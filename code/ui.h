#ifndef _UI_H_
#define _UI_H_

#define MAX_SIZE (1024)

//idea for UI drawing taken from RG34 project on the same GitHub repo

char dart_num_text[MAX_SIZE], score_text[MAX_SIZE],  time_left_text[MAX_SIZE], dart_power_text[MAX_SIZE], pointer[5];
int dart_num = 3, score = 0;
double pointer_x = 0, pointer_y = 0;
double time_left = 12;
double window_width, window_height;

void draw_string(double x, double y, char* string);
//function exists because sprintf needed a place to live :(
void change_string_content();

#endif