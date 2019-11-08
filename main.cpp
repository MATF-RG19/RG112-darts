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


static void on_display();
static void on_reshape(int width, int height);
static void on_keyboard(unsigned char key, int x, int y);
static void glut_initialization(int* argc, char** argv);
static void gl_initialization();
//set_eye's arguments are the same as gluLookAt's first 6 arguments
static void set_eye(int x, int y, int z, int xl, int yl, int zl);
//sets the color of the particular primitive
static void gl_material_color(int COLOUR);
//sets scene lighting
static void gl_lighting();
static GLUquadric *quad = gluNewQuadric();
//draws cartesian coordinate system
static void draw_cartesian();
//draws one wing for the dart
static void draw_wing();
//drawsa all 4 wings of a dart
static void draw_wings();
//draws base of the dart w/out wings
static void draw_dart_base();


//flag for switching shading technique with one button
static bool shadeFlag = true;
//initialization of vectors for diffuse and ambient material coloring
static GLfloat ambient[] = {1, 1, 1, 1};
static GLfloat diffuse[] = {1, 1, 1, 1};


int main(int argc, char** argv){

	glut_initialization(&argc, argv);

	gl_initialization();


	exit(EXIT_SUCCESS);
}

static void glut_initialization(int* argc, char** argv){

	glutInit(argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowPosition(200, 100);
	glutInitWindowSize(1000, 600);
	glutCreateWindow("Darts");

	glutKeyboardFunc(on_keyboard);
	glutDisplayFunc(on_display);
	glutReshapeFunc(on_reshape);

}

static void draw_cartesian(){
	
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

static void gl_initialization(){

	glEnable(GL_DEPTH_TEST);
	glLineWidth(1);

	glClearColor(0, 0, 0, 0);

	glutMainLoop();

}

static void on_keyboard(unsigned char key, int x, int y){

	switch(key){
		case 27: exit(EXIT_SUCCESS); break;
		case 'v': case 'V':
			glShadeModel(shadeFlag? GL_SMOOTH : GL_FLAT);
			shadeFlag = !shadeFlag;
			glutPostRedisplay();
			break;
		default: break;
	}

}

static void set_eye(int x, int y, int z, int xl, int yl, int zl){

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(x, y, z, xl, yl, zl, 0, 1, 0);

}

static void gl_lighting(){

	GLfloat light1Pos[] = {10, 10, 10, 0};
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

static void gl_material_color(int COLOUR){
	
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

static void on_reshape(int width, int height){

	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, (double)width / (double)height, 1, 50);

}

static void draw_dart_base(){
	
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

static void draw_wing(){
	
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

static void draw_wings(){
	
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

static void on_display(){

	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	set_eye(0, 0, 22, 0, 0, 0);
	gl_lighting();
	
	draw_cartesian();
	
	draw_dart_base();
	draw_wings();


	glutSwapBuffers();

}
