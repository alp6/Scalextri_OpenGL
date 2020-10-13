#include "car.h"
#include "texture.h"
#define PI 3.1415926538

Texture* carTex, *carColor;
int sep = 3;

Car::Car(int carID){
	this->carID = carID;
	this->change = true;
}

// Build the car
void Car::calculateVertex(void) {

	displayListId = glGenLists(1);
	glNewList(displayListId, GL_COMPILE);

	float gray[] = { 0.75f, 0.75f, 0.75f, 1.0f };
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, gray);

	// Define magnitudes of the car and draw it
	float w = 0.3, l = 0.5, h = 0.12; 
	float w_win = 0.9, h_win = 1.6; //for the windows
	float in = 0.025, out = 0.045, in_s = 0.025, out_s = 0.01, wheels = l / 5; // for the wheels

	// Driver Part
	if (carID == 1) { carTex = new Texture("Images/red_car_driver.jpg");}
	else if (carID == 2) { carTex = new Texture("Images/yellow_car_driver.jpg"); }
	glBegin(GL_QUADS);
	glBindTexture(GL_TEXTURE_2D, carTex->getTextureHandle());
	glTexCoord2f(0.0, 1.0); glVertex3f(0.0, h, -w / 2);
	glTexCoord2f(0.0, 0.0); glVertex3f(0.0, h, w / 2);
	glTexCoord2f(1.0, 0.0); glVertex3f(l, h, w / 2);
	glTexCoord2f(1.0, 1.0); glVertex3f(l, h, -w / 2);
	glEnd();

	if (carID == 1) {carColor = new Texture("Images/red_car.jpg");}
	else if (carID == 2) { carColor = new Texture("Images/yellow_car.jpg"); }
	glBegin(GL_QUADS);
	glBindTexture(GL_TEXTURE_2D, carColor->getTextureHandle());
	// Front Part
	glTexCoord2f(1.0, 1.0); glVertex3f(0.0, h, -w / 2);
	glTexCoord2f(0.0, 1.0); glVertex3f(0.0, 0.0, -w / 2);
	glTexCoord2f(0.0, 0.0);	glVertex3f(0.0, 0.0, w / 2);
	glTexCoord2f(1.0, 0.0);	glVertex3f(0.0, h, w / 2);
	//	Back Part
	glTexCoord2f(1.0, 1.0);  glVertex3f(l, h, -w / 2);
	glTexCoord2f(0.0, 1.0);  glVertex3f(l, 0.0, -w / 2);
	glTexCoord2f(0.0, 0.0); glVertex3f(l, 0.0, w / 2);
	glTexCoord2f(1.0, 0.0); glVertex3f(l, h, w / 2);
	// Right Side
	glTexCoord2f(0.0, 1.0);	glVertex3f(l, h, -w / 2);
	glTexCoord2f(0.0, 0.0); glVertex3f(l, 0.0, -w / 2);
	glTexCoord2f(1.0, 0.0); glVertex3f(0.0, 0.0, -w / 2);
	glTexCoord2f(1.0, 1.0); glVertex3f(0.0, h, -w / 2);
	// Left Side
	glTexCoord2f(0.0, 1.0);	glVertex3f(l, h, w / 2);
	glTexCoord2f(0.0, 0.0); glVertex3f(l, 0.0, w / 2);
	glTexCoord2f(1.0, 0.0); glVertex3f(0.0, 0.0, w / 2);
	glTexCoord2f(1.0, 1.0); glVertex3f(0.0, h, w / 2);
	//Upper Part
	glTexCoord2f(0.0, 0.0);  glVertex3f(l / 2, h * h_win, (w / 2) * w_win);
	glTexCoord2f(0.0, 1.0); glVertex3f(l / 2, h * h_win, (-w / 2) * w_win);
	glTexCoord2f(1.0, 1.0); glVertex3f(l - 0.05, h * h_win, (-w / 2) * w_win);
	glTexCoord2f(1.0, 0.0); glVertex3f(l - 0.05, h * h_win, (w / 2) * w_win);
	glEnd();

	//Bottom 
	glBindTexture(GL_TEXTURE_2D, 0.0); glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_QUADS);
	glVertex3f(0, 0.05, -w / 2); glVertex3f(0.0, 0.05, w / 2);
	glVertex3f(l, 0.05, w / 2); glVertex3f(l, 0.05, -w / 2);
	glEnd();

	// Windows
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	glColor4f(0.0, 0.0, 0.50, 0.3);
	glBegin(GL_QUADS); // Front and back
	glVertex3f(l / 2 - 0.05, h, (-w / 2) * w_win); glVertex3f(l / 2 - 0.05, h, (w / 2) * w_win);
	glVertex3f(l / 2, h * h_win, (w / 2) * w_win); glVertex3f(l / 2, h * h_win, (-w / 2) * w_win);
	glVertex3f(l - 0.05, h * h_win, (-w / 2) * w_win); glVertex3f(l - 0.05, h * h_win, (w / 2) * w_win);
	glVertex3f(l - 0.05, h, (w / 2) * w_win); glVertex3f(l - 0.05, h, (-w / 2) * w_win);
	glEnd();
	glBegin(GL_POLYGON); //Right Side
	glVertex3f(l - 0.05, h, (-w / 2) * w_win); glVertex3f(l - 0.05, h * h_win, (-w / 2) * w_win);
	glVertex3f(l / 2, h * h_win, (-w / 2) * w_win); glVertex3f(l / 2 - 0.05, h, (-w / 2) * w_win);
	glEnd();
	glBegin(GL_POLYGON); //Left Side
	glVertex3f(l - 0.05, h, (w / 2) * w_win); glVertex3f(l - 0.05, h * h_win, (w / 2) * w_win);
	glVertex3f(l / 2, h * h_win, (w / 2) * w_win); glVertex3f(l / 2 - 0.05, h, (w / 2) * w_win);
	glEnd();

	//Wheels
	for (float i = -1; i <= 1; i += 2) {
		for (float j = -1; j <= 1; j += 2) {
			glPushMatrix();
			if (i == -1) { glTranslatef(l + i * wheels, 0.05, j * w / 2); }
			else { glTranslatef(i * wheels, 0.05, j * w / 2); }
			glColor3f(0.0, 0.0, 0.0); glutSolidTorus(in, out, 30, 30);
			glColor3f(1.0, 1.0, 1.0);	 glutSolidTorus(in_s, out_s, 30, 30);
			glPopMatrix();
		}
	}

	glEndList();
}

// Calculate its position in the circuit
void Car::calculatePosition(void){

	// Radius at each point depends on the car position, also when starts going down/up
	float R, r, delta1, delta2, delta3 = 2.3;
	if (carID == 1) {
		R = 1.75; r = 1.25, delta1 = 0.8, delta2 = 0.6;
	}
	else if (carID == 2) {
		R = 1.25; r = 1.75; delta1 = 0.5, delta2 = 0.9;
	}

	// Change velocities of the car every time it changes the path
	if (change == true) {
		rdmNum = this->random(1.2, 2);
	}

	switch (partPath) {
	case 0:
		position[0] = R * cos(120 * PI / 180) + sep + d0*cos(150 * PI / 180);
		position[2] = R * sin(120 * PI / 180) - d0 * sin(150 * PI / 180);
		angle_xz = -30; angle_y = 0;
		d0 += 0.05 * rdmNum; 
		change = false;
		if (position[0] <= r*cos(-60*PI/180) - sep + 0.001) {
			partPath += 1; 
			change = true;
		}
		break;
	case 1:
		position[0] = r * cos((-60 - d1)*PI / 180) - sep;
		position[2] = r * sin((-60 - d1) * PI / 180) ;
		angle_xz = (-30 + d1); 
		d1 += 2 * rdmNum; 
		change = false;
		if (position[0] >= r * cos(60 * PI / 180) - sep + 0.01) {
			partPath += 1;  
			change = true;
		}
		break;
	case 2:
		position[0] = r * cos(60 * PI / 180) - sep + d2*cos(-30 * PI / 180);
		position[2] = r * sin(60 * PI / 180) + d2 * sin(-30 * PI / 180);
		angle_xz = 30 + 180; 
		d2 += 0.05; 
		if (position[0] < - delta1) {
			position[1] += 0.02;
			angle_y = -23;
		}	else if (position[0] > delta2 && position[0] < delta3) {
			position[1] -= 0.019;
			angle_y = 23 - pow(d2/10,6);
		} else if (position[0] > delta3){
			position[1] -= 0.019;
			angle_y = 10;
		}else {
			position[1] = 0.7 - 0.01;
			angle_y = 0;
		}
		if (position[0] >= R * cos(240 * PI / 180) + sep + 0.001) {
			partPath += 1; 
			position[1] = 0; 
			angle_y = 0; 
			change = true;
		}
		break;
	case 3:
		position[0] = R * cos((240 + d3) * PI / 180) + sep;
		position[2] = R * sin((240 + d3) * PI / 180);
		angle_xz = (30 + 180 - d3);
		d3 += 2 * rdmNum; 
		change = false;
		if (position[0] <= R * cos(120 * PI / 180) + sep - 0.001) {
			partPath = 0; 
			d0 = 0; d1 = 0; d2 = 0; d3 = 0; 
			n += 1; 
			change =true;
		}
		break;
	}
}

// Render it to the screen
void Car::render(void){

	glPushMatrix();

	glTranslatef(position[0] , position[1] + 0.03 , position[2]); 
	glRotatef(angle_xz, 0, 1, 0);
	glRotatef(angle_y, 0, 0, 1);

	
	glEnable(GL_TEXTURE_2D); 
	glEnable(GL_DEPTH_TEST);
	glCallList(displayListId);
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_DEPTH_TEST);

	glPopMatrix();
}

// Get car position
void Car::getPosition(float* vec) {
	vec[0] = position[0];
	vec[1] = position[1];
	vec[2] = position[2];
}

// Get number of loops
void Car::getLoops(int* loops) {
	*loops = n;
}

// Get a random number within a range
float  Car::random(float smallNum, float bigNum) {
	float diff = bigNum - smallNum;
	return (((float)rand() / RAND_MAX) * diff) + smallNum;
}
