#include <SDL.h>
#include <SDL_image.h>
#include <map>
#include <utility>
#include <stdio.h>

#include "Glyph.h"
namespace dfclone {
	Glyph::Glyph(SDL_Surface* tileset, int widthTiles, int heightTiles)
	{
		gWidth = widthTiles;
		gHeight = heightTiles;

		glyphs = new std::map<unsigned char, unsigned int*>();
		colorCache = new std::map<unsigned long long, unsigned int*>();

		//TODO load glyphs
	}
	Glyph::~Glyph() {
		//free all data
		for (auto it = glyphs->begin(); it != glyphs->end(); it++)
		{
			delete it->second;
		}
		delete glyphs;

		for (auto it = colorCache->begin(); it != colorCache->end(); it++)
		{
			delete it->second;
		}
		delete colorCache;

		printf("Glyph destroyed\n");
	}

	void Glyph::GetGlyphSizes(int* w, int* h) {
		*w = gWidth;
		*h = gHeight;
	}

	unsigned int const* Glyph::GetGlyphStandard(unsigned char index) {
		return (unsigned int const*)glyphs->at(index);
	}

	
	unsigned int const* Glyph::GetGlyphColor(unsigned char index, unsigned int fg, unsigned int bg)
	{
		unsigned long long hash = hashColor(fg, bg);

		//if cache hit
		if (colorCache->find(hash) != colorCache->end())
		{
			return (unsigned int const*)colorCache->at(hash);
		}
		else { //cache miss
			unsigned int* raw = glyphs->at(index);
			unsigned int* colorFilled = new unsigned int[gWidth * gHeight];

			//Color Filling Codes TODO (Process colors other than black / magenta / desired)
			for (int y = 0; y < gHeight; y++)
			{
				for (int x = 0; x < gWidth; x++)
				{
					unsigned int currentRaw = raw[x + y * gWidth];
					unsigned int calculatedColor = 0;
					if (currentRaw == 0xffff00ff)//magenta (BG)
					{
						calculatedColor = bg;
					}
					else if (currentRaw == 0xff000000)//fg
					{
						calculatedColor = fg;
					}
					else { //raw color
						calculatedColor = currentRaw;
					}

					colorFilled[x + y * gWidth] = calculatedColor;

				}
			}

			colorCache->insert(std::pair<unsigned long long, unsigned int*>(hash, colorFilled));
			return (unsigned int const*)colorFilled;
		}
	}

	unsigned long long Glyph::hashColor(unsigned int fg, unsigned int bg)
	{
		unsigned long long ret = 0;
		ret = ((unsigned long long)fg << 32) | bg;
		return ret;
	}
}