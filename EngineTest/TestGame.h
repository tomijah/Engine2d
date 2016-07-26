#pragma once
#include "GameBase.h"
#include "InputManager.h"
#include "SpriteRenderer.h"
#include "PostProcessor.h"
#include "ParticlePool.h"
#include "GrayScaleEffect.h"
#include "ShakeEffect.h"
#include "FireSource.h"
#include "Animation.h"
#include "ShaderBase.h"
#include "BitmapFontRenderer.h"

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
	BitmapFontRenderer * textR;
	SpriteRenderer * renderer;
	SpriteRenderer * uiRenderer;
	Camera2d * camera;
	ShaderBase * shader;
	ShaderBase * txtShader;
	PostProcessor * postprocessor;
	ParticlePool * smoke;
	ParticlePool * fire;
	GrayScaleEffect * grayScale;
	ShakeEffect * shake;
	FireSource * fireSource;
	Animation * animation;
	int dir = -1;
	glm::vec2 playerPosition;
	float fireRate = 50.0f;
	float scale = 1.0f;
	void drawInternal();
	void handlePlayerAnimation();
	void puff(glm::vec2 pos);
	bool locked = false;
};

