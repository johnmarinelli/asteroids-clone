#include "AsteroidPool.h"

AsteroidPool::AsteroidPool(void)
{
	m_sizeCounter = 0;
	m_asteroids = std::vector<Asteroid>(POOL_SIZE);
}

void AsteroidPool::create(GLfloat x, GLfloat y, GLfloat angle)
{
	if(m_sizeCounter > 2)
	{
		m_sizeCounter = 0;
	}

	for (int i = 0; i < POOL_SIZE; ++i)
	{
		if (!m_asteroids.at(i).m_isAlive)
		{
			m_asteroids.at(i).m_isAlive = true;
			m_asteroids.at(i).setSize(m_sizeCounter++);
			m_asteroids.at(i).setPosition(x, y, angle);

			return;
		}
	}
}

void AsteroidPool::update(int dTime)
{
	for (int i = 0; i < POOL_SIZE; ++i)
	{
		m_asteroids.at(i).update(dTime);
	}
}

Asteroid* AsteroidPool::getAsteroidAt(int index)
{
	assert(index > -1 && index < POOL_SIZE);
	return &m_asteroids.at(index);
}

int AsteroidPool::getSize()
{
	return POOL_SIZE;
}

AsteroidPool::~AsteroidPool(void)
{
}
