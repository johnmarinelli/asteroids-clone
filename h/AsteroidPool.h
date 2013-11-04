#ifndef ASTEROIDPOOL_H
#define ASTEROIDPOOL_H

#include "Asteroid.h"
#include <assert.h>
#include <vector>

class AsteroidPool
{
private:
    static const int POOL_SIZE = 15;
	std::vector<Asteroid> m_asteroids;

	int m_sizeCounter;

public:
	void create(GLfloat x, GLfloat y, GLfloat angle);

	void update(int dTime);

	Asteroid* getAsteroidAt(int index);
	int getSize();

	AsteroidPool(void);
	~AsteroidPool(void);
};

#endif

