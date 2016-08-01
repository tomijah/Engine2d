#include "TextureCache.h"
#include <iostream>
namespace Engine2d
{
	std::map<std::string, Texture*> TextureCache::_textureMap;

	Texture* TextureCache::getTexture(std::string name)
	{
		return _textureMap[name];
	}

	void TextureCache::preloadTexture(const GLchar * texturePath, std::string name, bool linear, bool generateMipmap)
	{
		Texture* t = new Texture();
		t->Generate(texturePath, linear);
		_textureMap[name] = t;
	}

	void TextureCache::releaseAll()
	{
		for (auto it = _textureMap.begin(); it != _textureMap.end(); ++it)
		{
			delete it->second;
		}

		_textureMap.clear();
	}
}