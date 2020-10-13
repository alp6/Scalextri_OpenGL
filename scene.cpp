#include "scene.h"
#include "texture.h"

#define PI 3.14159265
Texture* wooden, * wall, * road, *finishLine;

Scene::Scene(void)
{
	this->displayListId;
}

// Build the background and the circuit
void Scene::calculateVertex(void) {

	//Parameters of the cubemap 
	float dx_neg= -7.0, dx_pos=13.0, dy_neg=0.0, dy_pos=15.0, dz_neg= -5.0, dz_pos = 13.0 ;

	//Parameters of the road
	int r = 1, R = 2, sep = 3; // Separation among curves and outer and inner radius
	float rd = 1.0, rad = 0.45; //Parameters to find the coordenates of the middle upper path
	float height = 0.7;

	displayListId = glGenLists(1);
	glNewList(displayListId, GL_COMPILE);

	// Draw floor
	glPushMatrix();
	wooden = new Texture("Images/floor.jpg");
	glBegin(GL_QUADS);
	glBindTexture(GL_TEXTURE_2D, wooden->getTextureHandle());
	glTexCoord2f(0.0f, 0.0f);	glVertex3f(dx_neg, dy_neg, dz_neg);
	glTexCoord2f(3.0f, 0.0f);	glVertex3f(dx_pos, dy_neg, dz_neg);
	glTexCoord2f(3.0f, 3.0f);	glVertex3f(dx_pos, dy_neg, dz_pos);
	glTexCoord2f(0.0f, 3.0f);	glVertex3f(dx_neg, dy_neg, dz_pos);
	glEnd();
	glPopMatrix();

	//Draw walls
	glPushMatrix();
	wall = new Texture("Images/wall.jpg");
	glBegin(GL_QUAD_STRIP);
	glBindTexture(GL_TEXTURE_2D, wall->getTextureHandle());
	glTexCoord2f(0.0f, 0.0f);	glVertex3f(dx_neg, dy_neg, dz_pos); glTexCoord2f(0.0f, 3.0f);	glVertex3f(dx_neg, dy_pos, dz_pos);
	glTexCoord2f(2.50f, 0.0f);	glVertex3f(dx_neg, dy_neg, dz_neg); glTexCoord2f(2.50f, 3.0f);	glVertex3f(dx_neg, dy_pos, dz_neg);
	glTexCoord2f(5.0f, 0.0f);	glVertex3f(dx_pos, dy_neg, dz_neg); glTexCoord2f(5.0f, 3.0f);	glVertex3f(dx_pos, dy_pos, dz_neg);
	glTexCoord2f(7.5f, 0.0f);	glVertex3f(dx_pos, dy_neg, dz_pos); glTexCoord2f(7.5f, 3.0f);	glVertex3f(dx_pos, dy_pos, dz_pos);
	glTexCoord2f(10.0f, 0.0f);	glVertex3f(dx_neg, dy_neg, dz_pos); glTexCoord2f(10.0f, 3.0f);	glVertex3f(dx_neg, dy_pos, dz_pos);
	glEnd();
	glPopMatrix();

	//Draw road
	road = new Texture("Images/road.jpg");
	glBindTexture(GL_TEXTURE_2D, road->getTextureHandle());
	glBegin(GL_QUADS);
	glPushMatrix();
	// Path 0 - flat path
	glTexCoord2f(1, 4);  glVertex3f((R * cos(120 * PI / 180) + sep), 0.01, (R * sin(120 * PI / 180)));
	glTexCoord2f(1, 0); glVertex3f((r * cos(-60 * PI / 180) - sep), 0.01, r * sin(-60 * PI / 180));
	glTexCoord2f(0, 0); glVertex3f((R * cos(-60 * PI / 180) - sep), 0.01, (R * sin(-60 * PI / 180)));
	glTexCoord2f(0, 4); glVertex3f((r * cos(120 * PI / 180) + sep), 0.01, (r * sin(120 * PI / 180)));
	// Path 2 - ramp going up
	float x_diff = rd * cos(30 * PI / 180), z_diff = rd * sin(30 * PI / 180);
	float x_diff2 = rad * cos(120 * PI / 180), z_diff2 = rad * sin(120 * PI / 180);
	glTexCoord2f(1, 2); glVertex3f((r * cos(-120 * PI / 180) + sep), 0.01, (r * sin(-120 * PI / 180)));
	glTexCoord2f(0, 2);  glVertex3f((R * cos(-120 * PI / 180) + sep), 0.01, (R * sin(-120 * PI / 180)));
	glTexCoord2f(0, 0);  glVertex3f(x_diff + x_diff2, height, -z_diff - z_diff2);
	glTexCoord2f(1, 0); glVertex3f(x_diff - x_diff2, height, -z_diff + z_diff2);
	// Path 2 - flat path at y=height
	glTexCoord2f(0, 0); glVertex3f( - x_diff + x_diff2, height, z_diff - z_diff2);
	glTexCoord2f(0, 1); glVertex3f(x_diff + x_diff2, height, -z_diff - z_diff2);
	glTexCoord2f(1, 1); glVertex3f( x_diff - x_diff2, height, -z_diff + z_diff2);
	glTexCoord2f(1, 0); glVertex3f(-x_diff - x_diff2, height, z_diff + z_diff2);
	// Path 2 - ramp going down
	glTexCoord2f(1, 0); glVertex3f((R * cos(60 * PI / 180) - sep), 0.01, (R * sin(60 * PI / 180)));
	glTexCoord2f(0, 0); glVertex3f((r * cos(60 * PI / 180) - sep), 0.01, r * sin(60 * PI / 180));
	glTexCoord2f(0, 1); glVertex3f(-x_diff + x_diff2, height, z_diff - z_diff2);
	glTexCoord2f(1, 1); glVertex3f(-x_diff - x_diff2, height, z_diff + z_diff2);
	glEnd();
	glPopMatrix();
	glEnd();
	// Path 1 - Left Curve 
	glPushMatrix();
	glTranslatef(-sep, 0.0, 0.0);
	glBegin(GL_QUAD_STRIP);
	for (int i = 60; i <= 300; i += 8) {
		glTexCoord2f(0.0, 0.0); glVertex3f(r * cos(i * PI / 180), 0.01, r * sin(i * PI / 180));
		glTexCoord2f(1.0, 0.0); glVertex3f(R * cos(i * PI / 180), 0.01, R * sin(i * PI / 180));
		glTexCoord2f(0.0, 0.10); glVertex3f(r * cos((i + 4) * PI / 180), 0.01, r * sin((i + 4) * PI / 180));
		glTexCoord2f(1.0, 0.10); glVertex3f(R * cos((i + 4) * PI / 180), 0.01, R * sin((i + 4) * PI / 180));
	}
	glEnd();
	glPopMatrix();
	// Path 3 - Right Curve
	glPushMatrix();
	glTranslatef(sep, 0.0, 0.0);
	glBegin(GL_QUAD_STRIP);
	for (int i = -120; i <= 120; i += 8) {
		glTexCoord2f(0, 0.1);  glVertex3f(r * cos(i * PI / 180), 0.01, r * sin(i * PI / 180));
		glTexCoord2f(1, 0.1);  glVertex3f(R * cos(i * PI / 180), 0.01, R * sin(i * PI / 180));
		glTexCoord2f(0, 0);   glVertex3f(r * cos((i+4) * PI / 180), 0.01, r * sin((i+4)* PI / 180));
		glTexCoord2f(1, 0);  glVertex3f(R * cos((i+4) * PI / 180), 0.01, R * sin((i+4) * PI / 180));
	}
	glEnd();
	glPopMatrix();

	//Draw End Line
	finishLine = new Texture("Images/finish_line.png");
	glBindTexture(GL_TEXTURE_2D, finishLine->getTextureHandle());
	glPushMatrix();
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);	glVertex3f((R * cos(120 * PI / 180) + sep + 0.1), 0.02, (R * sin(120 * PI / 180)) + 0.05);
	glTexCoord2f(0.0f, 1.0f); glVertex3f((R * cos(120 * PI / 180) + sep) - 0.15, 0.02, (R * sin(120 * PI / 180)) - 0.05);
	glTexCoord2f(1.0f, 1.0f); glVertex3f((r * cos(120 * PI / 180) + sep) - 0.15, 0.02, r * sin(120 * PI / 180) - 0.05);
	glTexCoord2f(1.0f, 0.0f); glVertex3f((r * cos(120 * PI / 180) + sep + 0.1), 0.02, (r * sin(120 * PI / 180)) + 0.05);
	glEnd();
	glPopMatrix();

	glEndList();
}

// Render it to the screen
void Scene::render(void) {
	glEnable(GL_TEXTURE_2D);
	glCallList(displayListId);
	glDisable(GL_TEXTURE_2D);
}
