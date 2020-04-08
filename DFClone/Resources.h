#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <utility>
#include <map>


namespace dfclone {
	typedef std::map<std::string, SDL_Surface*> Surfaces;

	class Resources
	{
	public:
		static bool initialized();

		static bool init();

		static void shutdown();

		static  SDL_Surface* getSurfaceResource(std::string identifier);


	private:
		static SDL_Surface* img;

		static SDL_Surface* LoadImage(std::string path);

		static Surfaces* surfaces;

		static bool initial;
	};
}