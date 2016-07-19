#pragma once
#include "ParticlePool.h"
#include <glm/glm.hpp>

namespace Engine2d
{
	class FireSource
	{
	public:
		FireSource(ParticlePool * pool, glm::vec2 position);
		~FireSource();
		void Update(float deltaTime);
		void Light(float rate);
		void PutOut();
		bool IsBurning() { return _isBurning; }
		void SetRate(float rate) { _rate = rate; }
		void SetPosition(glm::vec2 position) { _position = position; }
	private:
		ParticlePool * _pool;
		glm::vec2 _position;
		bool _isBurning = false;
		float _rate = 0.0f;
		float toEmit = 0;
	};
}