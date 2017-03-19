#include "stdafx.h"
#include "GL\glut.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "Planeta.h"
#include "Texturas.h"
#include "Sistemas.h"
#include "Camara.h"

char title[] = "Sistema Solar";


//Variables para Traslación

double time;
double timeSpeed;
int screenWidth, screenHeight;

Sistemas SistemaSolar;
Camara camera;
Texturas* Stars;
using namespace std;

void DibujarCubo(void);

struct ControlStates{
	bool forward, backward, left, right, yawLeft, yawRight, pitchUp,
		pitchDown, rollLeft, rollRight;
} controls;

void timer(int) {
	glutPostRedisplay(); 
	glutTimerFunc(10, timer, 0); 
}

void initGL() {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); 
	glClearDepth(1.0f);                  
	glEnable(GL_DEPTH_TEST);  
	glEnable(GL_TEXTURE_2D);
	glDepthFunc(GL_LEQUAL);    
	glShadeModel(GL_SMOOTH);   

	glMatrixMode(GL_MODELVIEW);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);  

	glOrtho(-501.0, 501.0, -501.0, 501.0, 501.0, -501.0);
	GLUquadricObj *qobj;
	GLfloat mat_ambient[] = { 0.5, 0.5, 0.5, 1.0 };
	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat mat_shininess[] = { 50.0 };
	GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };
	GLfloat model_ambient[] = { 0.5, 0.5, 0.5, 1.0 };


	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, model_ambient);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);


	Texturas* Tierra = new Texturas("Texturas/txEarth.bmp");
	Texturas* Mercurio = new Texturas("Texturas/txMercurio.bmp");
	Texturas* Jupiter = new Texturas("Texturas/txJupiter.bmp");
	Texturas* Venus = new Texturas("Texturas/txVenus.bmp");
	Texturas* Anillos = new Texturas("Texturas/txAnillos.bmp");
	Texturas* Marte = new Texturas("Texturas/txMarte.bmp");
	Texturas* Sol = new Texturas("Texturas/txSol.bmp");
	Texturas* Saturno = new Texturas("Texturas/txSaturno.bmp");
	Texturas* Urano = new Texturas("Texturas/txUrano.bmp");
	Texturas* Neptuno = new Texturas("Texturas/txNeptuno.bmp");
	Texturas* Luna = new Texturas("Texturas/txLuna.bmp");

	Stars = new Texturas("Texturas/txStars.bmp");

	//					DisSol/TiOrb/TiRot/Radio/Textura/Anillos

	SistemaSolar.AddPlanet(0, 2, 500, 80000, Sol->getTextura(), false, 0);             //Sol
	SistemaSolar.AddPlanet(57910000, 88, 58.6, 2440, Mercurio->getTextura(),false,0);	//Mercurio
	SistemaSolar.AddPlanet(108200000, 224.65, 243, 6052, Venus->getTextura(),false,0);	//Venus
	SistemaSolar.AddPlanet(149600000, 365, 1, 6371, Tierra->getTextura(), false, 0);	//Tierra
	SistemaSolar.AddPlanet(227939100, 686, 1.03f, 3389, Marte->getTextura(), false, 0);	//Marte
	SistemaSolar.AddPlanet(778500000, 4332, 0.4139, 69911, Jupiter->getTextura(), true, 1); //Jupiter
	SistemaSolar.AddPlanet(1433000000, 10759, 0.44375, 58232, Saturno->getTextura(), true, 3); //Saturno
	SistemaSolar.AddPlanet(2877000000, 30685, 0.718056, 25362, Urano->getTextura(), true, 3); //Urano
	SistemaSolar.AddPlanet(4503000000, 60188, 0.6713, 24622, Neptuno->getTextura(), true, 3); //Neptuno

	SistemaSolar.SetTexturaAnillos(5, Anillos->getTextura());
	SistemaSolar.SetTexturaAnillos(6, Anillos->getTextura());
	SistemaSolar.SetTexturaAnillos(7, Anillos->getTextura());
	SistemaSolar.SetTexturaAnillos(8, Anillos->getTextura());

	SistemaSolar.addLuna(3, 7000000, 27.3, 27.3, 1738, Luna->getTextura());

																 // reset controls
	controls.forward = false;
	controls.backward = false;
	controls.left = false;
	controls.right = false;
	controls.rollRight = false;
	controls.rollLeft = false;
	controls.pitchDown = false;
	controls.pitchUp = false;
	controls.yawLeft = false;
	controls.yawRight = false;


	time = 2.552f;
	timeSpeed = 0.1f;
	timer(0);
}

void display() {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
	glMatrixMode(GL_MODELVIEW);     
	glLoadIdentity();
	
	time += timeSpeed;
	SistemaSolar.CalcularPosicion(time);

	if (controls.forward) camera.forward();		if (controls.backward) camera.backward();
	if (controls.left) camera.left();			if (controls.right) camera.right();
	if (controls.yawLeft) camera.yawLeft();		if (controls.yawRight) camera.yawRight();
	if (controls.rollLeft) camera.rollLeft();	if (controls.rollRight) camera.rollRight();
	if (controls.pitchUp) camera.pitchUp();		if (controls.pitchDown) camera.pitchDown();

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(70.0f, (float)screenWidth / (float)screenHeight, 1.0f, 10000.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	camera.transformOrientation();

	/*glBindTexture(GL_TEXTURE_2D, Stars->getTextura());
	DibujarCubo();*/

	camera.transformTranslation();

	glEnable(GL_LIGHTING);

	SistemaSolar.DibujarPlanetas();
	glDisable(GL_LIGHTING);

	SistemaSolar.DibujarOrbitas();

	glFlush();
	glutSwapBuffers();
}

void keyDown(unsigned char key, int x, int y){
	switch (key)
	{
	case '-':
		timeSpeed /= 2.0f; // half the rate of time passing
		break;
	case '=':
		timeSpeed *= 2.0f; // double the rate of time passing
		break;
	case ',':
		camera.slowDown(); // slow down camera
		break;
	case '.':
		camera.speedUp(); // speed up camera
		break;
		// these are all camera controls
	case 'w':
		controls.forward = true;
		break;
	case 's':
		controls.backward = true;
		break;
	case 'a':
		controls.left = true;
		break;
	case 'd':
		controls.right = true;
		break;
	case 'l':
		controls.rollRight = true;
		break;
	case 'j':
		controls.rollLeft = true;
		break;
	case 'i':
		controls.pitchDown = true;
		break;
	case 'k':
		controls.pitchUp = true;
		break;
	case 'q':
		controls.yawLeft = true;
		break;
	case 'e':
		controls.yawRight = true;
		break;
	}

}

void keyUp(unsigned char key, int x, int y){
	switch (key)
	{
	case 'w':
		controls.forward = false;
		break;
	case 's':
		controls.backward = false;
		break;
	case 'a':
		controls.left = false;
		break;
	case 'd':
		controls.right = false;
		break;
	case 'l':
		controls.rollRight = false;
		break;
	case 'j':
		controls.rollLeft = false;
		break;
	case 'i':
		controls.pitchDown = false;
		break;
	case 'k':
		controls.pitchUp = false;
		break;
	case 'q':
		controls.yawLeft = false;
		break;
	case 'e':
		controls.yawRight = false;
		break;
	}
}

void reshape(GLsizei width, GLsizei height) {

	screenWidth = width;
	screenHeight = height;
	glViewport(0, 0, (GLsizei)width, (GLsizei)height);
	glutTimerFunc(0, 0, 0);
}



/* Main function: GLUT runs as a console application starting at main() */
int main(int argc, char** argv){
	glutInit(&argc, argv);           
	glutInitDisplayMode(GLUT_DOUBLE); 
	glutInitWindowSize(1024, 720);   
	glutInitWindowPosition(50, 50); 
	glutCreateWindow(title);          
	glutDisplayFunc(display);       
	initGL();
	glutReshapeFunc(reshape);   
	glutKeyboardFunc(keyDown);
	glutKeyboardUpFunc(keyUp);
	glutMainLoop();                 
	return 0;
}

void DibujarCubo(void){
	glBegin(GL_QUADS);
	// new face
	glTexCoord2f(0.0f, 0.0f);	glVertex3f(-500.0f, -500.0f, 500.0f);
	glTexCoord2f(1.0f, 0.0f);	glVertex3f(500.0f, -500.0f, 500.0f);
	glTexCoord2f(1.0f, 1.0f);	glVertex3f(500.0f, 500.0f, 500.0f);
	glTexCoord2f(0.0f, 1.0f);	glVertex3f(-500.0f, 500.0f, 500.0f);
	// new face
	glTexCoord2f(0.0f, 0.0f);	glVertex3f(500.0f, 500.0f, 500.0f);
	glTexCoord2f(1.0f, 0.0f);	glVertex3f(500.0f, 500.0f, -500.0f);
	glTexCoord2f(1.0f, 1.0f);	glVertex3f(500.0f, -500.0f, -500.0f);
	glTexCoord2f(0.0f, 1.0f);	glVertex3f(500.0f, -500.0f, 500.0f);
	// new face
	glTexCoord2f(0.0f, 0.0f);	glVertex3f(500.0f, 500.0f, -500.0f);
	glTexCoord2f(1.0f, 0.0f);	glVertex3f(-500.0f, 500.0f, -500.0f);
	glTexCoord2f(1.0f, 1.0f);	glVertex3f(-500.0f, -500.0f, -500.0f);
	glTexCoord2f(0.0f, 1.0f);	glVertex3f(500.0f, -500.0f, -500.0f);
	// new face
	glTexCoord2f(0.0f, 0.0f);	glVertex3f(-500.0f, -500.0f, -500.0f);
	glTexCoord2f(1.0f, 0.0f);	glVertex3f(-500.0f, -500.0f, 500.0f);
	glTexCoord2f(1.0f, 1.0f);	glVertex3f(-500.0f, 500.0f, 500.0f);
	glTexCoord2f(0.0f, 1.0f);	glVertex3f(-500.0f, 500.0f, -500.0f);
	// new face
	glTexCoord2f(0.0f, 0.0f);	glVertex3f(-500.0f, 500.0f, -500.0f);
	glTexCoord2f(1.0f, 0.0f);	glVertex3f(500.0f, 500.0f, -500.0f);
	glTexCoord2f(1.0f, 1.0f);	glVertex3f(500.0f, 500.0f, 500.0f);
	glTexCoord2f(0.0f, 1.0f);	glVertex3f(-500.0f, 500.0f, 500.0f);
	// new face
	glTexCoord2f(0.0f, 0.0f);	glVertex3f(-500.0f, -500.0f, -500.0f);
	glTexCoord2f(1.0f, 0.0f);	glVertex3f(500.0f, -500.0f, -500.0f);
	glTexCoord2f(1.0f, 1.0f);	glVertex3f(500.0f, -500.0f, 500.0f);
	glTexCoord2f(0.0f, 1.0f);	glVertex3f(-500.0f, -500.0f, 500.0f);

	glEnd();
}