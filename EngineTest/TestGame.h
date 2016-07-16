#pragma once
#include "GameBase.h"
#include "InputManager.h"
#include "SpriteRenderer.h"
#include "TextRenderer.h"
#include "PostProcessor.h"
#include "ParticlePool.h"
#include "GrayScaleEffect.h"
#include "ShakeEffect.h"
#include "FireSource.h"

using namespace Engine2d;

class TestGame : public Engine2d::GameBase
{
public:
	TestGame(int width, int height);
	~TestGame();

	virtual void Update() override;
	virtual void Draw() override;
	virtual void Initialize() override;
private:
	SpriteRenderer * renderer;
	SpriteRenderer * uiRenderer;
	TextRenderer * textRenderer;
	Camera2d * camera;
	Shader * shader;
	PostProcessor * postprocessor;
	ParticlePool * smoke;
	ParticlePool * fire;
	GrayScaleEffect * grayScale;
	ShakeEffect * shake;
	FireSource * fireSource;
	float fireRate = 100.0f;
	float scale = 1.0f;
	void drawInternal();
};

