#pragma once
#include <GL\glut.h>

class Texturas{
private:
	GLuint Textura;
public:
	Texturas(const char * filename);

	GLuint getTextura(void);
};
