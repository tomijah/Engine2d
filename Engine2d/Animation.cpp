#include "Animation.h"
#include <iostream>
namespace Engine2d
{
	Animation::Animation(Texture * tex, int xTiles, int yTiles, float rate)
	{
		this->tex = tex;
		this->xTiles = xTiles;
		this->yTiles = yTiles;
		this->rate = rate;
		this->tileWidth = 1.0f / (float)xTiles;
		this->tileHeight = 1.0f / (float)yTiles;
		UV = glm::vec4(0, 0, 1, 1);
	}

	Animation::~Animation()
	{
	}

	void Animation::Update(float delta)
	{
		if (active) {
			elapsed += delta;

			if (elapsed >= rate) {
				elapsed -= rate;
				setNexIndex();
			}
		}
	}

	void Animation::PlayLoop(int index, int count)
	{
		
		PlayOnce(index, count);
		loop = true;
	}

	void Animation::PlayOnce(int index, int count)
	{
		//std::cout << "Play" << std::endl;
		active = true;
		elapsed = 0;
		startIndex = index;
		currentIndex = index;
		endIndex = index + count - 1;
		loop = false;
	}
	void Animation::Stop(int index)
	{
		//std::cout << "Stop" << std::endl;
		active = false;
		currentIndex = index;
		loop = false;
	}
	glm::vec4 Animation::GetUV(bool reversedX)
	{
		int xIndex = currentIndex % xTiles;
		int yIndex = currentIndex / xTiles;
		glm::vec4 uvs((float)xIndex * tileWidth, (float)yIndex* tileHeight, tileWidth, tileHeight);
		return uvs;
	}
	void Animation::setNexIndex()
	{
		if (currentIndex < endIndex) {
			currentIndex++;
		}
		else {
			if (loop) {
				currentIndex = startIndex;
			}
			else {
				Stop(startIndex);
			}
		}

		//std::cout << currentIndex << std::endl;
	}
}