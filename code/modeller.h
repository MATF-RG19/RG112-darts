#ifndef _MODELLER_H_
#define _MODELLER_H_
#include <vector>

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
#define VIOLET 12
#define GREY 13
#define HOTPINK 14
#define PINE 15
#define DARK_BLUE 16
#define DARK_RED 17
#define TIGER 18

//initialization of vectors for diffuse and ambient material coloring
GLfloat ambient[] = {1, 1, 1, 1};
GLfloat diffuse[] = {1, 1, 1, 1};
//initializing quad for cylinder
GLUquadric *quad = gluNewQuadric();
//signals if pseudo-random colour picker for dart has been enabled
bool random_colour = false;
//makes dart golden
bool pump_my_bitch_up = false;
//vector used to store rand values that determine the colour of the dart
std::vector<int> colour_picker(12);


//sets the initial colour for dart
void initial_colour();
//draws cartesian coordinate system
void draw_cartesian();
//calls 1st and 2nd function under this one
void draw_dart();
//draws one wing for the dart
void draw_wing();
//draws all 4 wings of a dart
void draw_wings();
//draws base of the dart w/out wings
void draw_dart_base();
//sets the color of the particular primitive
void gl_material_color(int COLOUR);
//draws a plane
void draw_planes();
//calls 1st and 2nd function under this one
void draw_dartboard();
//draws dartboard base()
void draw_dartboard_base();
//draws dartboard main round part
void draw_dartboard_main();

#endif