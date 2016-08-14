#pragma once
#include "GameBase.h"
#include "InputManager.h"
#include "SpriteRenderer.h"
#include "ParticlePool.h"
#include "ShaderBase.h"
#include "BitmapFontRenderer.h"
#include <Box2D/Box2D.h>
#include "Rocket.h"

using namespace Engine2d;

class GravityGame: public GameBase
{
public:
	GravityGame();
	~GravityGame();

	virtual void Update() override;
	virtual void Draw() override;
	virtual void Initialize() override;
private:
	ShaderBase * planetShader;
	SpriteRenderer * renderer;
	Camera2d * camera;
	Camera2d * uiCam;
	ShaderBase * txtShader;
	ShaderBase * spriteShader;
	BitmapFontRenderer * textRenderer;
	b2World * world;
	b2Body * planet;
	Rocket * rocket;
	float phisicsRate = 17.0f;
	float elapsed = 0;
	float phisicsSpeed = 1.0f;
	ParticlePool * smoke;
	void emitSmoke(float delta, glm::vec2 speed, glm::vec2 position);
	float smokeElapsed = 0.0f;
};

