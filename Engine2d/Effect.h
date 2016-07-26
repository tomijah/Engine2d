#pragma once
#include <iostream>
#include "ShaderBase.h"

namespace Engine2d
{
	class Effect
	{
	public:
		Effect(ShaderBase* shader, int width, int height);
		~Effect();
		void UseShader();
		bool IsEnabled() { return _isEnabled; }
		void Enable() { _isEnabled = true; }
		void EnableFor(float miliseconds);
		void Disable() { _isEnabled = false; }
		void Update(float gameTime, float delta);
		GLuint TextureId;
	private:
		bool _isEnabled = false;
		float ttl = 0;
		float time = 0;
	protected:
		ShaderBase * _shader;
		virtual void InternalUpdate(float gameTime) = 0;
		virtual void SetUniforms() = 0;
	};
}

