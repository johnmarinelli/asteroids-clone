#include "Spaceship.h"

Spaceship::Spaceship(void)
{
}

Spaceship::Spaceship(GLfloat x, GLfloat y) 
	: Entity(x, y, SPACESHIP_WIDTH, SPACESHIP_HEIGHT)
{
	m_xVelocity = 0;
	m_yVelocity = 0;

	if(!m_healthBar.loadTextureFromFileWithColorKey("healthbar.png", 0, 255, 255))
	{
		printf("Couldn't load health bar!\n");
	}

	if(!m_dead.loadTextureFromFileWithColorKey("dead.png", 0, 255, 255))
	{
		printf("Couldn't load dead picture!\n");
	}

	m_healthClips.xPos = 0;
	m_healthClips.yPos = 0;
	m_healthClips.width = HEALTHBAR_WIDTH;
	m_healthClips.height = HEALTHBAR_HEIGHT;

	m_Health = SPACESHIP_HEALTH;
	m_currentSpeed = 0;

	m_isAlive = true;
	m_Angle = 0;
	
	m_bulletPool = new Bullet[BULLET_CAP];
	m_bulletsFired = 0;
	
	if(!mGraphics.loadTextureFromFileWithColorKey("ship.png", 0, 255, 255))
	{
		printf("Couldn't load spaceship gfx\n");
	}
}

Spaceship::Spaceship(const Spaceship &c)
{
	m_collisionBox = c.m_collisionBox;

	m_xVelocity = c.m_xVelocity;
	m_yVelocity = c.m_yVelocity;

	m_currentSpeed = c.m_currentSpeed;

	m_Angle = c.m_Angle;

	m_bulletPool = c.m_bulletPool;
	m_bulletsFired = c.m_bulletsFired;

	mGraphics = c.mGraphics;
}

Spaceship Spaceship::operator=(const Spaceship &c)
{
	m_collisionBox = c.m_collisionBox;

	m_xVelocity = c.m_xVelocity;
	m_yVelocity = c.m_yVelocity;

	m_Angle = c.m_Angle;

	m_bulletPool = c.m_bulletPool;
	m_bulletsFired = c.m_bulletsFired;

	mGraphics = c.mGraphics;

	return *this;
}

void Spaceship::handleInput(unsigned char key)
{
	switch(key)
	{
	case 'w': m_currentSpeed++;              break;
	case 's': m_currentSpeed--;              break;
	case 'a': m_Angle -= ANGLE_OF_ROTATION;  break;
	case 'd': m_Angle += ANGLE_OF_ROTATION;  break;
	case ' ': fireBullet();                  break;
    case 'r': if(!m_isAlive){ revive(); }    break;
	}
}

void Spaceship::update(int dTime)
{
	if (m_isAlive)
	{
		if (m_currentSpeed > MAX_SPEED)
			m_currentSpeed = MAX_SPEED;
		else if (m_currentSpeed < 0)
			m_currentSpeed = 0;

		GLfloat dX, dY;
		dX = -m_currentSpeed * JCos(degreesToRadians(m_Angle + 90));
		dY = -m_currentSpeed * JSin(degreesToRadians(m_Angle + 90));

		m_collisionBox.xPos += dX;
		m_collisionBox.yPos += dY;

		for (int i = 0; i < m_bulletsFired; i++)
		{
			m_activeBullets[i].update(dTime);
		}
	}
}

void Spaceship::render()
{
	if (m_isAlive)
	{
		mGraphics.render(m_collisionBox.xPos, m_collisionBox.yPos, m_Angle);
		m_healthBar.render(m_collisionBox.xPos, m_collisionBox.yPos + (SPACESHIP_HEIGHT * 2), 0, &m_healthClips);
	
		for (int i = 0; i < m_bulletsFired; i++)
		{
			m_activeBullets[i].render();
		}
	}

	else
		m_dead.render(m_collisionBox.xPos, m_collisionBox.yPos, 0);
}

void Spaceship::fireBullet()
{
	if (m_bulletsFired > BULLET_CAP - 1)
	{
		printf("out of bullets");
		return;
	}
	
	m_activeBullets[m_bulletsFired] = m_bulletPool[m_bulletsFired];

	m_activeBullets[m_bulletsFired].fireBullet(m_collisionBox.xPos, m_collisionBox.yPos, m_Angle);
	
	m_bulletsFired++;
}

void Spaceship::onHit()
{
	m_Health--;
	
	m_healthClips.width -= HEALTHBAR_WIDTH / SPACESHIP_HEALTH;
    
	if(m_Health < 0){
		m_isAlive = false;
	}
}

Bullet Spaceship::getActiveBullets(int index)
{
	return m_activeBullets[index];
}

int Spaceship::getBulletsFired()
{
	return m_bulletsFired;
}

void Spaceship::setBulletInactive(int index)
{
	m_activeBullets[index].setInactive();
}

void Spaceship::revive()
{
    m_Health = SPACESHIP_HEALTH;
    m_xVelocity = 0; 
    m_yVelocity = 0;
    m_healthClips.width = HEALTHBAR_WIDTH;
    m_isAlive = true;
}

Spaceship::~Spaceship(void)
{
	delete m_bulletPool;
	m_bulletPool = NULL;
}
