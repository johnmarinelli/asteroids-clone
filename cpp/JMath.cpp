#include "JMath.h"

GLfloat degreesToRadians(GLfloat degrees)
{
	return (degrees * PI)/180;
}

GLfloat JCos(GLfloat radians)
{
	return std::cos(radians);
}

GLfloat JSin(GLfloat radians)
{
	return std::sin(radians);
}

bool checkCollision(collisionBox A, collisionBox B)
{
	GLfloat a_left, a_right, a_top, a_bottom;
	GLfloat b_left, b_right, b_top, b_bottom;

	a_left = A.xPos;
	a_right = A.xPos + A.width;
	a_top = A.yPos;
	a_bottom = A.yPos + A.height;

	b_left = B.xPos;
	b_right = B.xPos + B.width;
	b_top = B.yPos;
	b_bottom = B.yPos + B.height;

	if (a_bottom <= b_top)
		return false;
	if (a_top >= b_bottom)
		return false;
	if (a_right <= b_left)
		return false;
	if (a_left >= b_right)
		return false;

	return true;
}