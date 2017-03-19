#include "stdafx.h"
#include "Planeta.h"
#include "Gl\glut.h"

#include <vector>
#include "Lunas.h"

float planetSizeScale1 = 0.0006f;
const float distanceScale = 0.000001f;

Planeta::Planeta(float DistanciaSol, float TiempoOrbita, float TiempoRotacion, float Radio, GLuint Textura, bool Rings, int g){

	this->DistanciaSol = DistanciaSol;
	this->TiempoOrbita = TiempoOrbita;
	this->TiempoRotacion = TiempoRotacion;
	this->Radio = Radio;
	this->TexturaPlaneta = Textura;
	this->Rings = Rings;
	this->Grosor = g;
}


void Planeta::CalcularPosicion(float time){

	float angle = time * 3.1419f / TiempoOrbita;

	Posicion[0] = sin(angle) * DistanciaSol;
	Posicion[1] = 0;
	Posicion[2] = cos(angle) * DistanciaSol;

	Rotacion = time * 360 / TiempoRotacion;

	for (int i = 0; i < Luna.size(); i++){
		Luna[i].CalcularPosicion(time);
	}

}


void Planeta::DibujarPlaneta(void){
	glPushMatrix();

	glTranslatef(Posicion[0] * distanceScale, Posicion[1] * distanceScale, Posicion[2] * distanceScale);

	for (int i = 0; i < Luna.size(); i++){
		Luna[i].DibujarLuna();
	}

	
	glRotatef(Rotacion, 0.0f, 1.0f, 0.0f);
	glRotatef(270, 1.0f, 0.0f, 0.0f);

	glBindTexture(GL_TEXTURE_2D, TexturaPlaneta);

	GLUquadricObj* quadric = gluNewQuadric();
	gluQuadricTexture(quadric, true);
	gluQuadricNormals(quadric, GLU_SMOOTH);


	if (DistanciaSol < 0.001f){ // Si es el sol, desactiva la iluminación.
		float radiusScaled = Radio * planetSizeScale1;

		glDisable(GL_LIGHTING);
		gluSphere(quadric, radiusScaled, 30, 30);
		glEnable(GL_LIGHTING);
	}
	else
	{
		gluSphere(quadric, Radio * planetSizeScale1, 30, 30);
	}

	if (Rings) 
		switch (Grosor){
		case 1:
			drawTorus(0.02, (Radio * planetSizeScale1) - 0.26640, 16, 48);
			break;
		case 2:
			drawTorus(0.02, (Radio * planetSizeScale1) - 0.26640, 16, 48);
			drawTorus(0.02, ((Radio * planetSizeScale1) - 0.26640) + 0.15, 16, 48);
			break;
		case 3:
			drawTorus(0.02, (Radio * planetSizeScale1) - 0.26640, 16, 48);
			drawTorus(0.02, ((Radio * planetSizeScale1) - 0.26640) + 0.15, 16, 48);
			drawTorus(0.02, ((Radio * planetSizeScale1) - 0.26640) + 0.30, 16, 48);
			break;
	}

	glPopMatrix();

	
}

void Planeta::DibujarOrbita(void) {
	glBegin(GL_LINE_STRIP);

	for (float angle = 0.0f; angle < 6.283185307f; angle += 0.05f){
		glVertex3f(sin(angle) * DistanciaSol * distanceScale, 0.0f, cos(angle) * DistanciaSol * distanceScale);
	}
	glVertex3f(0.0f, 0.0f, DistanciaSol * distanceScale);

	glEnd();

	glPushMatrix();

	glTranslatef(Posicion[0] * distanceScale, Posicion[1] * distanceScale, Posicion[2] * distanceScale);

	for (int i = 0; i < Luna.size(); i++) {
		Luna[i].DibujarOrbitas();
	}
	glPopMatrix();

}

void Planeta::getPosicion(float* vec){
	vec[0] = Posicion[0] * distanceScale;
	vec[1] = Posicion[1] * distanceScale;
	vec[2] = Posicion[2] * distanceScale;
}

float Planeta::getRadio(void){
	return Radio;
}

void Planeta::addLuna(float DistanciaPlaneta, float TiempoOrbita, float TiempoRotacion, float Radio, GLuint texture){
	Luna.push_back(Lunas(DistanciaPlaneta, TiempoOrbita, TiempoRotacion, Radio, texture));
}

void Planeta::drawTorus(double r, double c, int rSeg, int cSeg) {

	glFrontFace(GL_CW);

	glBindTexture(GL_TEXTURE_2D, TexturaAnillos);

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	const double PI = 3.1415926535897932384626433832795;
	const double TAU = 2 * PI;

	for (int i = 0; i < rSeg; i++) {

		glBegin(GL_QUAD_STRIP);

		for (int j = 0; j <= cSeg; j++) {
			for (int k = 0; k <= 1; k++) {
				double s = (i + k) % rSeg + 0.5;
				double t = j % (cSeg + 1);
				double x = (c + (r + 0.06) * cos(s * TAU / rSeg)) * cos(t * TAU / cSeg);
				double y = (c + (r + 0.06)  * cos(s * TAU / rSeg)) * sin(t * TAU / cSeg);
				double z = (r)* sin(s * TAU / rSeg);
				double u = (i + k) / (float)rSeg;
				double v = t / (float)cSeg;

				glTexCoord2d(u, v);
				glNormal3f(2 * x, 2 * y, 2 * z);
				glVertex3d(2 * x, 2 * y, 2 * z);
			}
		}
		glEnd();
	}
	glFrontFace(GL_CCW);

}

void Planeta::SetTextura(GLuint textura) {
	TexturaAnillos = textura;
}
