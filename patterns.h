#ifndef PATTERNS_H
#define PATTERNS_H
#include "structs.h"

void set_glider(World &world, size_t x, size_t y, EDirecton direction)
{
	int x_direction = (direction & ( 1 << 0 )) >> 0 ? 1 : -1;
	int y_direction = (direction & ( 1 << 1 )) >> 1 ? 1 : -1;

	world.level[(x+1*x_direction) + (y+0*y_direction)*world.Width] = true;
	world.level[(x+2*x_direction) + (y+1*y_direction)*world.Width] = true;
	world.level[(x+0*x_direction) + (y+2*y_direction)*world.Width] = true;
	world.level[(x+1*x_direction) + (y+2*y_direction)*world.Width] = true;
	world.level[(x+2*x_direction) + (y+2*y_direction)*world.Width] = true;
}

void set_aircraft_carrier(World &world, size_t x, size_t y, EDirecton direction)
{
	int x_direction = (direction & ( 1 << 0 )) >> 0 ? 1 : -1;
	int y_direction = (direction & ( 1 << 1 )) >> 1 ? 1 : -1;

	world.level[(x+0*x_direction) + (y+0*y_direction)*world.Width] = true;
	world.level[(x+1*x_direction) + (y+0*y_direction)*world.Width] = true;
	world.level[(x+0*x_direction) + (y+1*y_direction)*world.Width] = true;
	world.level[(x+3*x_direction) + (y+1*y_direction)*world.Width] = true;
	world.level[(x+3*x_direction) + (y+2*y_direction)*world.Width] = true;
	world.level[(x+2*x_direction) + (y+2*y_direction)*world.Width] = true;
}

void set_line3(World &world, size_t x, size_t y, Eposition position) 
{
	int h_position = (position & ( 1 << 0 )) >> 0 ? 1 : 0;
	int v_position = (position & ( 1 << 1 )) >> 1 ? 1 : 0;

	world.level[(x+0*h_position) + (y+0*v_position)*world.Width] = true;
	world.level[(x+1*h_position) + (y+1*v_position)*world.Width] = true;
	world.level[(x+2*h_position) + (y+2*v_position)*world.Width] = true;
}

#endif //PATTERNS_H