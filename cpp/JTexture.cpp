#include "JTexture.h"

JTexture::JTexture(void)
{
	mTextureID = 0;
	mTextureWidth = 0;
	mTextureHeight = 0;
}

bool JTexture::loadTextureFromPixels32(GLuint *pixels, GLuint width, GLuint height)
{
	 //Free texture if it exists
    freeTexture();

    //Get texture dimensions
    mTextureWidth = width;
    mTextureHeight = height;

    //Generate texture ID
    glGenTextures(1, &mTextureID);

    //Bind texture ID
    glBindTexture(GL_TEXTURE_2D, mTextureID);

    //Generate texture
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);

    //Set texture parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    //Unbind texture
    glBindTexture(GL_TEXTURE_2D, NULL);

    //Check for error
    GLenum error = glGetError();

    if(error != GL_NO_ERROR)
    {
        printf("Error loading texture from %p pixels! %s\n", pixels, gluErrorString(error));
        return false;
    }

    return true;
}

bool JTexture::loadTextureFromPixels32()
{
	bool success = true;
	
	//if there are loaded pixels
	if(mTextureID == 0 && mPixels != NULL)
	{
		//generate texture id
		glGenTextures(1, &mTextureID);
		//bind texture id
		glBindTexture(GL_TEXTURE_2D, mTextureID);

		//generate texture
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, mTextureWidth, mTextureHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, mPixels);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

		//unbind
		glBindTexture(GL_TEXTURE_2D, NULL);

		GLenum error = glGetError();

		if(error != GL_NO_ERROR)
		{
			printf("Couldn't load texture from pixels! %s\n", gluErrorString(error));
			success = false;
		}
		else
		{
			//release pixels
			delete[] mPixels;
			mPixels = NULL;
		}
	}

	else
	{
		printf("Couldn't load texture from currentPixels; ");

		if(mTextureID != 0)
		{
			printf("A texture is already loaded\n");
		}

		else if (mPixels == NULL)
		{
			printf("There are no pixels to create texture from\n");
		}

		success = false;
	}

	return success;
}

bool JTexture::loadTextureFromFile(std::string path)
{
	bool textureLoaded = false;

	//generate & set current image ID
	ILuint imgID = 0;
	ilGenImages(1, &imgID);
	ilBindImage(imgID);

	//load image
	ILboolean success = ilLoadImage(path.c_str());

	if (success == IL_TRUE)
	{
		success = ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);

		if(success == IL_TRUE)
        {
            //Create texture from file pixels
            textureLoaded = loadTextureFromPixels32((GLuint*)ilGetData(), (GLuint)ilGetInteger(IL_IMAGE_WIDTH), (GLuint)ilGetInteger(IL_IMAGE_HEIGHT));
        }
	}
	
	if(!textureLoaded)
			printf("Unable to load %s\n", path.c_str());

	return textureLoaded;
}

bool JTexture::loadPixelsFromFile(std::string path)
{
	//deallocate previous texture data
	freeTexture();

	bool pixelsLoaded = false;

	ILuint imgID = 0;
	ilGenImages(1, &imgID);
	ilBindImage(imgID);

	ILboolean success = ilLoadImage(path.c_str());

	if(success == IL_TRUE)
	{
		success = ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);
		
		if(success == IL_TRUE)
		{
			GLuint imgWidth = (GLuint)ilGetInteger(IL_IMAGE_WIDTH);
			GLuint imgHeight = (GLuint)ilGetInteger(IL_IMAGE_HEIGHT);
			
			GLuint size = imgWidth * imgHeight;
			mPixels = new GLuint[size];

			mTextureWidth = imgWidth;
			mTextureHeight = imgHeight;

			memcpy(mPixels, ilGetData(), size * 4);
			pixelsLoaded = true;
		}

		ilDeleteImages(1, &imgID);
	}

	if(!pixelsLoaded)
	{
		printf("Unable to load %s\n", path.c_str());
	}

	return pixelsLoaded;
}

bool JTexture::loadTextureFromFileWithColorKey(std::string path, GLubyte r, GLubyte g, GLubyte b, GLubyte a)
{
	if(!loadPixelsFromFile(path))
	{
		return false;
	}

	GLuint size = mTextureWidth * mTextureHeight;

	//loop through all pixels
	for (int i = 0; i < size; ++i)
	{
		//each GLuint is an array of 4 GLubytes
		GLubyte* colors = (GLubyte*)&mPixels[i];

		if (colors[0] == r && colors[1] == g && colors[2] == b && ( 0 == a || colors[3] == a))
		{
			colors[0] = 255;
			colors[1] = 255;
			colors[2] = 255;
			colors[3] = 000;
		}
	}

	return loadTextureFromPixels32();
}

void JTexture::freeTexture()
{
	if (mTextureID != 0)
	{
		glDeleteTextures(1, &mTextureID);
		mTextureID = 0;
	}

	mTextureWidth = 0;
	mTextureHeight = 0;
}

void JTexture::render(GLfloat x, GLfloat y, GLfloat angle, JRect *clip)
{
	if (mTextureID != 0)
	{
		glPushMatrix();

		//glLoadIdentity();
		glTranslatef(x, y, 0.f);
		glRotatef(angle, 0.f, 0.f, 1.f);
		glTranslatef(mTextureWidth / -2.f, mTextureHeight / -2.f, 0.f);

		GLfloat texLeft = 0.f;
		GLfloat texTop = 0.f;
		GLfloat texRight = 1.f;
		GLfloat texBottom = 1.f;

		GLfloat quadWidth = mTextureWidth;
		GLfloat quadHeight = mTextureHeight;

		if(clip != NULL)
		{
			texLeft = clip->xPos / quadWidth;
			texRight = (clip->xPos + clip->width) / quadWidth;
			texTop = clip->yPos / quadHeight;
			texBottom = (clip->yPos + clip->height) / quadHeight;

			quadWidth = clip->width;
			quadHeight = clip->height;
		}

		glBindTexture(GL_TEXTURE_2D, mTextureID);

		glBegin(GL_QUADS);
			glTexCoord2f(texLeft, texTop); glVertex2f(0.f, 0.f );
            glTexCoord2f(texRight, texTop); glVertex2f(quadWidth, 0.f );
            glTexCoord2f(texRight, texBottom); glVertex2f(quadWidth, quadHeight);
            glTexCoord2f(texLeft, texBottom); glVertex2f(0.f, quadHeight);
        glEnd();

		glPopMatrix();
	}
}

GLuint JTexture::getTextureID()
{
	return mTextureID;
}

GLuint JTexture::getTextureHeight()
{
	return mTextureHeight;
}

GLuint JTexture::getTextureWidth()
{
	return mTextureWidth;
}

JTexture::~JTexture(void)
{
	freeTexture();
}
