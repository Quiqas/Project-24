#pragma once
#include "stdafx.h"
#include <GL\glut.h>
#include <vector>
#include <vector>
#include "Lunas.h"


class Planeta{

private:
	float DistanciaSol;

	// Tiempo que le toma completar una orbita.
	float TiempoOrbita;

	// Tiempo que le toma rotar.
	float TiempoRotacion;

	// Radio del Planeta.
	float Radio;

	// Textura del Planeta.
	GLuint TexturaPlaneta;

	GLuint TexturaAnillos;

	// Posicion en 3D.
	float Posicion[3];

	// Velocidad de Rotacion.
	float Rotacion;

	std::vector<Lunas> Luna;

	bool Rings;

	int Grosor;

public:
	// Distancia en km (kilometros) y tiempo medido en dias terrestres (365.25)
	Planeta(float DistanciaSol, float TiempoOrbita, float TiempoRotacion, float Radio, GLuint Textura, bool Rings, int g);

	// Calcula la posicion del planeta en el ambiente 3D usando un tiempo dado.
	void CalcularPosicion(float time);

	// Dibuja el planeta en la pantalla
	void DibujarPlaneta(void);

	// Dibuja las orbitas
	void DibujarOrbita(void);

	// Obtiene la posicion
	void getPosicion(float* vec);

	// Obtiene el radio
	float getRadio(void);

	void addLuna(float DistanciaPlaneta, float TiempoOrbita, float TiempoRotacion, float Radios, GLuint texture);

	void drawTorus(double, double, int, int);

	void SetTextura(GLuint);

};

