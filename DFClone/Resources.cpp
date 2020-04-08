#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <utility>
#include <map>
#include "Resources.h"

namespace dfclone {

	Surfaces *Resources::surfaces;
	SDL_Surface* img;

	bool Resources::initial = false;

	bool Resources::initialized() {
		return initial;
	}

	SDL_Surface* Resources::LoadImage(std::string path) {
		SDL_Surface* optimizedSurface = NULL;

		//Load image at specified path
		SDL_Surface* loadedSurface = IMG_Load(path.c_str());
		if (loadedSurface == NULL)
		{
			printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
			return NULL;
		}

		return loadedSurface;

	}

	SDL_Surface * Resources::getSurfaceResource(std::string identifier) {
		//doesn't exist
		if (surfaces->find(identifier)==surfaces->end())
			return NULL;

		auto it = surfaces->find(identifier);

		return it->second;
	}

	void Resources::shutdown() {
		SDL_FreeSurface(img);
		img = NULL;
		IMG_Quit();
	}

	bool Resources::init()
	{
		int imgFlags = IMG_INIT_PNG;
		if (!(IMG_Init(imgFlags) & imgFlags))
		{
			printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
			return false;
		}

		surfaces = new Surfaces();

		Resources::img = LoadImage("loaded.png");
		surfaces->insert(std::pair<std::string, SDL_Surface*>("loaded.png", img));

		initial = true;
		return true;
	}

	SDL_Surface* Resources::img;
}