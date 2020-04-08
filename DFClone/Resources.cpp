#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <utility>
#include <map>
#include "Resources.h"
#include "Glyph.h"

namespace dfclone {

	//declarations from static
	Surfaces *Resources::surfaces;
	SDL_Surface* Resources::img;
	SDL_Surface* Resources::tileset;
	Glyph* Resources::glyphTable;
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
		for (auto it = surfaces->begin(); it != surfaces->end(); it++)
		{
			SDL_FreeSurface(it->second);
		}

		delete surfaces;

		IMG_Quit();

		delete glyphTable;
		printf("Resources destroyed\n");
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

		//Load resources -> images
		Resources::img = LoadImage("loaded.png");
		surfaces->insert(std::pair<std::string, SDL_Surface*>("loaded.png", img));
		Resources::tileset = LoadImage("tileset16x16.png");
		surfaces->insert(std::pair < std::string, SDL_Surface*>("tileset", tileset));
		//generate glyph table
		glyphTable = new Glyph(tileset, 16, 16);

		initial = true;
		return true;
	}

	Glyph* Resources::GetGlyphTable() {
		return glyphTable;
	}


}