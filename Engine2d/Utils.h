#pragma once
#include <random>

namespace Engine2d {
	extern	std::random_device __rd;
	extern	std::mt19937 __mt;
	float getRandom(float min = 0.0f, float max = 1.0f);
}