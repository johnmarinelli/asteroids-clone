#include "Entity.h"

Entity::Entity()
{
}

Entity::Entity(GLfloat x, GLfloat y, GLfloat width, GLfloat height)
{
	m_collisionBox.xPos = x;
	m_collisionBox.yPos = y;
	m_collisionBox.width = width;
	m_collisionBox.height = height;
}