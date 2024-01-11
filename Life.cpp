#include <stdio.h>
#include <algorithm>
#include <time.h> 
#include <unistd.h>
#include <vector>


#define WindowHeight 20
#define WindowWidth  50

#define size(T) sizeof(T)/sizeof(T[0])

static size_t frame = 0;

void generate_units(size_t num, std::vector<bool> &level)
{
	for (size_t i = 0; i < num; i++)
	{
		level[rand() % (WindowWidth*WindowHeight)] = true;
	}
}

void draw_frame(std::vector<bool> &level)
{
	for (size_t row = 0; row < WindowHeight; row++)
	{
		for (size_t col = 0; col < WindowWidth; col++)
		{
			printf("%s", level[col + row*WindowWidth] ? "@" : " ");
		}
		printf("\n");
	}
	printf("Current frame is %d", ++frame);
	
	printf("\033[%d;%dH", 0, 0);
}

std::vector<bool> calc_next_state(std::vector<bool> &level)
{
	std::vector<bool> temp;
	temp.resize(WindowWidth*WindowHeight, false);

	for (size_t row = 0; row < WindowHeight; row++)
	{
		for (size_t col = 0; col < WindowWidth; col++)
		{
			bool state = level[col + row*WindowWidth];
			int neighbours = 0;
			
			for (int pos_y = -1; pos_y < 2; pos_y++)
			{
				for (int pos_x = -1; pos_x < 2; pos_x++)
				{
					if (!(pos_x == 0 && pos_y == 0))
					{
						if(((row + pos_y) >= 0) && ((row + pos_y) < WindowHeight) && ((col + pos_x) >= 0) && ((col + pos_x) < WindowWidth))
						{
							if(level[(col+pos_x) + (row+pos_y)*WindowWidth])
							{
								neighbours += 1;
							}
						}
					}
				}
			}

			if ((neighbours == 3 && !state) || ((neighbours == 3 || neighbours == 2) && state))
			{
				temp[col + row*WindowWidth] = true;
			}
			else {
				temp[col + row*WindowWidth] = false;
			}
		}		
	}
	
	

	return temp;
}

void set_glider(std::vector<bool> &level, size_t x, size_t y)
{
	level[(x+1) + (y+0)*WindowWidth] = true;
	level[(x+2) + (y+1)*WindowWidth] = true;
	level[(x+0) + (y+2)*WindowWidth] = true;
	level[(x+1) + (y+2)*WindowWidth] = true;
	level[(x+2) + (y+2)*WindowWidth] = true;
}

int main(int argc, char const *argv[])
{
	srand(time(NULL));
	std::vector<bool> level;
	level.resize(WindowWidth*WindowHeight, false);

	// // random generation
	// generate_units(WindowWidth*WindowHeight/3, level);

	// setting patterns 
	{
		// glider
		set_glider(level, 1, 1);
		set_glider(level, 5, 7);

		// spining line
		level[20 + 10*WindowWidth] = true;
		level[21 + 10*WindowWidth] = true;
		level[22 + 10*WindowWidth] = true;
	}

	
	while(true)
	{
		draw_frame(level);
		level = calc_next_state(level);
		usleep(1*1000000/30);	
	}

	return 0;
}