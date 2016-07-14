#pragma once
#include <glm/glm.hpp>
#include <GL/glew.h>
#include "SpriteRenderer.h"
#include <random>
#include "Camera2d.h"
#include "Shader.h"

namespace Engine2d
{
	struct Particle {
		glm::vec2 position, velocity;
		float ttl;
	};

	struct ParticleRenderData
	{
		glm::vec2 position;
		float ttl;
	};

	class ParticlePool
	{
	public:
		ParticlePool(
			int maxNum, 
			float ttl, 
			std::string textureName, 
			glm::vec2 size = glm::vec2(30.0f,30.0f),
			glm::vec2 gravity = glm::vec2(0));
		~ParticlePool();
		void Update(float deltaTime);
		void Draw(SpriteRenderer * renderer);
		void DrawFast(Camera2d * camera);
		void AddParticle(glm::vec2 velocity, glm::vec2 position);
		void SeTColor(glm::vec3 color);
	private:
		void initBuffers();
		Particle * particles;
		Particle * lastInactive;
		int max;
		float ttl;
		glm::vec2 gravity;
		glm::vec2 size;
		glm::vec3 color;
		std::string textureName;
		GLuint VAO;
		GLuint VBO;
		GLuint particlesVBO;
		Shader * _shader;
		int toDraw;
		ParticleRenderData * renderData;
	};
}