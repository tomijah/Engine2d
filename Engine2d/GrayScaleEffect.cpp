#include "GrayScaleEffect.h"

namespace Engine2d
{
	GrayScaleEffect::GrayScaleEffect(int width, int height) : Effect("shaders/gray", width, height)
	{
	}
	
	GrayScaleEffect::~GrayScaleEffect()
	{
	}

	void GrayScaleEffect::InternalUpdate(float gameTime)
	{
	}
	void GrayScaleEffect::SetUniforms()
	{
	}
}