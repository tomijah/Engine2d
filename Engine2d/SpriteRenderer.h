#pragma once
#include "ShaderBase.h"
#include "Texture.h"
#include <glm/glm.hpp>
#include "Camera2d.h"
#include "TextureCache.h"
#include <glm/gtc/matrix_transform.hpp>

namespace Engine2d 
{
	class SpriteRenderer
	{
	public:
		SpriteRenderer(ShaderBase * shader, Camera2d * camera);
		~SpriteRenderer();
		void Render(
			const char * textureName,
			glm::vec2 &position,
			glm::vec2 &size = glm::vec2(10.0f, 10.0f),
			glm::vec2 &origin = glm::vec2(0),
			GLfloat rotation = 0.0f,
			glm::vec4 &color = glm::vec4(1.0f),
			glm::vec4 &destination = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f)
		);

		void Render2(
			GLuint textureId,
			glm::vec2 &position,
			glm::vec2 &size = glm::vec2(10.0f, 10.0f),
			glm::vec2 &origin = glm::vec2(0),
			GLfloat rotation = 0.0f,
			glm::vec4 &color = glm::vec4(1.0f),
			glm::vec4 &destination = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f)
		);

		void RenderConstantState(
			ShaderBase * shader,
			glm::vec2 &position,
			glm::vec2 &size = glm::vec2(10.0f, 10.0f),
			glm::vec2 &origin = glm::vec2(0),
			GLfloat rotation = 0.0f,
			glm::vec4 &color = glm::vec4(1.0f),
			glm::vec4 &destination = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f)
		);

		void Setup();
		void UseShader();
	private:
		GLuint VAO;
		GLuint VBO;
		ShaderBase * _shader;
		Camera2d * _camera;
	};
}