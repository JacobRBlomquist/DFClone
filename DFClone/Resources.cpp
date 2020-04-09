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
	 Textures* Resources::textures;
	 SDL_Renderer* Resources::renderer;
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

	 SDL_Texture* Resources::getTextureResource(std::string identifier)
	 {
		//doesn't exist
		if (textures->find(identifier)== textures->end())
			return textures->at("NotFound");

		auto it = textures->find(identifier);

		return it->second;
	}

	void Resources::shutdown() {
		for (auto it = textures->begin(); it != textures->end(); it++)
		{
			SDL_DestroyTexture(it->second);
		}

		delete textures;

		IMG_Quit();

		delete glyphTable;
		printf("Resources destroyed\n");
	}

	SDL_Texture* Resources::CreateTexture(SDL_Renderer* p_renderer, SDL_Surface* p_surface)
	{
		SDL_Surface * argb = SDL_ConvertSurfaceFormat(p_surface, SDL_PIXELFORMAT_ARGB8888, NULL);

		if (!argb)
		{
			printf("Error creating ARGB surface: %s\n", SDL_GetError());
		}

		SDL_Texture* ret = SDL_CreateTextureFromSurface(p_renderer, argb);

		if (!ret)
		{
			printf("Error creating Texture from ARGB Surface: %s\n", SDL_GetError());
		}


		SDL_FreeSurface(argb);
		return ret;
	}

	bool Resources::init(SDL_Renderer* p_renderer)
	{
		Resources::renderer = p_renderer;
		int imgFlags = IMG_INIT_PNG;
		if (!(IMG_Init(imgFlags) & imgFlags))
		{
			printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
			return false;
		}

		textures = new Textures();

		//Load resources -> images
	
		SDL_Texture* img =Resources::CreateTexture(p_renderer, LoadImage("loaded.png"));
		textures->insert(std::pair<std::string, SDL_Texture*>("loaded.png", img));

		SDL_Texture* tileset = Resources::CreateTexture(p_renderer, LoadImage("tileset16x16.png"));
		textures->insert(std::pair < std::string, SDL_Texture*>("tileset", tileset));

		SDL_Texture* notFound = Resources::CreateTexture(p_renderer, LoadImage("NotFound.png"));
		textures->insert(std::pair < std::string, SDL_Texture*>("NotFound", notFound));


		//generate glyph table
		//TODO
		glyphTable = new Glyph(tileset, 16, 16);

		initial = true;
		return true;
	}

	Glyph* Resources::GetGlyphTable() {
		return glyphTable;
	}


}