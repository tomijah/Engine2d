#pragma once
#include "Texture.h"
#include <GL/glew.h>
#include <glm/glm.hpp>

namespace Engine2d 
{
	class Animation
	{
	public:
		Animation(Texture * tex, int xTiles, int yTiles, float rate);
		~Animation();
		GLuint GetTextureId() {
			return tex->Id;
		}

		void Update(float delta);
		void PlayLoop(int index, int count);
		void PlayOnce(int index, int count);
		void Stop(int index);
		glm::vec4 GetUV(bool reversedX = false);
	private:
		Texture * tex;
		int xTiles;
		int yTiles;
		float tileWidth;
		float tileHeight;
		float elapsed = 0;
		float rate;
		int startIndex = 0;
		int currentIndex = 0;
		int endIndex = 0;
		glm::vec4 UV;
		bool loop = false;
		bool active = false;
		void setNexIndex();
	};
}