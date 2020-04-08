#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <string>

namespace dfclone {

	class Display
	{
	public:
		void render();
		bool init(std::string title);
		Display();

		~Display();


		SDL_Window* mWindow;

	private:

		SDL_Surface* mWindowSurface;

	};
}