#ifndef STRUCTS_H
#define STRUCTS_H
#include <SDL.h>

struct World
{
	std::vector<bool> level;
	size_t Height;
	size_t Width;

	World(size_t h, size_t w)
	{
		Height = h;
		Width = w;
		level.resize(Width*Height, false);
	} 
};

struct gWindow
{
	SDL_Window* window;
	SDL_Surface* screenSurface;
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