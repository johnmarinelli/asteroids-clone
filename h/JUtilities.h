#ifndef J_UTILITIES_H
#define J_UTILITIES_H

#include "JOpenGL.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

const int SPACE_WIDTH = 1280;
const int SPACE_HEIGHT = 960;

const int FRAMES_PER_SECOND = 60;

//initialize projection & modelview matrix & clear color
bool initGL();
bool loadMedia();
void loadAsteroids();

void handleKeys(unsigned char key, int x, int y);

void update(int dTime);

void renderScene();

#endif