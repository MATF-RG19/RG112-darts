#include <iostream>
#include "GL/glut.h"

static void on_display();
static void on_reshape(int width, int height);
static void on_keyboard(unsigned char key, int x, int y);
static void glut_initialization(int* argc, char** argv);
static void gl_initialization();
//set_eye's arguments are the same as gluLookAt's first 6 arguments
static void set_eye(int x, int y, int z, int xl, int yl, int zl);
//sets the color of the particular primitive
static void gl_material_color(GLfloat* amb, GLfloat* diff);
//sets scene lighting
static void gl_lighting();
static GLUquadric *quad = gluNewQuadric();


//flag for switching shading technique with one button
static bool shadeFlag = true;
//initialization of vectors for diffuse and ambient material coloring
static GLfloat a[] = {1, 1, 1, 1};
static GLfloat d[] = {1, 1, 1, 1};


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

static void gl_initialization(){

	glEnable(GL_DEPTH_TEST);

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

static void gl_material_color(GLfloat* amb, GLfloat* diff){

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, amb);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diff);


}

static void on_reshape(int width, int height){

	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, (double)width / (double)height, 1, 50);

}

static void on_display(){

	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	set_eye(0, 0, 22, 0, 0, 0);
	gl_lighting();


	//middle cylinder
	glPushMatrix();
		a[0] = 1, a[1] = 1, a[2] = 1; //a[3] is already globally initialized at 1
		d[0] = 1, d[1] = 1, d[2] = 1; //d[3] is already globally initialized at 1
		gl_material_color(a, d);
		glRotatef(90, 0, 1, 0);
		gluCylinder(quad, 1, 1, 4, 40, 10);
	glPopMatrix();

	glPushMatrix();
		a[0] = 1, a[1] = 1, a[2] = 1;
		d[0] = 1, d[1] = 1, d[2] = 1;
		gl_material_color(a, d);
		glTranslated(4, 0, 0);
		glRotatef(90, 0, 1, 0);
		gluCylinder(quad, 1, .6, 3, 40, 40);
	glPopMatrix();

	glPushMatrix();
		a[0] = 1, a[1] = 1, a[2] = 1;
		d[0] = 1, d[1] = 1, d[2] = 1;
		gl_material_color(a, d);
		glTranslated(0, 0, 0);
		glRotatef(-90, 0, 1, 0);
		gluCylinder(quad, 1, .6, 3, 40, 40);
	glPopMatrix();

	glPushMatrix();
		a[0] = 1, a[1] = 1, a[2] = 1;
		d[0] = 1, d[1] = 1, d[2] = 1;
		gl_material_color(a, d);
		glTranslated(-8, 0, 0);
		glRotatef(90, 0, 1, 0);
		gluCylinder(quad, .6, .6, 5, 40, 40);
	glPopMatrix();

	glPushMatrix();
		a[0] = 1, a[1] = 1, a[2] = 1;
		d[0] = 1, d[1] = 1, d[2] = 1;
		gl_material_color(a, d);
		glTranslated(7, 0, 0);
		glRotatef(90, 0, 1, 0);
		gluCylinder(quad, .6, .3, 0.8, 40, 40);
	glPopMatrix();

	glPushMatrix();
		a[0] = 1, a[1] = 1, a[2] = 1;
		d[0] = 1, d[1] = 1, d[2] = 1;
		gl_material_color(a, d);
		glTranslated(7.8, 0, 0);
		glRotatef(90, 0, 1, 0);
		glutSolidCone(.3, 9, 30, 0);
	glPopMatrix();

	glPushMatrix();
		a[0] = 1, a[1] = 1, a[2] = 1;
		d[0] = 1, d[1] = 1, d[2] = 1;
		gl_material_color(a, d);
		glTranslated(-8, 0, 0);
		glRotatef(-90, 0, 1, 0);
		gluCylinder(quad, .6, .45, 0.8, 40, 40);
	glPopMatrix();

	glPushMatrix();
		a[0] = 1, a[1] = 1, a[2] = 1;
		d[0] = 1, d[1] = 1, d[2] = 1;
		gl_material_color(a, d);
		glTranslated(-8.8, 0, 0);
		glRotatef(-90, 0, 1, 0);
		gluCylinder(quad, .45, .45, 3.5, 40, 40);
	glPopMatrix();



	glutSwapBuffers();

}
