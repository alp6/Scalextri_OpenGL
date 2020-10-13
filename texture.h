#ifndef TGA_H
#define TGA_H

#ifdef _WIN32
#include <Windows.h>
#endif

#include <GL/glut.h>
#include <SOIL.h>

class Texture
{
private:
	GLuint textureHandle;
public:
	Texture(const char* imagePath); // Generate the texture
	GLuint getTextureHandle(void); // Get the texture
};

#endif
