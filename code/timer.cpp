#include "GL/glut.h"
#include "cameraAndLightning.cpp"
#include "modeller.h"


bool inspect_active = false;
bool throw_active = true;
int dart_throw_value = 0;

void on_timer_inspect(int value);
void on_timer_get_back(int value);
void on_timer_throw(int value);

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
		glutTimerFunc(25, on_timer_throw, 0);
		throw_active = true;
	}
	else{
		dart_throw_value = 0;
		throw_active  = false;
	}
}

void on_timer_throw(int value){
	if(value){
		return;
	}
	
	
	if(dart_throw_value < 127) {
		dart_throw_value++;
	}
	
	glutPostRedisplay();
	
	if(throw_active){
		glutTimerFunc(10, on_timer_throw, 0);
	}
}

void on_timer_inspect(int value){
	if(value){
		return;
	}
	
	if(x > 14){
		x--;
	}
	
	if(y > 20){
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
	
	if(y < 25){
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