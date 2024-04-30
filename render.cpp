#include <stdio.h>
#include <SDL.h>
#include <SDL2/SDL_ttf.h>

#include "structs.h"

static size_t frame = 0;

bool sdl_init(gWindow &window, int w, int h)
{
	if(SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		return false;
	} 

	window.window = SDL_CreateWindow("Life", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, w, h, SDL_WINDOW_SHOWN);
	if(window.window == NULL)
	{
		printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
		return false;
	} 

	window.renderer = SDL_CreateRenderer(window.window, -1, SDL_RENDERER_ACCELERATED);


	if( TTF_Init() == -1 )
    {
        printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
        return false;
    } 
	
	window.font = TTF_OpenFont("times.ttf", 24);
	

	return true;
}

void sdl_print_score(gWindow &window, World &world, size_t& frame)
{
	SDL_Rect Message_rect = {
    	.x = world.Width*window.scale - 150,
		.y = world.Height*window.scale - 100,
		.w = 150,
		.h = 100,
    };

    std::string text = " Frame: " + std::to_string(frame) + " ";
	SDL_Surface* surfaceMessage  = TTF_RenderText_LCD(window.font, text.c_str(), {204, 0, 102, 255}, {99, 99, 99, 230}); 
    SDL_Texture* message = SDL_CreateTextureFromSurface(window.renderer, surfaceMessage);


    SDL_RenderCopy(window.renderer, message, NULL, &Message_rect);

    SDL_FreeSurface(surfaceMessage);
	SDL_DestroyTexture(message);

}

void sdl_drawPixelScaled(int x, int y, int scale, SDL_Renderer *renderer)
{
	for(int rs = 0; rs < scale; rs++)
	{
		for(int cs = 0; cs < scale; cs++)
		{
			SDL_RenderDrawPoint(renderer, x*scale+cs, y*scale+rs);
		}
	}
}

bool sdl_draw_screen(gWindow &window, World &world)
{
	bool success = true;
	++frame;


	if (window.renderer == nullptr)
    {
        printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        success = false;
        return success;
    }

    SDL_RenderClear(window.renderer);

    SDL_SetRenderDrawColor(window.renderer, 255, 255, 255, 255);
    for (int row = 0; row < world.Height; ++row)
    {
    	for (int col = 0; col < world.Width; ++col)
    	{
    		if(world.level[col + row*world.Width])
	    	{
	    		sdl_drawPixelScaled(col, row, window.scale, window.renderer);
	    	}
    	}
    }
    SDL_SetRenderDrawColor(window.renderer, 0,0,0,255);

    sdl_print_score(window, world, frame);

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