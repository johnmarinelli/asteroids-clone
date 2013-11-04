#include "Asteroid.h"
#include "JMath.h"
#include "JUtilities.h"
#include <assert.h>

Asteroid::Asteroid(void)
{
	space_width = 1280;
	space_height = 960;

	m_size = asteroidSize::small;
	m_isAlive = false;
}

void Asteroid::setSize(int size)
{
	assert(size > -1 && size < asteroidSize::large + 1);
	m_size = (asteroidSize)size;
}

void Asteroid::setPosition(GLfloat x, GLfloat y, GLfloat angle)
{
	m_collisionBox.xPos = x;
	m_collisionBox.yPos = y;

	switch(m_size)
	{
	case asteroidSize::small:
		m_collisionBox.width = SMALL_ASTEROID_WIDTH; 
		m_collisionBox.height = SMALL_ASTEROID_HEIGHT;
		m_Speed = SMALL_ASTEROID_SPEED;
		m_Health = 1;
		
		if(!mGraphics.loadTextureFromFileWithColorKey("asteroid32x32.png", 0, 255, 255))
		{
			printf("Couldn't load asteroid gfx\n");
		}
		
		break;

	case asteroidSize::medium: 
		m_collisionBox.width = MED_ASTEROID_WIDTH; 
		m_collisionBox.height = MED_ASTEROID_HEIGHT;
		m_Speed = MED_ASTEROID_SPEED;
		m_Health = 2;

		if(!mGraphics.loadTextureFromFileWithColorKey("asteroid64x64.png", 0, 255, 255))
		{
			printf("Couldn't load asteroid gfx\n");
		}
		
		break;

	case asteroidSize::large: 
		m_collisionBox.width = LARGE_ASTEROID_WIDTH; 
		m_collisionBox.height = LARGE_ASTEROID_HEIGHT;
		m_Speed = LARGE_ASTEROID_SPEED;
		m_Health = 3;

		if(!mGraphics.loadTextureFromFileWithColorKey("asteroid128x128.png", 0, 255, 255))
		{
			printf("Couldn't load asteroid gfx\n");
		}
		
		break;
	}
	
	m_Angle = angle;

	m_xVelocity = -m_Speed * JCos(degreesToRadians(angle + 90));
	m_yVelocity = -m_Speed * JSin(degreesToRadians(angle + 90));

	m_isAlive = true;
}

void Asteroid::update(int dTime)
{
	if(m_isAlive)
	{
		m_collisionBox.xPos += m_xVelocity;
		m_collisionBox.yPos += m_yVelocity;
	}

	if (m_collisionBox.xPos > space_width || m_collisionBox.xPos < 0
		|| m_collisionBox.yPos > space_height || m_collisionBox.yPos < 0)
		m_isAlive = false;

	/*else if ()
		m_collisionBox.xPos = space_width;
	else if )
		m_collisionBox.yPos = space_height;*/
	
}

void Asteroid::render()
{
	if(m_isAlive)
		mGraphics.render(m_collisionBox.xPos, m_collisionBox.yPos, m_Angle++);
}

//rtns false if dead
bool Asteroid::onHit()
{
	m_Health--;

	if(m_Health <= 0)
	{
		setDead();
		return false;
	}

	return true;
}

void Asteroid::setDead()
{
	m_isAlive = false;
}

Asteroid::~Asteroid(void)
{
}
