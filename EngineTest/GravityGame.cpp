#include "GravityGame.h"
#include "SpriteRendererShader.h"
#include "SdfTextShader.h"
#include "CircleShader.h"
#include <glm/glm.hpp>
#include <sstream>
#include <glm/gtx/rotate_vector.hpp>
#include <Box2D/Common/b2Settings.h>
#include "Utils.h"

GravityGame::GravityGame()
{
	rocket = new Rocket();
}


GravityGame::~GravityGame()
{
}

void GravityGame::Update()
{
	smoke->Update(deltaTime);
	elapsed += deltaTime;
	
	if (elapsed >= phisicsRate) {
		
		elapsed -= phisicsRate;
		world->Step(phisicsSpeed / 60.0f, 6, 2);
	}

	world->ClearForces();
	camera->Update(deltaTime);
	rocket->getBody()->SetAngularVelocity(0.0f);
	float scale = camera->getScale();
	if (inputManager->getWheel() != 0.0f) {
		
		if (inputManager->getWheel() > 0.0f) {
			scale = scale * 1.2f;
		}
		else {
			scale = scale / 1.2f;
		}

		scale = glm::max(scale, 0.0f);
		camera->setScale(scale);
	}

	if (inputManager->isKeyDown(SDLK_d)) {
		rocket->getBody()->SetAngularVelocity(0.8f);
	}

	if (inputManager->isKeyDown(SDLK_a)) {
		rocket->getBody()->SetAngularVelocity(-0.8f);
	}

	if (inputManager->isKeyPressed(SDLK_UP)) {
		phisicsSpeed *= 2.0f;
	}

	if (inputManager->isKeyPressed(SDLK_DOWN)) {
		phisicsSpeed /= 2.0f;
		if (phisicsSpeed < 1.0f) {
			phisicsSpeed = 1.0f;
		}
	}

	float dist = rocket->getBody()->GetPosition().Length();
	b2Vec2 forceDirection = rocket->getBody()->GetPosition();
	glm::vec2 normalized = glm::normalize(glm::vec2(forceDirection.x, forceDirection.y));

	b2Vec2 force(-normalized.x * 22000.02f / (dist * dist), -normalized.y * 22000.02f / (dist * dist));
	//b2Vec2 force(0, 0);
	//std::cout << dist << std::endl;

	if (inputManager->isKeyDown(SDLK_w) && phisicsSpeed == 1.0f) {
		glm::vec2 throttleVector(0.0f, -1.0f);
		throttleVector = glm::rotate(throttleVector, rocket->getBody()->GetAngle());
		throttleVector = throttleVector * 0.03f;
		force = force + b2Vec2(throttleVector.x, throttleVector.y);
		//if(rocket->getBody()->GetLinearVelocity().Length()<2.0f)
		//emitSmoke(deltaTime, glm::vec2(-throttleVector.x*0.05f, -throttleVector.y*0.05f) , glm::vec2(rocket->getBody()->GetPosition().x - throttleVector.x * 8.5f, rocket->getBody()->GetPosition().y - throttleVector.y * 8.5f));
	}

	rocket->getBody()->ApplyForceToCenter(force, true);
	std::cout << rocket->getBody()->GetLinearVelocity().Length() << std::endl;
	camera->setPosition(glm::vec2(rocket->getBody()->GetPosition().x, rocket->getBody()->GetPosition().y));
	
}

void GravityGame::emitSmoke(float delta, glm::vec2 speed, glm::vec2 position)
{
	float rate =1.0f;
	smokeElapsed += delta;

	while (smokeElapsed >= rate) {
		smokeElapsed -= rate;
		position.x += getRandom(-0.005f, 0.005f);
		position.y += getRandom(-0.005f, 0.005f);
		smoke->AddParticle(speed, position);
	}
}

void GravityGame::Draw()
{
	TextureCache::getTexture("planet")->Bind();
	planetShader->Use();

	renderer->RenderConstantState(planetShader, glm::vec2(0, 0), glm::vec2(2000.0f, 2000.0f), glm::vec2(1000.0f, 1000.0f), planet->GetAngle(), glm::vec4(1.0f));
	
	renderer->Render("falcon", glm::vec2(rocket->getBody()->GetPosition().x, rocket->getBody()->GetPosition().y), glm::vec2(0.08f, 0.52f), glm::vec2(0.040f, 0.26f), rocket->getBody()->GetAngle());

	std::stringstream ss;
	ss << "Fps: " << fps;
	textRenderer->Start();
	//textRenderer->DrawString(ss.str(), glm::vec2(5.0f, 5.0f), 0.3f, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
	textRenderer->DrawString("ship", glm::vec2(400.0f, 300.0f), 0.2f, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
	textRenderer->Stop();

	smoke->Draw(camera);
}

void GravityGame::Initialize()
{
	world = new b2World(b2Vec2(0.0f, 0.0f));
	world->SetAutoClearForces(false);
	b2CircleShape circleShape;
	circleShape.m_p.Set(0.0f, 0.0f);
	circleShape.m_radius = 1000.0f;
	b2BodyDef def;
	def.type = b2_kinematicBody;
	def.position.SetZero();
	planet = world->CreateBody(&def);
	planet->CreateFixture(&circleShape, 0.0f);
	planet->SetActive(true);
	//planet->SetAngularVelocity(0.001f);
	planet->SetSleepingAllowed(false);

	camera = new Camera2d(this->width, this->height);
	camera->Smooth = false;
	float initialScale = 512.0f;
	camera->setScale(initialScale);

	uiCam = new Camera2d(this->width, this->height);
	uiCam->setPosition(glm::vec2(this->width / 2, this->height / 2));

	spriteShader = new SpriteRendererShader();
	txtShader = new SdfTextShader();
	planetShader = new CircleShader();
	textRenderer = new BitmapFontRenderer(txtShader, uiCam);
	textRenderer->Load("Arial", -18);

	renderer = new SpriteRenderer(spriteShader, camera);
	TextureCache::preloadTexture("textures/black.jpg", "planet", true, true);
	TextureCache::preloadTexture("textures/falcon-heavy.png", "falcon", false, false);
	TextureCache::preloadTexture("textures/smoke_particle.png", "s1");
	smoke = new ParticlePool(400, 200.0f, "s1", glm::vec2(0.1f, 0.1f), glm::vec2(0.0f, 0.0f), true);
	rocket->init(world);
}


