#include "SpriteRenderer.h"

namespace Engine2d
{
	SpriteRenderer::SpriteRenderer(ShaderBase * shader, Camera2d * camera)
	{
		_shader = shader;
		_camera = camera;
		this->Setup();
	}

	SpriteRenderer::~SpriteRenderer()
	{
		_shader = nullptr;
		_camera = nullptr;
	}
	void SpriteRenderer::Render(const char * textureName, glm::vec2 & position, glm::vec2 & size, glm::vec2 & origin, GLfloat rotation, glm::vec4 & color, glm::vec4 & destination)
	{
		UseShader();
		glm::mat4 model;
		model = glm::translate(model, glm::vec3(position, 0.0f)); 
		model = glm::rotate(model, rotation, glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::translate(model, glm::vec3(-origin.x, -origin.y, 0.0f));
		model = glm::scale(model, glm::vec3(size, 1.0f));

		_shader->SetMatrix4("model", model);
		_shader->SetVector4f("uvTransform", destination);
		_shader->SetMatrix4("projection", _camera->getProjectionMatrix());
		_shader->SetVector4f("spriteColor", color);
		_shader->SetInteger("emptyTexture", 0);

		glActiveTexture(GL_TEXTURE0);
		TextureCache::getTexture(textureName)->Bind();

		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
		glBindVertexArray(0);
	}

	void SpriteRenderer::Render2(GLuint textureId, glm::vec2 & position, glm::vec2 & size, glm::vec2 & origin, GLfloat rotation, glm::vec4 & color, glm::vec4 & destination)
	{
		UseShader();
		glm::mat4 model;
		model = glm::translate(model, glm::vec3(position, 0.0f));
		model = glm::rotate(model, rotation, glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::translate(model, glm::vec3(-origin.x, -origin.y, 0.0f));
		model = glm::scale(model, glm::vec3(size, 1.0f));

		_shader->SetMatrix4("model", model);
		_shader->SetVector4f("uvTransform", destination);
		_shader->SetMatrix4("projection", _camera->getProjectionMatrix());
		_shader->SetVector4f("spriteColor", color);
		
		if (textureId == 0) {
			_shader->SetInteger("emptyTexture", 1);
		}
		else {
			_shader->SetInteger("emptyTexture", 0);
		}

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, textureId);

		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
		glBindVertexArray(0);
	}

	void SpriteRenderer::RenderConstantState(glm::vec2 & position, glm::vec2 & size, glm::vec2 & origin, GLfloat rotation, glm::vec4 & color, glm::vec4 & destination)
	{
		glm::mat4 model;
		model = glm::translate(model, glm::vec3(position, 0.0f));
		model = glm::rotate(model, rotation, glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::translate(model, glm::vec3(-origin.x, -origin.y, 0.0f));
		model = glm::scale(model, glm::vec3(size, 1.0f));

		_shader->SetMatrix4("model", model);
		_shader->SetVector4f("uvTransform", destination);
		_shader->SetMatrix4("projection", _camera->getProjectionMatrix());
		_shader->SetVector4f("spriteColor", color);
		_shader->SetInteger("emptyTexture", 0);

		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
		glBindVertexArray(0);
	}

	void SpriteRenderer::Setup()
	{
		GLfloat vertices[] = {
			// Pos      // Tex
			0.0f, 1.0f, 0.0f, 1.0f,
			1.0f, 1.0f, 1.0f, 1.0f,
			0.0f, 0.0f, 0.0f, 0.0f,
			1.0f, 0.0f, 1.0f, 0.0f
		};

		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);

		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)(2 * sizeof(GLfloat)));
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}
	void SpriteRenderer::UseShader()
	{
		_shader->Use();
	}
}