#pragma once
#include <GL\glut.h>

class Lunas
{
private:
	float DistanciaPlaneta;

	float TiempoOrbita;

	float TiempoRotacion;

	float Radio;

	GLuint Textura;

	float Posicion[3];

	float Rotacion;

public:

	Lunas(float DistanciaPlaneta, float TiempoOrbita, float TiempoRotacion, float Radio, GLuint texture);

	void CalcularPosicion(float time);

	void DibujarLuna(void);

	void DibujarOrbitas(void);
};

