#include "GameBase.h"
#include <math.h>
#include <algorithm>
using namespace std;

namespace Engine2d 
{
	GameBase::GameBase(int width, int height) : fps(0), totalTime(0), deltaTime(0)
	{
		this->width = width;
		this->height = height;
		_display = new Display(width, height, "OpenGL");
		inputManager = new InputManager();
	}

	GameBase::~GameBase()
	{
		delete _display;
		delete inputManager;
	}

	void GameBase::Run()
	{
		glewExperimental = true;
		glewInit();
		//glEnable(GL_DEPTH_TEST);
		glEnable(GL_STENCIL_TEST);
		glEnable(GL_CULL_FACE);

		//blending
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		//antialiasing
		glEnable(GL_MULTISAMPLE);
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		//vsync
		SDL_GL_SetSwapInterval(1);

		_display->DisableCursor();

		std::cout << glGetString(GL_VERSION) << std::endl;
		Initialize();

		float prev = totalTime;
		float startSample = 0;
		int frames = 0;
		float minDelta = 1000.0f / 120.0f;

		while (!_display->IsClosed()) {
			inputManager->update();
			_display->HandleInput(inputManager);
			Update();

			glClearDepth(1.0);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
			Draw();
			_display->SwapBuffers();
			
			totalTime = (float)SDL_GetTicks();
			deltaTime = totalTime - prev;
			prev = totalTime;
			frames++;
			if (totalTime - startSample >= 1000.0f) {
				fps = round (frames * (1000.0f/(totalTime - startSample)));
				startSample = totalTime;
				frames = 0;
			}
		}
	}
}