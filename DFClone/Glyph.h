#ifndef GLYPH_H
#define GLYPH_H

#include <SDL.h>
#include <SDL_image.h>
#include <map>


namespace dfclone {
	class Glyph
	{
	public:
		/* Initialize glyph class with a particular tileset surface. (code page 437)
			-tileset - surface to generate glyphs from
			- widthTiles - the width of a single tile (i.e. 16px etc.)
			- heightTiles - the height of a single tile
		*/
		Glyph(SDL_Surface* tileset, int widthTiles, int heightTiles);
		~Glyph();
		/* Get width and height of a single glyph.
			- w - destination for width
			- h - destination for height
		*/
		void GetGlyphSizes(int* w, int* h);

		/*Get a glyph with standard tileset colors.
		(magenta for background and black for foreground)
		-index - code page 437 glyph code

		-returns an int array containing color data in ARGB 8888 format.
		*/
		unsigned int const* GetGlyphStandard(unsigned char index);
		/*Get a glyph with colors determined by a set fg and bg color.
		Magenta in tileset will become bg, and black in tileset will become fg.
		Any other color in the tileset besides magenta and black will be copied to the glyph as is.
		-index - code page 437 glyph code
		-fg - foreground color in ARGB 8888 format
		-bg - background color in ARGB 8888 format

		-returns an int array containing color data in ARGB 8888 format.
		*/
		unsigned int const* GetGlyphColor(unsigned char index, unsigned int fg, unsigned int bg);


	private:

		unsigned long long hashColor(unsigned int fg, unsigned int bg);

		std::map<unsigned char, unsigned int*>* glyphs;
		std::map<unsigned long long, unsigned int*>* colorCache;
		int gWidth;
		int gHeight;
	};
}
#endif