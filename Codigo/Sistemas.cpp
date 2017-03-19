#include "stdafx.h"
#include "Sistemas.h"
#include "Sistemas.h"

Sistemas::Sistemas(){}

void Sistemas::CalcularPosicion(float time){

	for (int i = 0; i < planets.size(); i++){
		planets[i].CalcularPosicion(time);
	}
}

void Sistemas::AddPlanet(float DistanciaSol, float TiempoOrbita, float TiempoRotacion, float Radio, GLuint texture, bool Rings, int g){
	planets.push_back(Planeta(DistanciaSol, TiempoOrbita, TiempoRotacion, Radio, texture, Rings, g));
}

void Sistemas::DibujarPlanetas(){

	for (int i = 0; i < planets.size(); i++){
		planets[i].DibujarPlaneta();
	}
}

void Sistemas::DibujarOrbitas(){
	for (int i = 0; i < planets.size(); i++){
		planets[i].DibujarOrbita();
	}
}

void Sistemas::getPosicionPlaneta(int index, float* vec){
	planets[index].getPosicion(vec);
}


float Sistemas::getRadioPlaneta(int index){
	return planets[index].getRadio();
}

void Sistemas::addLuna(int planetIndex, float distanceFromPlanet, float orbitTime, float rotationTime, float radius, GLuint textureHandle){
	planets[planetIndex].addLuna(distanceFromPlanet, orbitTime, rotationTime, radius, textureHandle);
}

void Sistemas::SetTexturaAnillos(int planetIndex, GLuint textura) {
	planets[planetIndex].SetTextura(textura);
}
