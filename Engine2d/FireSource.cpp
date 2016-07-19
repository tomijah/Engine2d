#include "FireSource.h"
#include "Utils.h"
#include <iostream>

namespace Engine2d {

	FireSource::FireSource(ParticlePool * pool, glm::vec2 position)
	{
		_pool = pool;
		_position = position;
	}

	FireSource::~FireSource()
	{
	}

	void FireSource::Update(float deltaTime)
	{
		if (_isBurning && _rate > 0.0f) {
			toEmit += deltaTime / (1000.0f / _rate);
			
			while (toEmit >= 1) {
				_pool->AddParticle(glm::vec2(getRandom(-0.01,0.01), -0.1f * getRandom()), _position + glm::vec2(getRandom(-5.0f, 5.0f), getRandom(-10.0f, 10.0f)));
				toEmit -= 1.0f;
			}
		}
	}

	//Rate = count per sec
	void FireSource::Light(float rate)
	{
		_isBurning = true;
		_rate = rate;
	}

	void FireSource::PutOut()
	{
		_isBurning = false;
	}
}