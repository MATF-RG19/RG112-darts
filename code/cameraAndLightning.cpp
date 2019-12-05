#include <GL/glut.h>

//the camera always stays in xy plane e.i there is only rotation and North/South movement

//set_eye's arguments are the same as gluLookAt's first 6 arguments
void set_eye(double x, double y, double z, double xVec, double yVec, double zVec);
//sets scene lighting
void gl_lighting();

//initial camera angle
double camAngle = 0;
//initial camera position
double x = 24, y = 25, z = 84;
//initial camera LookAt vectors (they define the line of sight)
double xVec = 0, yVec = 0, zVec = -127;
//camera movement speed (this is multiplied by axes vector when moving with W or S)
double camSpeed = 1;

void set_eye(double x, double y, double z, double xVec, double yVec, double zVec){
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(x, y, z, x + xVec, 0, z + zVec, 0, 1, 0);
	
}

void gl_lighting(){
	
	//sets the light source in the right upper corner of the playground
	GLfloat light1Pos[] = {129, 59, 129, 0};
	GLfloat light1Amb[] = {.6, .6, .6, 1};
	GLfloat light1Diff[] = {.8, .8, .8, 1};
	GLfloat light1Spe[] = {1, 1, 1, 1};
	
	GLfloat spec[] = {1, 1, 1, 1};
	GLfloat shininess = 20;
	
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glLightfv(GL_LIGHT0, GL_POSITION, light1Pos);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light1Amb);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light1Diff);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light1Spe);
	
	
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, spec);
	
}