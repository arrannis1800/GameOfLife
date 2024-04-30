#ifndef PATTERNS_H
#define PATTERNS_H
#include "structs.h"

void set_dot(World &world, int x, int y)
{
	if(x < world.Width && y < world.Height)
	{
		world.level[x + y*world.Width] = true;
	}
}

void set_glider(World &world, int x, int y, EDirecton direction)
{
	int x_direction = (direction & ( 1 << 0 )) >> 0 ? 1 : -1;
	int y_direction = (direction & ( 1 << 1 )) >> 1 ? 1 : -1;

	set_dot(world, x+1*x_direction, y+0*y_direction);
	set_dot(world, x+2*x_direction, y+1*y_direction);
	set_dot(world, x+0*x_direction, y+2*y_direction);
	set_dot(world, x+1*x_direction, y+2*y_direction);
	set_dot(world, x+2*x_direction, y+2*y_direction);
}

void set_aircraft_carrier(World &world, int x, int y, EDirecton direction)
{
	int x_direction = (direction & ( 1 << 0 )) >> 0 ? 1 : -1;
	int y_direction = (direction & ( 1 << 1 )) >> 1 ? 1 : -1;

	set_dot(world, x+0*x_direction, y+0*y_direction);
	set_dot(world, x+1*x_direction, y+0*y_direction);
	set_dot(world, x+0*x_direction, y+1*y_direction);
	set_dot(world, x+3*x_direction, y+1*y_direction);
	set_dot(world, x+3*x_direction, y+2*y_direction);
	set_dot(world, x+2*x_direction, y+2*y_direction);
}

void set_line3(World &world, int x, int y, Eposition position) 
{
	int h_position = (position & ( 1 << 0 )) >> 0 ? 1 : 0;
	int v_position = (position & ( 1 << 1 )) >> 1 ? 1 : 0;

	set_dot(world, x+0*h_position, y+0*v_position);
	set_dot(world, x+1*h_position, y+1*v_position);
	set_dot(world, x+2*h_position, y+2*v_position);
}

#endif //PATTERNS_H