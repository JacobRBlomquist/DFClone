#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include "Display.h"
#include "Resources.h"


bool initSDL()
{

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		return false;
	}
	return true;
}


int main(int argc, char** argv)
{
	if (!initSDL())
	{
		printf("Failed to initialize Base SDL");
		return 1;
	}

	dfclone::Display* mainDisplay = new dfclone::Display();
	if (!mainDisplay->init("DF Clone"))return 1;
	SDL_Renderer* mainRenderer = mainDisplay->getRenderer();


	//load resources
	if (!dfclone::Resources::init(mainRenderer)||!dfclone::Resources::initialized())
	{
		return 1;
	}


	//Main loop flag
	bool quit = false;

	//Event handler
	SDL_Event e;

	//While application is running
	while (!quit)
	{
		//Handle events on queue
		while (SDL_PollEvent(&e) != 0)
		{
			//User requests quit
			if (e.type == SDL_QUIT)
			{
				quit = true;
			}
			else if (e.type == SDL_WINDOWEVENT)
			{
				if (e.window.event == SDL_WINDOWEVENT_RESIZED)
				{
					printf("Resizing window: %d X %d\n",e.window.data1,e.window.data2);
				}
			}
			else if (e.type == SDL_DROPFILE)
			{
				char* droppedFileDir = e.drop.file;

				SDL_ShowSimpleMessageBox(
					SDL_MESSAGEBOX_INFORMATION,
					"File dropped on window",
					droppedFileDir,
					SDL_GetWindowFromID(e.drop.windowID)
					);

			}
			
		}

		mainDisplay->render();

	}
	delete mainDisplay;
	dfclone::Resources::shutdown();

	SDL_Quit();
	return 0;
}

