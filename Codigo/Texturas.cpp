#include "stdafx.h"
#include "Texturas.h"
#include "GL\glut.h"
#include <cstdio>
#include <cstdlib>



Texturas::Texturas(const char * filename) {

	int width, height;
	unsigned char * data;
	FILE * file;

	file = fopen(filename, "rb");

	if (file == NULL) int y = 0;
	width = 1024;
	height = 512;
	data = (unsigned char *)malloc(width * height * 3);
	fread(data, width * height * 3, 1, file);
	fclose(file);

	for (int i = 0; i < width * height; ++i) {
		int index = i * 3;
		unsigned char B, R;
		B = data[index];
		R = data[index + 2];

		data[index] = R;
		data[index + 2] = B;
	}

	glGenTextures(1, &Textura);
	glBindTexture(GL_TEXTURE_2D, Textura);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	gluBuild2DMipmaps(GL_TEXTURE_2D, 4, width, height, GL_RGB, GL_UNSIGNED_BYTE, data);
	free(data);
}

GLuint Texturas::getTextura(void){
	return Textura;
}
