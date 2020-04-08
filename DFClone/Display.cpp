#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <string>

#include "Display.h"
#include "Resources.h"

namespace dfclone {

	void Display::render() {
		//Apply the PNG image
		SDL_BlitSurface(Resources::getSurfaceResource("loaded.png"), NULL, mWindowSurface, NULL);

		//Update the surface
		SDL_UpdateWindowSurface(mWindow);
	}
	bool Display::init(std::string title) {
		mWindow = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN);
		if (mWindow == NULL)
		{
			printf("Window could not be created. SDL Error: %s\n", SDL_GetError());
			return false;
		}

		mWindowSurface = SDL_GetWindowSurface(mWindow);
		return true;
	}
	Display::Display()
	{
		SDL_FreeSurface(mWindowSurface);
		mWindowSurface = NULL;

		SDL_DestroyWindow(mWindow);
		mWindow = NULL;
	}


	Display::~Display() {
		std::cout << "DESTROYING DISPLAY";

	}
}