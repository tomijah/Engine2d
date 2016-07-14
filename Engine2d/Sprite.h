#pragma once
#include "Texture.h"

namespace Engine2d
{
	class Sprite
	{
	public:
		Sprite(float x, float y, float width, float height, Texture* texture);
		~Sprite();
		void Draw();
	private:
		GLuint VAO;
		GLuint VBO;
		Texture* _texture;
	};
}
