#include "TestGame.h"
#include <iostream>
#include "TextureCache.h"
#include <glm/glm.hpp>
#include <sstream>
#include "SpriteRendererShader.h"
#include "SdfTextShader.h"
#include "SdfShapeShader.h"
#include "CircleShader.h"

using namespace std;
using namespace Engine2d;

TestGame::TestGame(int width, int height) : GameBase(width, height)
{
}

TestGame::~TestGame()
{
	delete renderer;
	delete camera;
	delete shader;
	delete txtShader;
	delete uiRenderer;
	delete postprocessor;
	delete shake;
	delete grayScale;
	delete fireSource;
	delete fire;
	delete smoke;
	delete sdfShader;
	TextureCache::releaseAll();
}

void TestGame::Update()
{
	camera->Update(deltaTime);
	smoke->Update(deltaTime);
	fire->Update(deltaTime);
	postprocessor->Update(totalTime, deltaTime);
	fireSource->Update(deltaTime);
	animation->Update(deltaTime);

	if (inputManager->isKeyPressed(SDL_BUTTON_LEFT)) {
		shake->EnableFor(200.0f);
		puff(playerPosition);
		playerPosition = inputManager->getMouseCoords(camera);
		puff(playerPosition);
	}

	if (inputManager->isKeyDown(SDL_BUTTON_RIGHT)) {
		for (int i = 0; i < 1; i++) {
			fire->AddParticle(
				glm::vec2(0.0f, -0.1f * getRandom()),
				inputManager->getMouseCoords(camera) + glm::vec2(getRandom(-10.0f, 10.0f),
					getRandom(-10.0f, 10.0f)));
		}
	}

	if (inputManager->isKeyDown(SDLK_d)) {
		camera->translatePosition(glm::vec2(0.2f * deltaTime * (1 / scale), 0.0f));
		locked = false;
	}

	if (inputManager->isKeyDown(SDLK_l)) {
		locked = true;
	}

	if (inputManager->isKeyDown(SDLK_a)) {
		camera->translatePosition(glm::vec2(-0.2f * deltaTime * (1 / scale), 0.0f));
		locked = false;
	}

	if (inputManager->isKeyDown(SDLK_w)) {
		camera->translatePosition(glm::vec2(0.0f, -0.2f * deltaTime * (1 / scale)));
		locked = false;
	}

	if (inputManager->isKeyDown(SDLK_s)) {
		camera->translatePosition(glm::vec2(0.0f, 0.2f * deltaTime * (1 / scale)));
		locked = false;
	}

	if (inputManager->isKeyDown(SDLK_EQUALS)) {
		fireRate += 0.1f;
		fireSource->SetRate(fireRate);
	}

	if (inputManager->isKeyDown(SDLK_MINUS)) {
		fireRate = glm::max(fireRate - 0.1f, 0.0f);
		fireSource->SetRate(fireRate);
	}

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

	if (inputManager->isKeyPressed(SDLK_SPACE)) {
		if (grayScale->IsEnabled()) {
			grayScale->Disable();
		}
		else {
			grayScale->Enable();
		}
	}

	if (inputManager->isKeyPressed(SDLK_f)) {
		if (fireSource->IsBurning()) {
			fireSource->PutOut();
		}
		else {
			fireSource->Light(fireRate);
		}
	}

	handlePlayerAnimation();
	if (locked) {
		camera->setPosition(playerPosition);
	}

	fireSource->SetPosition(playerPosition + glm::vec2(0, -15.0f));
}

void TestGame::Draw()
{
	postprocessor->Start();
	drawInternal();
	postprocessor->Render();

	std::stringstream ss;
	ss << "Fps: " << fps;

	textR->Start();
	textR->DrawString(ss.str(), glm::vec2(5.0f, 5.0f), 0.4f, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));

	textR->Stop();

	uiRenderer->Render("cur",
		inputManager->getMouseCoords(),
		glm::vec2(20.0f, 20.0f), glm::vec2(0), 0, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
}

void TestGame::drawInternal()
{
	TextureCache::getTexture("1")->Bind();
	sdfShader->Use();
	renderer->RenderConstantState(sdfShader, glm::vec2(400, 300), glm::vec2(240, 240), glm::vec2(120, 120), 0.0f, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
	renderer->Render(
		"a",
		playerPosition,
		glm::vec2(31.25f),
		glm::vec2(15.625),
		0.0f,
		glm::vec4(1.0f),
		animation->GetUV());

	fire->Draw(camera);
	smoke->Draw(camera);
}

void TestGame::handlePlayerAnimation()
{
	bool moving = false;
	int newDir = -1;
	float distance = deltaTime * 0.04f;
	if (distance <= 0) {
		return;
	}

	glm::vec2 transition(0);

	if (inputManager->isKeyDown(SDLK_DOWN)) {
		newDir = 0;
		moving = true;
		transition.y += distance;
	}

	if (inputManager->isKeyDown(SDLK_UP)) {
		newDir = 12;
		moving = true;
		transition.y -= distance;
	}

	if (inputManager->isKeyDown(SDLK_LEFT)) {
		newDir = 4;
		moving = true;
		transition.x -= distance;
	}

	if (inputManager->isKeyDown(SDLK_RIGHT)) {
		newDir = 8;
		moving = true;
		transition.x += distance;
	}

	if (inputManager->isKeyDown(SDLK_RIGHT) && inputManager->isKeyDown(SDLK_DOWN)) {
		newDir = 16;
		transition = glm::normalize(transition) * distance;
	}

	if (inputManager->isKeyDown(SDLK_RIGHT) && inputManager->isKeyDown(SDLK_UP)) {
		newDir = 28;
		transition = glm::normalize(transition) * distance;
	}

	if (inputManager->isKeyDown(SDLK_LEFT) && inputManager->isKeyDown(SDLK_DOWN)) {
		newDir = 20;
		transition = glm::normalize(transition) * distance;
	}

	if (inputManager->isKeyDown(SDLK_LEFT) && inputManager->isKeyDown(SDLK_UP)) {
		newDir = 24;
		transition = glm::normalize(transition) * distance;
	}

	if (moving) {
		if (dir != newDir) {
			dir = newDir;
			animation->PlayLoop(dir, 4);
		}

		playerPosition += transition;

	} else {
		if (dir >= 0) {
			animation->Stop(0);
			dir = -1;
		}
	}
}

void TestGame::puff(glm::vec2 pos)
{
	for (int i = 0; i < 15; i++) {
		smoke->AddParticle(glm::vec2(0.0f, -0.1f * getRandom()),
			pos + glm::vec2(getRandom(-30.0f, 30.0f),
				getRandom(-30.0f, 30.0f)));
	}
}

void TestGame::Initialize()
{
	grayScale = new GrayScaleEffect(this->width, this->height);
	shake = new ShakeEffect(this->width, this->height);
	postprocessor = new PostProcessor();
	postprocessor->AddEffect(this->grayScale);
	postprocessor->AddEffect(this->shake);
	camera = new Camera2d(this->width, this->height);
	camera->Smooth = true;
	camera->setPosition(glm::vec2(this->width / 2, this->height / 2));

	Camera2d * uiCam = new Camera2d(this->width, this->height);
	uiCam->setPosition(glm::vec2(this->width / 2, this->height / 2));

	shader = new SpriteRendererShader();
	txtShader = new SdfTextShader();
	sdfShader = new CircleShader();
	textR = new BitmapFontRenderer(txtShader, uiCam);
	textR->Load("Arial", -18);
	uiRenderer = new SpriteRenderer(shader, uiCam);
	renderer = new SpriteRenderer(shader, camera);

	TextureCache::preloadTexture("textures/cur.png", "cur");
	TextureCache::preloadTexture("textures/flame1.jpg", "f1");
	TextureCache::preloadTexture("textures/smoke_particle.png", "s1");
	TextureCache::preloadTexture("textures/grasslight-big.jpg", "1", true, true);
	TextureCache::preloadTexture("textures/anim.png", "a");
	animation = new Animation(TextureCache::getTexture("a"), 4, 8, 100);
	smoke = new ParticlePool(400, 2500.0f, "s1", glm::vec2(60.0f, 60.0f), glm::vec2(0.00005f, 0.0f));
	fire = new ParticlePool(1500, 1000.0f, "f1", glm::vec2(15.0f, 15.0f), glm::vec2(0.0f, 0.0f), true);
	fire->SeTColor(glm::vec3(1.0f, 0.2f, 0.0f));
	fireSource = new FireSource(fire, glm::vec2(600.0f, 400.0f));
	smoke->SeTColor(glm::vec3(1.0f, 1.0f, 1.0f));

	playerPosition.x = 400;
	playerPosition.y = 300;
}