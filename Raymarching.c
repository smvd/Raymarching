#include <Raylib.h>
#include "Circle.c"
#include "Client.c"
#include "Constants.c"
#include <stdio.h>

#ifndef RAYMARCHING_HEADER
#define RAYMARCHING_HEADER

void Raymarching(CLIENT user, CIRCLE world[WORLD_SIZE])
{
	float currentDistance = WINDOW_WIDTH;
	float distance = WINDOW_WIDTH;

	Vector2 origin = user.pos;

	while (distance >= MINIMUM_DISTANCE && origin.x < WINDOW_WIDTH && origin.x > 0 && origin.y < WINDOW_HEIGHT && origin.y > 0)
	{
		distance = WINDOW_WIDTH;
		for (int i = 0; i < WORLD_SIZE; i++)
		{
			currentDistance = SDFCircle(origin, world[i]);

			if (currentDistance < distance)
			{
				distance = currentDistance;
			}
		}

		DrawCircleLines(origin.x, origin.y, distance, WHITE);
		DrawCircleV(origin, POINT_RADIUS, RED);

		origin = MoveAlongVector(origin, user.mouse, distance);
	}
}

#endif