#include <algorithm>
#include <vector>
#include <random>

#include "structs.h"
#include "patterns.h"
#include "render.cpp"

const int WorldHeight = 150;
const int WorldWidth  = 300;
const int LevelScale  = 4;

void generate_units(size_t num, World &world)
{
	std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<size_t> dis(0, world.Width * world.Height - 1);
	for (size_t i = 0; i < num; i++)
	{
		world.level[dis(gen)] = true;
	}
}
int find_neighbours(World &world, int row, int col)
{
	int neighbours = 0;

	for (int pos_y = -1; pos_y < 2; pos_y++)
	{
		for (int pos_x = -1; pos_x < 2; pos_x++)
		{
			if (pos_x == 0 && pos_y == 0)
				continue;
			
			if(((row + pos_y) < 0) || ((row + pos_y) >= world.Height) || ((col + pos_x) < 0) || ((col + pos_x) >= world.Width))
				continue;

			if(world.level[(col+pos_x) + (row+pos_y)*world.Width])
			{
				neighbours += 1;
			}
		}
	}

	return neighbours;
}

std::vector<bool> calc_next_state(World &world)
{
	std::vector<bool> temp = std::vector(world.Width*world.Height, false);

	for (int row = 0; row < world.Height; row++)
	{
		for (int col = 0; col < world.Width; col++)
		{
			bool state = world.level[col + row*world.Width];
			
			int neighbours = find_neighbours(world, row, col);

			if ((neighbours == 3 && !state) || ((neighbours == 3 || neighbours == 2) && state))
			{
				temp[col + row*world.Width] = true;
			}
			else 
			{
				temp[col + row*world.Width] = false;
			}
		}		
	}
	
	

	return temp;
}

int main(int argc, char* args[])
{
	(void)argc;
	(void)args;
	World world = World(WorldHeight, WorldWidth);

	// random generation
	size_t num_units = world.Width*world.Height/3;
	generate_units(num_units, world);

	// // setting patterns 
	// {
	// 	set_glider(world, 10, 10, EDirecton::down_right);
	// 	set_glider(world, 5, 7, EDirecton::upper_left);

	// 	set_line3(world, 3, 10, Eposition::horisontal);
	// 	set_line3(world, 11, 3, Eposition::vertical);


	// 	set_aircraft_carrier(world, 100, 30, EDirecton::down_right);
	// 	set_aircraft_carrier(world, 100, 50, EDirecton::upper_left);
	// }

	gWindow window;
	window.scale = LevelScale;

	if(sdl_init(window, world.Width*window.scale, world.Height*window.scale))
	{
		bool quit = false;
    	SDL_Event e;

		while(!quit)
		{
			while (SDL_PollEvent(&e))
	        {
	            if (e.type == SDL_QUIT)
	                quit = true;
	        }
			sdl_draw_screen(window, world);
			world.level = calc_next_state(world);
		}
	}

	sdl_finish(window);

	return 0;
}