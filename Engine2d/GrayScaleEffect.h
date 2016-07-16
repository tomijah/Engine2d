#pragma once
#include "Effect.h"

namespace Engine2d
{
	class GrayScaleEffect: public Effect
	{
	public:
		GrayScaleEffect(int width, int height);
		~GrayScaleEffect();
	protected:
		virtual void InternalUpdate(float gameTime) override;
		virtual void SetUniforms() override;
	};
}