#pragma once
#include <Box2D/Box2D.h>
#include <glm/glm.hpp>

class Rocket
{
public:
	Rocket();
	~Rocket();
	void init(b2World * world);
	b2Body * getBody() {
		return body;
	}
	b2Fixture * getFixture() {
		return fixture;
	}
private:
	b2Body * body;
	b2Fixture * fixture;
};

