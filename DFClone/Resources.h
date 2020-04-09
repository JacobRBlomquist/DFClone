#ifndef RESOURCES_H
#define RESOURCES_H


#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <utility>
#include <map>
#include "Glyph.h"


namespace dfclone {
	typedef std::map<std::string, SDL_Texture*> Textures;

	class Resources
	{
	public:
		static bool initialized();

		static bool init(SDL_Renderer * p_renderer);

		static void shutdown();

		static  SDL_Texture* getTextureResource(std::string identifier);

		static Glyph* GetGlyphTable();

	private:
		
		static SDL_Texture* CreateTexture(SDL_Renderer* p_renderer, SDL_Surface* p_surface);

		static Glyph* glyphTable;

		static SDL_Surface* LoadImage(std::string path);

		static Textures* textures;

		static SDL_Renderer* renderer;

		static bool initial;
	};
}

#endif // !RESOURCES_H