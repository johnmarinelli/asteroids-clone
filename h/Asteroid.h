#ifndef ASTEROID_H
#define ASTEROID_H

#include "Entity.h"

enum asteroidSize
{
	small,
	medium,
	large,
};

const GLfloat SMALL_ASTEROID_WIDTH = 32;
const GLfloat SMALL_ASTEROID_HEIGHT = 32;
const GLfloat MED_ASTEROID_WIDTH = 64;
const GLfloat MED_ASTEROID_HEIGHT = 64;
const GLfloat LARGE_ASTEROID_WIDTH = 128;
const GLfloat LARGE_ASTEROID_HEIGHT = 128;

const int SMALL_ASTEROID_SPEED = 3;
const int MED_ASTEROID_SPEED = 2;
const int LARGE_ASTEROID_SPEED = 1;

class Asteroid : public Entity
{
private:
	GLfloat m_xVelocity;
	GLfloat m_yVelocity;

	GLfloat m_Angle;

	GLfloat space_width;
	GLfloat space_height;

	asteroidSize m_size;

	int m_Speed;
	int m_Health;

public:
	bool m_isAlive;

	Asteroid(void);

	void setSize(int size);
	void setPosition(GLfloat x, GLfloat y, GLfloat angle);

	void update(int dTime);
	void render();

	bool onHit();
	void setDead();

	~Asteroid(void);
};

#endif