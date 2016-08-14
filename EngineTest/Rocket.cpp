#include "Rocket.h"



Rocket::Rocket()
{
}


Rocket::~Rocket()
{
}

void Rocket::init(b2World * world)
{
	b2BodyDef def;
	def.type = b2_dynamicBody;
	def.position.Set(0.0f, -1000.0f);
	body = world->CreateBody(&def);
	b2PolygonShape shape;
	shape.SetAsBox(0.02f, 0.25f);
	b2FixtureDef fixtureDef; 
	fixtureDef.shape = &shape;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 12.5f;
	fixture = body->CreateFixture(&fixtureDef);
	body->SetLinearDamping(0.0f);
}
