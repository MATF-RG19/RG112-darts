#include "GL/glut.h"
#include "cameraAndLightning.cpp"
#include "ui.h"


bool inspect_active = false;
bool throw_active = false;
bool can_throw = true;

//mouse state is used to determine if the mouse is UP or DOWN when pressed
int mouse_state = 0;
double dart_throw_vector_speed = 0;
double dart_throw_power = 2;
double dart_throw_rotation_angle = 0;

void on_timer_inspect(int value);
void on_timer_get_back(int value);
void on_timer_throw(int value);
//keeps timer running when !throw_active
void go_timer(int value);
//used to track for how long is the LMB held
void dart_power(int value);

void inspect_animation(){
	if(!inspect_active){
		glutTimerFunc(25, on_timer_inspect, 0);
		inspect_active = true;
	}
	else{
		glutTimerFunc(20, on_timer_get_back, 0);
		inspect_active = false;
	}
}

void throw_animation(){
	if(!throw_active){
		throw_active = true;
		glutTimerFunc(20, on_timer_throw, 0);
	}
}

void on_timer_throw(int value){
	if(value){
		return;
	}
	
	if(dart_throw_vector_speed <= 158){
		can_throw = false;
		dart_throw_vector_speed += dart_throw_power;
		//the expression on the right is there to modify the rotation a bit depending on the dart_throw_power
		dart_throw_rotation_angle += 18 + (dart_throw_power - 4)*2;
	}
	else{
		glutTimerFunc(20, go_timer, 0);
		throw_active = false;
		dart_throw_vector_speed = 0;
		dart_throw_power = 2;
		dart_throw_rotation_angle = 0;
		can_throw = true;
	}
	
	if(!throw_active){
		can_throw = true;
	}
	
	if(time_left > 0.02) {
		time_left -= .02;
	}
	else{
		can_throw = false;
	}
	
	glutPostRedisplay();
	
	
	if(throw_active){
		glutTimerFunc(20, on_timer_throw, 0);
	}
}

void go_timer(int value){
	if(value){
		return;
	}
	
	time_left -= .02;
	
	glutPostRedisplay();
	
	if(!throw_active){
		glutTimerFunc(20, go_timer, 0);
	}
}

void dart_power(int value){
	if(value){
		return;
	}
	
	if(dart_throw_power < 6.9) {
		dart_throw_power += 0.1;
	}
	
	glutPostRedisplay();
	
	if(mouse_state == GLUT_DOWN){
		glutTimerFunc(15, dart_power, 0);
	}
}

void on_timer_inspect(int value){
	if(value){
		return;
	}
	
	if(x > 14){
		x--;
	}
	
	if(y > 30){
		y--;
	}
	
	if(z > 43){
		z--;
	}
	//prevents movement along z axes (locks free camera)
	if(z < 43){
		z++;
	}
	
	if(zVec < 0){
		zVec += 0.01;
	}
	if(xVec > -1) {
		xVec -= 0.01;
	}
		
	glutPostRedisplay();
	
	if(inspect_active){
		glutTimerFunc(15, on_timer_inspect, 0);
	}
	
}

void on_timer_get_back(int value){
	if(value){
		return;
	}
	
	if(x < 24){
		x++;
	}
	
	if(y < 35){
		y++;
	}
	
	if(z < 84){
		z++;
	}
	//locks camera in place
	if(z > 84){
		z--;
	}
	
	if(zVec > -1){
		zVec -= 0.01;
	}
	
	if(xVec < 0){
		xVec += 0.01;
	}
	
	glutPostRedisplay();
	
	if(!inspect_active){
		glutTimerFunc(15, on_timer_get_back, 0);
	}
}