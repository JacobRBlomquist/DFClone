#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <string>

#include "Display.h"
#include "Resources.h"

namespace dfclone {

	void Display::render() {
		//SDL_RenderClear(mRenderer);
		//Apply the PNG image
		SDL_Texture* surfTex = Resources::getTextureResource("tileset");

		
		SDL_RenderCopy(mRenderer, surfTex, NULL,NULL);
		SDL_RenderPresent(mRenderer);

		//Update the surface
		SDL_UpdateWindowSurface(mWindow);
	}
	bool Display::init(std::string title) {
		mWindow = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN|SDL_WINDOW_RESIZABLE);
		if (mWindow == NULL)
		{
			printf("Window could not be created. SDL Error: %s\n", SDL_GetError());
			return false;
		}

		mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED);

		SDL_RendererInfo info;
		SDL_GetRendererInfo(mRenderer, &info);

		printf("Renderer Name: %s\n", info.name);
		printf("Texture Formats: \n");

		for (int i = 0; i < info.num_texture_formats; i++)
		{
			printf("%s\n", SDL_GetPixelFormatName(info.texture_formats[i]));
		}

		SDL_SetRenderDrawColor(mRenderer, 0x44, 0x44, 0x44, 0xff);
		//mWindowSurface = SDL_GetWindowSurface(mWindow);
		return true;
	}
	Display::Display()
	{
		SDL_DestroyRenderer(mRenderer);

		SDL_DestroyWindow(mWindow);
		mWindow = NULL;
	}


	Display::~Display() {
		std::cout << "Display Destroyed\n";

	}
	SDL_Renderer* Display::getRenderer()
	{
		return mRenderer;
	}
}