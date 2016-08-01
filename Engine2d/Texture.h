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
		void Generate(const char* fileName, bool linear = false, bool generateMipmap = true);
		void Bind();
		int Width;
		int Height;
		GLuint Id;
	};
}