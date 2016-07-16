#pragma once
#include "Effect.h"

namespace Engine2d
{
	class ShakeEffect : public Effect
	{
	public:
		ShakeEffect(int width, int height);
		~ShakeEffect();
	protected:
		virtual void InternalUpdate(float gameTime) override;
		virtual void SetUniforms() override;
	};
}