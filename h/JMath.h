#ifndef JMATH_H
#define JMATH_H

#include <stdio.h>
#include <cmath>
#include "JOpenGL.h"
#include "Entity.h"

#define PI 3.1415926f

GLfloat degreesToRadians(GLfloat degrees);

GLfloat JCos(GLfloat radians);

GLfloat JSin(GLfloat radians);

bool checkCollision(collisionBox A, collisionBox B);

#endif 