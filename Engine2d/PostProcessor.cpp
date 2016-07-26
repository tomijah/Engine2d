#include "PostProcessor.h"
#include <iostream>

namespace Engine2d
{
	PostProcessor::PostProcessor()
	{
		glGenFramebuffers(1, &_fbo);
		glBindFramebuffer(GL_FRAMEBUFFER, _fbo);

		//color buffer (texture)
		glGenTextures(1, &_texture);
		glBindTexture(GL_TEXTURE_2D, _texture);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 800, 600, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glBindTexture(GL_TEXTURE_2D, 0);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, _texture, 0);

		// stencil/depth buffer 
		glGenRenderbuffers(1, &_rbo);
		glBindRenderbuffer(GL_RENDERBUFFER, _rbo);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, 800, 600);
		glBindRenderbuffer(GL_RENDERBUFFER, 0);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, _rbo);
		
		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		{
			std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
		}

		glBindFramebuffer(GL_FRAMEBUFFER, 0);

		GLfloat vertices[] = {
			// Pos      // Tex
			-1.0f, 1.0f, 0.0f, 1.0f,
			-1.0f, -1.0f, 0.0f, 0.0f,
			1.0f, 1.0f, 1.0f, 1.0f,
			1.0f, -1.0f, 1.0f, 0.0f
		};

		glGenVertexArrays(1, &_vao);
		
		GLuint vbo;
		glGenBuffers(1, &vbo);

		glBindVertexArray(_vao);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)(2 * sizeof(GLfloat)));
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}

	PostProcessor::~PostProcessor()
	{
		glDeleteFramebuffers(1, &_fbo);
		glDeleteTextures(1, &_texture);
	}

	void PostProcessor::Start()
	{
		activeEffects.clear();
		for (auto const& value : effects) {
			if (value->IsEnabled()) {
				activeEffects.push_back(value);
			}
		}

		if (activeEffects.empty()) {
			return;
		}

		glBindFramebuffer(GL_FRAMEBUFFER, _fbo);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, _texture, 0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	}

	void PostProcessor::Render()
	{
		if (activeEffects.empty()) {
			return;
		}

		//std::cout << "not empty" << std::endl;

		GLuint lastTextureId = _texture;

		for (auto const& value : activeEffects) {
			if (activeEffects.back() == value) {
				glBindFramebuffer(GL_FRAMEBUFFER, 0);
				
				value->UseShader();

				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_2D, lastTextureId);

				glBindVertexArray(_vao);
				glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
				glBindVertexArray(0);
			}
			else {
				glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, value->TextureId, 0);
				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

				value->UseShader();

				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_2D, lastTextureId);

				glBindVertexArray(_vao);
				glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
				glBindVertexArray(0);

				lastTextureId = value->TextureId;
			}
		}
	}
	void PostProcessor::AddEffect(Effect *effect)
	{
		effects.push_back(effect);
	}

	void PostProcessor::Update(float gameTime, float delta)
	{
		for (auto const& value : effects) {
			if (value->IsEnabled()) {
				value->Update(gameTime, delta);
			}
		}
	}

}