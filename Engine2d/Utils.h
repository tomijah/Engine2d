#pragma once
#include <random>
#include "Camera2d.h"
#include "ShaderBase.h"
#include "Display.h"
#include "GameBase.h"

namespace Engine2d {
	#define MULTI_LINE_STRING(a) #a
	extern	std::random_device __rd;
	extern	std::mt19937 __mt;
	float getRandom(float min = 0.0f, float max = 1.0f);
}