#pragma once

#include <iostream>
#include <SDL/SDL.h>
#include <string>
#include "InputManager.h"

namespace Engine2d {
	class Display
	{
	public:
		Display(int width, int height, const std::string& title);
		~Display();
		void HandleInput(InputManager * inputManager);
		void SwapBuffers();
		bool IsClosed();
		void EnableCursor();
		void DisableCursor();
		virtual void Log(const std::string& message);
	private:
		bool _isClosed;
		SDL_Window * _window;
		SDL_GLContext _glContext;
	};

}