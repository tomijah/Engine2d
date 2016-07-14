#pragma once
#include "Texture.h"
#include <iostream>
#include <map>

namespace Engine2d
{
	class TextureCache
	{
	public:
		static Texture* getTexture(std::string name);
		static void preloadTexture(const GLchar * texturePath, std::string name);
	private:
		static std::map<std::string, Texture*> _textureMap;
	};
}