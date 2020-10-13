#ifndef SCENE_H
#define SCENE_H

#ifdef _WIN32
#include <Windows.h>
#endif

#include <gl\glut.h>
#include <SOIL.h>
#include <vector>

class Scene {
private:
	int displayListId;
public:
	Scene(void);
	void calculateVertex(void);
	void render(void);
};
#endif