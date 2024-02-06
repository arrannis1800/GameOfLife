#include <stdio.h>
#include <SDL.h>

#include "structs.h"

static size_t frame = 0;

bool sdl_init(gWindow &window, int w, int h)
{
	bool success = true;

	if(SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		success = false;
	} else
	{
		window.window = SDL_CreateWindow("Life", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, w, h, SDL_WINDOW_SHOWN);
		if(window.window == NULL)
		{
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			success = false;
		} else
		{
			window.renderer = SDL_CreateRenderer(window.window, -1, SDL_RENDERER_ACCELERATED);
		}
	}

	return success;
}

bool sdl_render(gWindow &window, World &world)
{
	bool success = true;

	

	if (window.renderer == nullptr)
    {
        printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        success = false;
        return success;
    }

    SDL_RenderClear(window.renderer);

    SDL_SetRenderDrawColor(window.renderer, 255, 255, 255, 255);
    for (size_t row = 0; row < world.Height; row++)
    {
    	for (size_t col = 0; col < world.Width; col++)
    	{
    		if(world.level[col + row*world.Width])
	    	{
	    		for(size_t rs = 0; rs < window.scale; rs++)
	    		{
	    			for(size_t cs = 0; cs < window.scale; cs++)
	    			{
	    				SDL_RenderDrawPoint(window.renderer, col*window.scale+cs, row*window.scale+rs);
	    			}
	    		}
	    		
	    	}
    	}
    }
    SDL_SetRenderDrawColor(window.renderer, 0,0,0,255);


	SDL_RenderPresent(window.renderer);

	SDL_Delay(100);

	return success;
}

void sdl_finish(gWindow &window)
{
    SDL_DestroyRenderer(window.renderer);
	SDL_DestroyWindow(window.window);
	SDL_Quit();
}