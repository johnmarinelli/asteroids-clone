#ifndef SPACESHIP_H
#define SPACESHIP_H

#include "Entity.h"
#include "Bullet.h"

const int SPACESHIP_WIDTH = 110;
const int SPACESHIP_HEIGHT = 54;

const int SPACESHIP_HEALTH = 10;
const int HEALTHBAR_WIDTH = 128;
const int HEALTHBAR_HEIGHT = 32;

const int MAX_SPEED = 7;
const int BULLET_CAP = 10000;
const int ANGLE_OF_ROTATION = 7;

class Spaceship : public Entity
{
private:
	GLfloat m_xVelocity;
	GLfloat m_yVelocity;

	GLfloat m_Angle;

	Bullet *m_bulletPool;
	Bullet m_activeBullets[BULLET_CAP];

	int m_bulletsFired;
	int m_currentSpeed;

	JTexture m_healthBar;
	JRect m_healthClips;
	int m_Health;

	JTexture m_dead;

	bool m_isAlive;

public:
	Spaceship(void);
	Spaceship(GLfloat x, GLfloat y);
	Spaceship(const Spaceship &c);
	Spaceship operator=(const Spaceship &c);

	void handleInput(unsigned char key);
	void update(int dTime);
	void render();

	void fireBullet();
	void onHit();

	Bullet getActiveBullets(int index);
	int getBulletsFired();
	void setBulletInactive(int index);

    void revive();

	GLfloat getX()    { return m_collisionBox.xPos; };
	GLfloat getY()    { return m_collisionBox.yPos; };

	~Spaceship(void);
};

#endif

