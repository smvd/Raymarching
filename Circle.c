#include <Raylib.h>
#include "Constants.c"
#include "Vector.c"

#ifndef CIRCLE_HEADER
#define CIRCLE_HEADER

typedef struct
{
    Vector2 pos;
    float radius;
}CIRCLE;

void DrawWorld(CIRCLE c[WORLD_SIZE])
{
	for (int i = 0; i < WORLD_SIZE; i++)
    {
        DrawCircleV(c[i].pos, c[i].radius, DARKBLUE);
    }
}

int CircleCircleCollision(CIRCLE a, CIRCLE b)
{
	a.pos.x -= b.pos.x;
	a.pos.y -= b.pos.y;

	a.radius -= b.radius;

	return a.pos.x * a.pos.x + a.pos.y * a.pos.y <= a.radius * a.radius;
}

float SDFCircle(Vector2 s, CIRCLE c)
{
    return VectorDistance(s, c.pos) - c.radius;
}

#endif