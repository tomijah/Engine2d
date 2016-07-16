#include "ParticlePool.h"
#include <iostream>
#include <vector>

namespace Engine2d
{
	ParticlePool::ParticlePool(int maxNum, float ttl, std::string textureName, glm::vec2 size, glm::vec2 gravity) :
		max(maxNum), gravity(gravity), ttl(ttl), textureName(textureName), size(size)
	{
		particles = new Particle[max];
		renderData = new ParticleRenderData[max];
		lastActivated = nullptr;
		color = glm::vec3(1.0f);
		initBuffers();
	}

	ParticlePool::~ParticlePool()
	{
		delete[] particles;
	}

	void ParticlePool::Update(float deltaTime)
	{
		toDraw = 0;
		Particle * current = &particles[0];
		int loops = max;
		while (loops) {
			if (current->ttl > 0) {
				current->velocity += gravity * deltaTime;
				current->position += current->velocity * deltaTime;
				current->ttl -= deltaTime;
			}
			if (current->ttl > 0) {
				toDraw++;
			}

			current++;
			loops--;
		}
	}

	void ParticlePool::Draw(Camera2d * camera)
	{
		if (!toDraw) {
			return;
		}

		Particle * current = &particles[0];
		int drawn = 0;
		while (drawn < toDraw) {
			if (current->ttl > 0) {
				renderData[drawn].position = current->position;
				renderData[drawn].ttl = current->ttl;
				drawn++;
			}

			current++;
		}

		if (!drawn) {
			return;
		}

		glBlendFunc(GL_SRC_ALPHA, GL_ONE);
		_shader->Use();
		glActiveTexture(GL_TEXTURE0);
		TextureCache::getTexture(textureName)->Bind();
		_shader->SetMatrix4("projection", camera->getProjectionMatrix());
		
		glBindBuffer(GL_ARRAY_BUFFER, particlesVBO);
		glBufferData(GL_ARRAY_BUFFER, max * 3 * sizeof(GLfloat), NULL, GL_STREAM_DRAW);
		glBufferSubData(GL_ARRAY_BUFFER, 0, drawn * sizeof(GLfloat) * 3, renderData);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(VAO);
		glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, 4, drawn);
		glBindVertexArray(0);

		//std::cout << drawn << std::endl;
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

	void ParticlePool::AddParticle(glm::vec2 velocity, glm::vec2 position)
	{
		Particle * current;
		Particle * toActivate = nullptr;
		if (lastActivated != nullptr) {
			long offset = lastActivated - particles;
			int loopsFromOffset = max - offset;

			current = lastActivated;
			while (loopsFromOffset) {
				if (current->ttl <= 0) {
					toActivate = current;
					break;
				}

				current++;
				loopsFromOffset--;
			}
		}

		if (toActivate == nullptr) {
			current = particles;
			int loops = max;
			while (loops) {
				if (current->ttl <= 0) {
					toActivate = current;
					break;
				}

				current++;
				loops--;
			}
		}

		if (toActivate != nullptr) {
			toActivate->velocity = velocity;
			toActivate->ttl = ttl;
			toActivate->position = position;
			lastActivated = toActivate;
		}
	}

	void ParticlePool::SeTColor(glm::vec3 color)
	{
		this->color = color;
		_shader->Use();
		_shader->SetVector3f("spriteColor", color);
	}

	void ParticlePool::initBuffers()
	{
		_shader = new Shader("shaders/particles");
		GLfloat vertices[] = {
					// Pos			// Tex
			-size.x / 2, size.y / 2, 0.0f, 1.0f,
			size.x / 2, size.y / 2, 1.0f, 1.0f,
			-size.x / 2, -size.y / 2, 0.0f, 0.0f,
			size.x / 2, -size.y / 2, 1.0f, 0.0f
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

		//particles data
		glGenBuffers(1, &particlesVBO);
		
		glBindBuffer(GL_ARRAY_BUFFER, particlesVBO);
		glBufferData(GL_ARRAY_BUFFER, max * 3 * sizeof(GLfloat), NULL, GL_STREAM_DRAW);

		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
		glEnableVertexAttribArray(2);
		
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glVertexAttribDivisor(0, 0);
		glVertexAttribDivisor(1, 0);
		glVertexAttribDivisor(2, 1);

		glBindVertexArray(0);

		_shader->Use();
		_shader->SetVector3f("spriteColor", color);
		_shader->SetFloat("maxTtl", ttl);
	}
}