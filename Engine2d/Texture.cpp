#include "Texture.h"
#include <iostream>
namespace Engine2d
{
	Texture::Texture() :Id(0)
	{
	}

	Texture::~Texture()
	{
		glDeleteTextures(1, &Id);
	}

	void Texture::Generate(const char * fileName)
	{
		glGenTextures(1, &Id);
		glBindTexture(GL_TEXTURE_2D, Id);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		unsigned char* image = SOIL_load_image(fileName, &Width, &Height, nullptr, SOIL_LOAD_RGBA);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, Width, Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
		glGenerateMipmap(GL_TEXTURE_2D);
		SOIL_free_image_data(image);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	void Texture::Bind()
	{
		glBindTexture(GL_TEXTURE_2D, Id);
	}
}