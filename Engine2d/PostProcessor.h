#pragma once
#include "Shader.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Engine2d
{
	class PostProcessor
	{
	public:
		PostProcessor(Shader * shader);
		~PostProcessor();
		void StartRecording();
		void StopRecording();
		void RenderWithShader(float time);
	private:
		Shader * _shader;
		GLuint _fbo;
		GLuint _texture;
		GLuint _rbo;
		GLuint _vao;
	};
}