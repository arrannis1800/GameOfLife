#include <stdio.h>
#include <algorithm>
#include <time.h> 
#include <unistd.h>
#include <vector>

#include "structs.h"
#include "patterns.h"

#define WindowHeight 20
#define WindowWidth  50
static size_t frame = 0;

void generate_units(size_t num, Window &window)
{
	for (size_t i = 0; i < num; i++)
	{
		window.level[rand() % (window.Width*window.Height)] = true;
	}
}

void draw_frame(Window &window)
{
	for (size_t row = 0; row < window.Height; row++)
	{
		for (size_t col = 0; col < window.Width; col++)
		{
			printf("%s", window.level[col + row*window.Width] ? "@" : " ");
		}
		printf("\n");
	}
	printf("Current frame is %zu", ++frame);
	
	printf("\033[%d;%dH", 0, 0);
}

std::vector<bool> calc_next_state(Window &window)
{
	std::vector<bool> temp;
	temp.resize(window.Width*window.Height, false);

	for (size_t row = 0; row < window.Height; row++)
	{
		for (size_t col = 0; col < window.Width; col++)
		{
			bool state = window.level[col + row*window.Width];
			int neighbours = 0;
			
			for (int pos_y = -1; pos_y < 2; pos_y++)
			{
				for (int pos_x = -1; pos_x < 2; pos_x++)
				{
					if (!(pos_x == 0 && pos_y == 0))
					{
						if(((row + pos_y) >= 0) && ((row + pos_y) < window.Height) && ((col + pos_x) >= 0) && ((col + pos_x) < window.Width))
						{
							if(window.level[(col+pos_x) + (row+pos_y)*window.Width])
							{
								neighbours += 1;
							}
						}
					}
				}
			}

			if ((neighbours == 3 && !state) || ((neighbours == 3 || neighbours == 2) && state))
			{
				temp[col + row*window.Width] = true;
			}
			else 
			{
				temp[col + row*window.Width] = false;
			}
		}		
	}
	
	

	return temp;
}

int main(int argc, char const *argv[])
{
	srand(time(NULL));
	Window window;
	window.Width = WindowWidth;
	window.Height = WindowHeight;
	window.level.resize(window.Width*window.Height, false);

	// // random generation
	// generate_units(WindowWidth*WindowHeight/3, window);

	// setting patterns 
	{
		set_glider(window, 10, 10, EDirecton::down_right);
		set_glider(window, 5, 7, EDirecton::upper_left);

		set_line3(window, 3, 10, Eposition::horisontal);
		set_line3(window, 11, 3, Eposition::vertical);
	}

	
	while(true)
	{
		draw_frame(window);
		window.level = calc_next_state(window);
		usleep(1*1000000/30);	
	}

	return 0;
}