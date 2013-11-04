#ifndef JTEXTURE_H
#define JTEXTURE_H

#include "JOpenGL.h"
#include <IL/il.h>
#include <string>

struct JRect
{
	GLfloat xPos;
	GLfloat yPos;
	GLfloat width;
	GLfloat height;
};

class JTexture
{
private:
	GLuint mTextureID;
	GLuint mTextureWidth;
	GLuint mTextureHeight;

	GLuint *mPixels;
	GLuint mImgWidth;
	GLuint mImgHeight;

public:
	JTexture(void);

	bool loadTextureFromPixels32(GLuint* pixels, GLuint width, GLuint height);
	bool loadTextureFromPixels32();
	bool loadTextureFromFile(std::string path);
	bool loadPixelsFromFile(std::string path);
	bool loadTextureFromFileWithColorKey(std::string path, GLubyte r, GLubyte g, GLubyte b, GLubyte a = 000);	

	void render(GLfloat x, GLfloat y, GLfloat angle, JRect *clip = NULL);

	GLuint getTextureID();
	GLuint getTextureWidth();
	GLuint getTextureHeight();

	void freeTexture();

	~JTexture(void);
};

#endif