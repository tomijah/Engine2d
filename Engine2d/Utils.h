#pragma once
#include <random>

namespace Engine2d {
	std::random_device __rd;
	std::mt19937 __mt(__rd());

	float getRandom(float min = 0.0f, float max = 1.0f)
	{
		std::uniform_real_distribution<float> __dist(min, max);
		return __dist(__mt);
	}
}