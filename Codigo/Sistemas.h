#pragma once
#include "GL\glut.h"
#include <vector>
#include "Planeta.h"

class Sistemas
{
private:
	std::vector<Planeta> planets;

public:
	Sistemas();

	void CalcularPosicion(float time);

	void AddPlanet(float distanceFromSun, float orbitTime, float rotationTime, float radius, GLuint textureHandle, bool Rings, int g);

	void DibujarPlanetas();

	void DibujarOrbitas();

	void getPosicionPlaneta(int index, float* vec);

	float getRadioPlaneta(int index);

	void addLuna(int planetIndex, float distanceFromPlanet, float orbitTime, float rotationTime, float radius, GLuint textureHandle);

	void SetTexturaAnillos(int planetIndex , GLuint Textura);
};

