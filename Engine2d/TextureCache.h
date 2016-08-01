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
		static void preloadTexture(const GLchar * texturePath, std::string name, bool linear = false, bool generateMipmap = true);
		static void releaseAll();
	private:
		static std::map<std::string, Texture*> _textureMap;
	};
}