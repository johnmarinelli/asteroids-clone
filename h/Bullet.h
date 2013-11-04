#ifndef BULLET_H
#define BULLET_H

#include "Entity.h"
#include "JMath.h"

const int BULLET_WIDTH = 10;
const int BULLET_HEIGHT = 10;
const int BULLET_SPEED = 10;

const int BULLET_LIFETIME = 1000; //1000 milliseconds

class Bullet : public Entity
{
private:
	GLfloat m_xVelocity;
	GLfloat m_yVelocity;

	int timeAlive;

public:
	Bullet(void);

	bool m_isActive;

	void fireBullet(GLfloat xPos, GLfloat yPos, GLfloat angle);
	void update(int dTime);
	void render();

	void setInactive();

	~Bullet(void);
};

#endif