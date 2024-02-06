#include <algorithm>
#include <time.h> 
#include <unistd.h>
#include <vector>

#include "structs.h"
#include "patterns.h"
#include "render.cpp"

#define WindowHeight 200
#define WindowWidth  300
#define LevelScale 4

void generate_units(size_t num, World &world)
{
	for (size_t i = 0; i < num; i++)
	{
		world.level[rand() % (world.Width*world.Height)] = true;
	}
}

std::vector<bool> calc_next_state(World &world)
{
	std::vector<bool> temp;
	temp.resize(world.Width*world.Height, false);

	for (size_t row = 0; row < world.Height; row++)
	{
		for (size_t col = 0; col < world.Width; col++)
		{
			bool state = world.level[col + row*world.Width];
			int neighbours = 0;
			
			for (int pos_y = -1; pos_y < 2; pos_y++)
			{
				for (int pos_x = -1; pos_x < 2; pos_x++)
				{
					if (!(pos_x == 0 && pos_y == 0))
					{
						if(((row + pos_y) >= 0) && ((row + pos_y) < world.Height) && ((col + pos_x) >= 0) && ((col + pos_x) < world.Width))
						{
							if(world.level[(col+pos_x) + (row+pos_y)*world.Width])
							{
								neighbours += 1;
							}
						}
					}
				}
			}

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
	srand(time(NULL));
	World world;
	world.Width = WindowWidth;
	world.Height = WindowHeight;
	world.level.resize(world.Width*world.Height, false);

	// // random generation
	// generate_units(WindowWidth*WindowHeight/3, world);

	// setting patterns 
	{
		set_glider(world, 10, 10, EDirecton::down_right);
		set_glider(world, 5, 7, EDirecton::upper_left);

		set_line3(world, 3, 10, Eposition::horisontal);
		set_line3(world, 11, 3, Eposition::vertical);
	}

	gWindow window;
	window.scale = LevelScale;

	if(sdl_init(window, WindowWidth*window.scale, WindowHeight*window.scale))
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
			sdl_render(window, world);
			world.level = calc_next_state(world);
		}
	}

	sdl_finish(window);

	return 0;
}