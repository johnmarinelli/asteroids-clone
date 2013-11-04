#include "JUtilities.h"
#include <time.h>
#include <vector>
#include <IL/il.h>
#include <IL/ilu.h>
#include "JTexture.h"
#include "Spaceship.h"
#include "Asteroid.h"
#include "AsteroidPool.h"

collisionBox camera;

const int ASTEROID_CAP = 10;
int gCurrentAsteroids;

Spaceship *gSpaceship;

//waow
//objekt pool pattrn
//so fansy
AsteroidPool gAsteroidPool;

bool initGL()
{
	glViewport(0.f, 0.f, SCREEN_WIDTH, SCREEN_HEIGHT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, SPACE_WIDTH, SPACE_HEIGHT, 0, 1.0, -1.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glPushMatrix();

	glClearColor(0.f, 0.f, 0.f, 1.f);
	glEnable(GL_TEXTURE_2D);

	 //Set blending 
	glEnable(GL_BLEND);
	glDisable(GL_DEPTH_TEST);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	GLenum error = glGetError();

	if (error != GL_NO_ERROR)
	{
		printf( "Error initializing OpenGL! %s\n", gluErrorString(error));
        return false;
	}

	ilInit();
    ilClearColour(255, 255, 255, 000);

    //Check for error
    ILenum ilError = ilGetError();
    if( ilError != IL_NO_ERROR )
    {
        printf("Error initializing DevIL! %s\n", iluErrorString(ilError));
        return false;
    }
	
	if(!loadMedia())
	{
		printf("Couldn't load media\n");
		return false;
	}

	printf("OpenGL and DevIL initialized\nWelcome to another Asteroids clone!  Written in OpenGL 2.1\n");
    printf("Controls:\nUp: W\nDown: S\nLeft: A\nRight: D\nFire: Spacebar\nRespawn: R\n");
	return true;
}

bool loadMedia()
{
	camera.width = SPACE_WIDTH;
	camera.height = SPACE_HEIGHT;
	camera.xPos = 0;
	camera.yPos = 0;

	gSpaceship = new Spaceship(SPACE_WIDTH / 2.f, SPACE_HEIGHT / 2.f);

	gCurrentAsteroids = 0;
	loadAsteroids();

	return true;
}

void loadAsteroids()
{
	std::srand(time(NULL));

	if (gCurrentAsteroids < 8)
	{
		int cap = std::rand() % (ASTEROID_CAP - gCurrentAsteroids);

		for (int i = 0; i < cap; ++i)
		{
			int x = std::rand() % SPACE_WIDTH;
			int y = std::rand() % SPACE_HEIGHT;

			int angle = std::rand() % 360;

			gAsteroidPool.create(x, y, angle);
			gCurrentAsteroids++;
		}
	}

	//printf("cap: %d\ncurrent asteroids: %d\n", ASTEROID_CAP, gCurrentAsteroids);
}

void handleCamera()
{
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	camera.xPos = (gSpaceship->getX()) - SPACE_WIDTH / 2.f;
	camera.yPos = (gSpaceship->getY()) - SPACE_HEIGHT / 2.f;

	glTranslatef(-camera.xPos, -camera.yPos, 0.f); 

	glPushMatrix();
}

void handleKeys(unsigned char key, int x, int y)
{
	gSpaceship->handleInput(key);
}

void update(int dTime)
{
	gSpaceship->update(dTime);
	
	//if spaceship goes out of bounds it appears on other side of 'world'
	if(gSpaceship->m_collisionBox.xPos > SPACE_WIDTH)
		gSpaceship->m_collisionBox.xPos = 0;

	else if (gSpaceship->m_collisionBox.xPos < 0)
		gSpaceship->m_collisionBox.xPos = SPACE_WIDTH;

	if(gSpaceship->m_collisionBox.yPos > SPACE_HEIGHT)
		gSpaceship->m_collisionBox.yPos = 0;

	else if (gSpaceship->m_collisionBox.yPos < 0)
		gSpaceship->m_collisionBox.yPos = SPACE_HEIGHT;

	if (gCurrentAsteroids < 3)
		loadAsteroids();
	
	gAsteroidPool.update(dTime);

	//bullet-asteroid collision
	for (int i = 0; i < gAsteroidPool.getSize(); ++i)
	{
		if(gAsteroidPool.getAsteroidAt(i)->m_isAlive){

		for (int j = 0; j < gSpaceship->getBulletsFired(); ++j)
		{
			if (checkCollision(gSpaceship->getActiveBullets(j).m_collisionBox, gAsteroidPool.getAsteroidAt(i)->m_collisionBox))
			{
				gSpaceship->setBulletInactive(j);

				if(!gAsteroidPool.getAsteroidAt(i)->onHit())
				{
					gCurrentAsteroids--;
				}

				printf("current asteroids: %d\n", gCurrentAsteroids);
			}
		}
		}
	}

	//spaceship-asteroid collision
	for (int i = 0; i < gAsteroidPool.getSize(); ++i)
	{
		if(gAsteroidPool.getAsteroidAt(i)->m_isAlive){

			if (checkCollision(gSpaceship->m_collisionBox, gAsteroidPool.getAsteroidAt(i)->m_collisionBox))
			{
				gSpaceship->onHit();

				if(gAsteroidPool.getAsteroidAt(i)->onHit())
					gCurrentAsteroids--;
			}

		}
		//this is a hacked together solution
		else
			gCurrentAsteroids--;
	}
}

void renderScene()
{
	glClear(GL_COLOR_BUFFER_BIT);
	
	handleCamera();

	gSpaceship->render();

	for (int i = 0; i < gAsteroidPool.getSize(); ++i)
	{
		//super fancy occlusion culling
		if (checkCollision(gAsteroidPool.getAsteroidAt(i)->m_collisionBox, camera))
		{
			gAsteroidPool.getAsteroidAt(i)->render();
		}
	}

	glFlush();
	
	glutSwapBuffers();
}