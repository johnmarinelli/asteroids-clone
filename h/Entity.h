#ifndef ENTITY_H
#define ENTITY_H

#include "JOpenGL.h"
#include "JTexture.h"

struct collisionBox
{
	GLfloat xPos;
	GLfloat yPos;
	GLfloat width;
	GLfloat height;
};

class Entity
{
public:
	Entity();
	Entity(GLfloat x, GLfloat y, GLfloat width, GLfloat height);

	collisionBox m_collisionBox;

	JTexture mGraphics;

	virtual void update(int dTime) = 0;
	virtual void render() = 0;
};

#endif