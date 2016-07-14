#pragma once
#include <iostream>
#include "Display.h"
#include <GL/glew.h>

namespace Engine2d
{
	class GameBase
	{
	public:
		GameBase(int width = 800, int height = 600);
		~GameBase();
		void Run();
		virtual void Update() = 0;
		virtual void Draw() = 0;
		virtual void Initialize() = 0;
	private:
		Display* _display;
	protected:
		InputManager* inputManager;
		float fps;
		float totalTime;
		float deltaTime;
		int width;
		int height;
	};
}