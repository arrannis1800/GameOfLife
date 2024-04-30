#ifndef STRUCTS_H
#define STRUCTS_H
#include <SDL.h>
#include <SDL2/SDL_ttf.h>

struct World
{
	std::vector<bool> level;
	int Height;
	int Width;

	World(int h, int w)
	{
		Height = h;
		Width = w;
		level.resize(Width*Height, false);
	} 
};

struct gWindow
{
	SDL_Window* window;
	SDL_Surface* surfaceMessage;
	TTF_Font* font;
	SDL_Texture* message;
	SDL_Renderer* renderer;
	int scale;
};

enum EDirecton
{
	upper_left = 0, // 00
	upper_right = 1, // 01
	down_left = 2, // 10
	down_right = 3, // 11
};

enum Eposition
{
	horisontal = 1, // 01
	vertical = 2, // 10
};

#endif //STRUCTS_H