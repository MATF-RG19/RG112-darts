#ifndef _UI_H_
#define _UI_H_

#define MAX_SIZE (1024)

//idea for UI drawing taken from RG34 project on the same GitHub repo

char dart_num_text[MAX_SIZE], score_text[MAX_SIZE],  time_left_text[MAX_SIZE], end_game_text[MAX_SIZE];
int dart_num = 3, score = 0;
double time_left = 24;

void draw_string(double x, double y, char* string);
//function exists because sprintf needed a place to live :(
void change_string_content();

#endif