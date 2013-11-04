#include "Bullet.h"

Bullet::Bullet(void)
	: Entity(0, 0, BULLET_WIDTH, BULLET_HEIGHT)
{
	m_xVelocity = 0;
	m_yVelocity = 0;

	m_isActive = false;

	timeAlive = 0;
}

void Bullet::fireBullet(GLfloat xPos, GLfloat yPos, GLfloat angle)
{
	m_isActive = true;

	m_collisionBox.xPos = xPos;
	m_collisionBox.yPos = yPos;
	m_collisionBox.height = BULLET_HEIGHT;
	m_collisionBox.width = BULLET_WIDTH;

	m_xVelocity = JCos(degreesToRadians(angle + 90));
	m_yVelocity = JSin(degreesToRadians(angle + 90));
}

void Bullet::update(int dTime)
{
	if (timeAlive > BULLET_LIFETIME)
	{
		setInactive();
		return;
	}

	GLfloat dx, dy;
	
	dx = -m_xVelocity * BULLET_SPEED;
	dy = -m_yVelocity * BULLET_SPEED;

	if(m_isActive)
	{
		m_collisionBox.xPos += dx;
		m_collisionBox.yPos += dy;
	}

	timeAlive += dTime;
}

void Bullet::render()
{
	if(m_isActive)
	{
		glPushMatrix();
		glTranslatef(m_collisionBox.xPos, m_collisionBox.yPos, 0.f);

		glDisable(GL_BLEND);

		glBegin(GL_QUADS);
			glColor3f(1.f, 1.f, 1.f);
			glVertex2f(0.f, 0.f);
			glVertex2f(10.f, 0.f);
			glVertex2f(10.f, 10.f);
			glVertex2f(0.f, 10.f);
		glEnd();

		glPopMatrix();

		glEnable(GL_BLEND);
	}
}

void Bullet::setInactive()
{
	m_isActive = false;

	m_collisionBox.xPos = -10;
	m_collisionBox.yPos = -10;
	m_collisionBox.width = 0;
	m_collisionBox.height = 0;
}

Bullet::~Bullet(void)
{
}
