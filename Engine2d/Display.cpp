#include "Display.h"
#include <iostream>
#include <string>

namespace Engine2d {
	Display::Display(int width, int height, const std::string& title)
	{
		_isClosed = false;
		SDL_Init(SDL_INIT_EVERYTHING);
		//SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
	//	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 16);
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
		SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
		SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
		SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
		SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
		SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
		_window = SDL_CreateWindow(title.c_str(), 
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED, 
			width, height, 
			SDL_WINDOW_OPENGL);
		_glContext = SDL_GL_CreateContext(_window);
	}

	Display::~Display()
	{
		SDL_GL_DeleteContext(this->_glContext);
		SDL_DestroyWindow(_window);
		SDL_Quit();
	}

	void Display::HandleInput(InputManager * inputManager)
	{
		SDL_Event e;
		inputManager->setWheel(0.0f);
		while (SDL_PollEvent(&e)) {
			switch (e.type)
			{
			case SDL_QUIT:
				_isClosed = true;
				break;
			case SDL_MOUSEMOTION:
				inputManager->setMouseCoords((float)e.motion.x, (float)e.motion.y);
				break;
			case SDL_KEYDOWN:
				inputManager->pressKey(e.key.keysym.sym);
				break;
			case SDL_KEYUP:
				inputManager->releaseKey(e.key.keysym.sym);
				break;
			case SDL_MOUSEBUTTONDOWN:
				inputManager->pressKey(e.button.button);
				break;
			case SDL_MOUSEBUTTONUP:
				inputManager->releaseKey(e.button.button);
				break;
			case SDL_MOUSEWHEEL:
				inputManager->setWheel((float)e.wheel.y);
			default:
				break;
			}
		}
	}

	void Display::SwapBuffers()
	{
		SDL_GL_SwapWindow(_window);
	}

	bool Display::IsClosed()
	{
		return _isClosed;
	}

	void Display::EnableCursor()
	{
		SDL_ShowCursor(SDL_ENABLE);
	}

	void Display::DisableCursor()
	{
		SDL_ShowCursor(SDL_DISABLE);
	}

	void Display::Log(const std::string& message)
	{
		std::cout << message;
	}

}