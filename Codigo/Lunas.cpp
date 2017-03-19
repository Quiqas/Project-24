#include "stdafx.h"
#include "Lunas.h"
#include <cmath>
#include "GL\glut.h"
#include "Variable.h"



Lunas::Lunas(float DistanciaPlaneta, float TiempoOrbita, float TiempoRotacion, float Radio, GLuint texture){
	this->DistanciaPlaneta = DistanciaPlaneta;
	this->TiempoOrbita = TiempoOrbita;
	this->TiempoRotacion = TiempoRotacion;
	this->Radio = Radio;
	this->Textura = texture;
}

void Lunas::CalcularPosicion(float time){

	float angle = time * 3.1419f / TiempoOrbita;

	Posicion[0] = sin(angle) * DistanciaPlaneta;
	Posicion[2] = cos(angle) * DistanciaPlaneta;
	Posicion[1] = (cos(angle) * DistanciaPlaneta)/2;

	Rotacion = time * 360 / TiempoRotacion;
}

void Lunas::DibujarLuna(void){
	glPushMatrix();

	glBindTexture(GL_TEXTURE_2D, Textura);

	glTranslatef(Posicion[0] * distanceScale, Posicion[1] * distanceScale, Posicion[2] * distanceScale);
	glRotatef(-Rotacion, 0.0f, 0.0f, 1.0f);

	GLUquadricObj* quadric = gluNewQuadric();
	gluQuadricTexture(quadric, true);
	gluQuadricNormals(quadric, GLU_SMOOTH);

	gluSphere(quadric, Radio * planetSizeScale, 30, 30);

	glPopMatrix();
}

void Lunas::DibujarOrbitas(void){

	glBegin(GL_LINE_STRIP);

	for (float angle = 0.0f; angle < 6.283185307f; angle += 0.1f){
		glVertex3f(sin(angle) * DistanciaPlaneta * distanceScale, (cos(angle) * DistanciaPlaneta * distanceScale)/2, cos(angle) * DistanciaPlaneta * distanceScale);
	}
	glVertex3f(0.0f, 0.0f, DistanciaPlaneta * distanceScale);

	glEnd();
}