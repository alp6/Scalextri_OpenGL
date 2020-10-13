#ifndef CAR_H
#define CAR_H

#ifdef _WIN32
#include <Windows.h>
#endif
#include <gl\glut.h>
#include <vector>

class Car {
private:
	int displayListId;
	int carID; // differenciate each car
	float position[3]; //position in 3d space
	int partPath, n; // part of the ciurcuit and number of loops
	float d0, d1, d2, d3; //cumulative distance travelled at each path
	float angle_xz, angle_y; // Rotation of the car
	float rdmNum;
	bool change; // Tells when there is a change of path
public:
	Car(int carID);
	void calculateVertex(void);
	void calculatePosition(void);
	void render(void);
	void getPosition(float* vec);
	void getLoops(int* loops);
	float random(float smallNum, float bigNum);
};
#endif