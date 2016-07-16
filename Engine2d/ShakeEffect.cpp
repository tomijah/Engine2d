#include "ShakeEffect.h"

namespace Engine2d
{

	ShakeEffect::ShakeEffect(int width, int height) : Effect("shaders/shake", width, height)
	{
	}


	ShakeEffect::~ShakeEffect()
	{
	}

	void ShakeEffect::InternalUpdate(float gameTime)
	{
	}
	void ShakeEffect::SetUniforms()
	{
	}
}