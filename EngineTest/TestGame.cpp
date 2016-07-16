#include "TestGame.h"
#include <iostream>
#include "TextureCache.h"
#include <glm/glm.hpp>
#include <sstream>
#include <Utils.h>

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
	delete textRenderer;
	delete uiRenderer;
	delete postprocessor;
}

void TestGame::Update()
{
	smoke->Update(deltaTime);
	fire->Update(deltaTime);
	postprocessor->Update(totalTime, deltaTime);
	fireSource->Update(deltaTime);

	if (inputManager->isKeyPressed(SDL_BUTTON_LEFT)) {
		shake->EnableFor(200.0f);
		for (int i = 0; i < 15; i++) {
			smoke->AddParticle(glm::vec2(0.0f, -0.1f * getRandom()),
				inputManager->getMouseCoords(camera) + glm::vec2(getRandom(-30.0f, 30.0f),
					getRandom(-30.0f, 30.0f)));
		}
	}

	/*if (inputManager->isKeyDown(SDL_BUTTON_RIGHT)) {
		for (int i = 0; i < 1; i++) {
			fire->AddParticle(
				glm::vec2(0.0f, -0.1f * getRandom()),
				inputManager->getMouseCoords(camera) + glm::vec2(getRandom(-10.0f, 10.0f),
					getRandom(-10.0f, 10.0f)));
		}
	}*/

	if (inputManager->isKeyDown(SDLK_d)) {
		camera->translatePosition(glm::vec2(0.2f * deltaTime, 0.0f));
	}
	if (inputManager->isKeyDown(SDLK_a)) {
		camera->translatePosition(glm::vec2(-0.2f * deltaTime, 0.0f));
	}

	if (inputManager->isKeyDown(SDLK_w)) {
		camera->translatePosition(glm::vec2(0.0f, -0.2f * deltaTime));
	}

	if (inputManager->isKeyDown(SDLK_s)) {
		camera->translatePosition(glm::vec2(0.0f, 0.2f * deltaTime));
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
		scale = glm::max(scale + 0.1f * inputManager->getWheel(), 0.0f);
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
}

void TestGame::Draw()
{
	postprocessor->Start();
	drawInternal();
	postprocessor->Render();

	std::stringstream ss;
	ss << "Fps: " << fps;
	textRenderer->RenderText(ss.str(), 5.0f, 5.0f, 1.0f);

	uiRenderer->Render("cur",
		inputManager->getMouseCoords(),
		glm::vec2(20.0f, 20.0f), glm::vec2(0), 0, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
}

void TestGame::Initialize()
{
	grayScale = new GrayScaleEffect(this->width, this->height);
	shake = new ShakeEffect(this->width, this->height);
	postprocessor = new PostProcessor();
	postprocessor->AddEffect(this->grayScale);
	postprocessor->AddEffect(this->shake);
	camera = new Camera2d(this->width, this->height);
	camera->setPosition(glm::vec2(this->width / 2, this->height / 2));
	shader = new Shader("shaders/spriteRenderer");
	renderer = new SpriteRenderer(shader, camera);
	Camera2d * uiCam = new Camera2d(this->width, this->height);
	uiCam->setPosition(glm::vec2(this->width / 2, this->height / 2));
	uiRenderer = new SpriteRenderer(shader, uiCam);
	TextureCache::preloadTexture("textures/cur.png", "cur");
	TextureCache::preloadTexture("textures/flame1.jpg", "f1");
	TextureCache::preloadTexture("textures/smoke.jpg", "s1");
	TextureCache::preloadTexture("textures/1.jpg", "1");
	TextureCache::preloadTexture("textures/anim.png", "a");
	textRenderer = new TextRenderer(this->width, this->height);
	textRenderer->Load("fonts/Capture_it.ttf",25);
	smoke = new ParticlePool(400, 2500.0f, "s1", glm::vec2(60.0f, 60.0f), glm::vec2(0.00005f, 0.0f));
	fire = new ParticlePool(1500, 1000.0f, "f1", glm::vec2(30.0f, 30.0f), glm::vec2(0.0f, 0.0f));
	fire->SeTColor(glm::vec3(1.0f, 0.2f, 0.0f));
	fireSource = new FireSource(fire, glm::vec2(600.0f, 400.0f));
	fireSource->Light(100.0f);
	smoke->SeTColor(glm::vec3(0.2f, 0.2f, 0.2f));
}

void TestGame::drawInternal()
{
	renderer->Render("1", glm::vec2(0.0f, 0.0f), glm::vec2(800, 600), glm::vec2(0, 0));
	renderer->Render("a", glm::vec2(100.0f), glm::vec2(125 / 4, 250 / 8), glm::vec2(0, 0), 0.0f, glm::vec4(1.0f), glm::vec4(0.0f, 0.0f, 1.0f / 4.0f, 1.0f / 8.0f));
	renderer->Render2(0, glm::vec2(100.0f, 400.0f), glm::vec2(100.0f, 50.0f), glm::vec2(0), 0, glm::vec4(1.0f, 0.0f, 0.0f, 0.5f));

	smoke->Draw(camera);
	fire->Draw(camera);
}

