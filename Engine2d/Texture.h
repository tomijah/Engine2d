#pragma once
#include <GL/glew.h>
#include <SOIL.h>
namespace Engine2d
{
	class Texture
	{
	public:
		Texture();
		~Texture();
		void Generate(const char* fileName);
		void Bind();
		int Width;
		int Height;
		GLuint Id;
	};
}