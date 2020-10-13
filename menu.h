#ifndef MENU_H
#define MENU_H

#ifdef _WIN32
#include <Windows.h>
#endif
#include <GL/glut.h>
#include <stdlib.h>
#include <string>

class Menu {
private:
	float startTime;
	float timeLoop;
public:
	Menu(float startTime, float timeLoop);
	void renderBitmapString(float x, float y, float z, void* font, const char* string);
	void counter(double time, int rLoops, int yLoops,  bool* stop);
	void cameraSettings(double time, float* carLoc1, float* carLoc2);
};

#endif