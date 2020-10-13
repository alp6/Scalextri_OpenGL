#include "menu.h"

#define PI 3.14159265

Menu::Menu(float startTime, float timeLoop) {
    this->startTime = startTime;
    this->timeLoop = timeLoop;
}

void Menu::counter(double time, int rLoops, int yLoops,  bool* stop) {

    // Perform transformation so that text looks at the camera
    float modelview[16];
    int i, j;
    glPushMatrix();
    glGetFloatv(GL_MODELVIEW_MATRIX, modelview); // get the current modelview matrix
    glLoadMatrixf(modelview); // set the modelview with no rotations and scaling
    // undo all rotations and scaling
    for (i = 0; i < 3; i++)
        for (j = 0; j < 3; j++) {
            if (i == j)
                modelview[i * 4 + j] = 1.0;
            else
                modelview[i * 4 + j] = 0.0;
        }

    // Define font types 
    int font1 = (int)GLUT_BITMAP_TIMES_ROMAN_24;
    int font2 = (int)GLUT_BITMAP_HELVETICA_18;
    int font3 = (int)GLUT_BITMAP_9_BY_15;
    char  s[30];

    // Display different text depending on time
    if (time <= startTime) {

        //Start Screen
        char buffer0[50];
        if (time <startTime *2/3) { sprintf_s(buffer0, "SCALEXTRIC RACE");}
        if (time > startTime * 10 / 15 && time < startTime * 11 / 15) { sprintf_s(buffer0, " STARTING IN..."); }
        if (time > startTime * 11 / 15 && time < startTime * 12 / 15) { sprintf_s(buffer0, "              3"); }
        if (time > startTime * 12 / 15 && time < startTime * 13 / 15) { sprintf_s(buffer0, "             2"); }
        if (time > startTime * 13 / 15 && time < startTime * 14 / 15) { sprintf_s(buffer0, "             1"); }
        if (time > startTime * 14/ 15 && time < startTime ) { sprintf_s(buffer0, "             Go!"); }

        glColor3f(1.000, 1.000, 1.000);
        this->renderBitmapString(-0.3, 0.0, sin(30 * PI / 180), (void*)font1, buffer0);
        *stop = true;

    }else if (yLoops < 5 && rLoops < 5) {

        // During Race: Print # Loops of each car
        char buffer1[50];
        sprintf_s(buffer1, "Red Loops:     %d", rLoops+1);
        glColor3f(1.000, 0.000, 0.000);
        this->renderBitmapString(0.5, -0.7, sin(30 * PI / 180), (void*)font2, buffer1);
        char buffer2[50];
        sprintf_s(buffer2, "Yellow Loops: %d", yLoops+1);
        glColor3f(1.000, 1.000, 0.000);
        this->renderBitmapString(0.5, -0.8, sin(30 * PI / 180), (void*)font2, buffer2);
        *stop = false;

    }else{

        // Announce the winner
        char buffer3[50];
        if (rLoops == 5) {
            sprintf_s(buffer3, "Red Car Won!");
            glColor3f(1.000, 0.000, 0.000);
        }else if (yLoops == 5) {
            sprintf_s(buffer3, "Yellow Car Won!");
            glColor3f(1.000, 1.000, 0.000);
        }
        this->renderBitmapString(-0.3, -0.7, sin(30 * PI / 180), (void*)font1, buffer3);
        *stop = true;
    }

    glPopMatrix();
}

void Menu::cameraSettings(double time, float* carLoc1, float* carLoc2) {

    if (time >= 0 && time <= startTime) {
        gluLookAt(4.0, 3.0, 4.0, 0, 0, 0, 0.0, 1.0, 0.0);
    } else if (time >= startTime && time <= startTime + timeLoop )  {
        gluLookAt(carLoc2[0] +1 , 1.5, carLoc2[2]+1 , carLoc2[0], carLoc2[1], carLoc2[2], 0, 1, 0);
    }else if (time >= startTime + timeLoop && time <= startTime + timeLoop*2) {
        gluLookAt(-0.0, 7.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -1.0);
    } else if (time >= startTime + timeLoop*2 && time <= startTime + timeLoop*3) {
        gluLookAt(carLoc1[0] + 1, 1.5, carLoc1[2] + 1, carLoc1[0], carLoc1[1], carLoc1[2], 0, 1, 0);
    } else if (time >= startTime + timeLoop *3 && time <= startTime + timeLoop*4) {
        gluLookAt(3.0, 1.0, -3.0, 0, 0, 0, 0.0, 1.0, 0.0);
    }else if (time >= startTime + timeLoop*4 && time <= startTime + timeLoop * 5) {
        gluLookAt(carLoc2[0] + 1.0, carLoc2[1] + 1.5, carLoc2[2] + 1.0, carLoc2[0], carLoc2[1], carLoc2[2], 0, 1, 0);
    }else if (time >= startTime + timeLoop * 5) {
        gluLookAt(4.0, 3.0, 4.0, 0, 0, 0, 0.0, 1.0, 0.0);
    }
}

void Menu::renderBitmapString(float x, float y, float z, void* font, const char* string) {
    const char* c;
    glRasterPos3f(x, y, z);
    for (c = string; *c != '\0'; c++) {
        glutBitmapCharacter(font, *c);
    }
}
