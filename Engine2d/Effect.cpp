#include "Effect.h"

namespace Engine2d
{
	Effect::Effect(std::string shaderName, int width, int height)
	{
		_shader = new Shader(shaderName);
		glGenTextures(1, &TextureId);
		glBindTexture(GL_TEXTURE_2D, TextureId);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glBindTexture(GL_TEXTURE_2D, 0);
	}

	Effect::~Effect()
	{
		delete _shader;
		glDeleteTextures(1, &TextureId);
	}
	void Effect::UseShader()
	{
		_shader->Use();
		_shader->SetFloat("time", time);
		SetUniforms();
	}
	void Effect::EnableFor(float miliseconds)
	{
		Enable();
		ttl = miliseconds;
	}

	void Effect::Update(float gameTime, float delta)
	{
		bool checkTtl = false;
		if (ttl > 0) {
			ttl -= delta;
			checkTtl = true;
		}

		if (checkTtl && _isEnabled && ttl <= 0) {
			Disable();
		}

		time = gameTime;

		InternalUpdate(gameTime);
	}
}