#pragma once
#include "Shader.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <vector>
#include "Effect.h"

namespace Engine2d
{
	class PostProcessor
	{
	public:
		PostProcessor();
		~PostProcessor();
		void Start();
		void Render();
		void AddEffect(Effect * effect);
		void Update(float gameTime, float delta);
	private:
		GLuint _fbo;
		GLuint _texture;
		GLuint _rbo;
		GLuint _vao;
		std::vector<Effect *> effects;
		std::vector<Effect *> activeEffects;
	};
}