#include "ShakeEffect.h"
#include "ShakeShader.h"

namespace Engine2d
{
	ShakeEffect::ShakeEffect(int width, int height) : Effect(new ShakeShader(), width, height)
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