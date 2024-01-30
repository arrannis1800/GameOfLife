#include "structs.h"

void set_glider(Window &window, size_t x, size_t y, EDirecton direction)
{
	int x_direction = (direction & ( 1 << 0 )) >> 0 ? 1 : -1;
	int y_direction = (direction & ( 1 << 1 )) >> 1 ? 1 : -1;

	window.level[(x+1*x_direction) + (y+0*y_direction)*window.Width] = true;
	window.level[(x+2*x_direction) + (y+1*y_direction)*window.Width] = true;
	window.level[(x+0*x_direction) + (y+2*y_direction)*window.Width] = true;
	window.level[(x+1*x_direction) + (y+2*y_direction)*window.Width] = true;
	window.level[(x+2*x_direction) + (y+2*y_direction)*window.Width] = true;
}

void set_line3(Window &window, size_t x, size_t y, Eposition position) 
{
	int h_position = (position & ( 1 << 0 )) >> 0 ? 1 : 0;
	int v_position = (position & ( 1 << 1 )) >> 1 ? 1 : 0;

	window.level[(x+0*h_position) + (y+0*v_position)*window.Width] = true;
	window.level[(x+1*h_position) + (y+1*v_position)*window.Width] = true;
	window.level[(x+2*h_position) + (y+2*v_position)*window.Width] = true;
}