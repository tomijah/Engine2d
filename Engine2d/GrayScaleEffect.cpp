#include "GrayScaleEffect.h"
#include "GrayScaleShader.h"

namespace Engine2d
{
	GrayScaleEffect::GrayScaleEffect(int width, int height) : Effect(new GrayScaleShader(), width, height)
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