#include "TextureCache.h"
#include <iostream>
namespace Engine2d
{
	std::map<std::string, Texture*> TextureCache::_textureMap;

	Texture* TextureCache::getTexture(std::string name)
	{
		return _textureMap[name];
	}

	void TextureCache::preloadTexture(const GLchar * texturePath, std::string name)
	{
		Texture* t = new Texture();
		t->Generate(texturePath);
		_textureMap[name] = t;
	}
}