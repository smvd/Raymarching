#include <Raylib.h>
#include <Math.h>

#ifndef VECTOR_HEADER
#define VECTOR_HEADER

Vector2 VectorSubtract(Vector2 a, Vector2 b)
{
	a.x -= b.x;
	a.y -= b.y;

	return a;
}

float VectorDistance(Vector2 a, Vector2 b)
{
	return sqrt(pow(b.x - a.x, 2) + pow(b.y - a.y, 2));
}

Vector2 MoveAlongVector(Vector2 origin, Vector2 end, float distance)
{
	float t = distance / VectorDistance(origin, end);

	origin.x = ((1 - t)*origin.x + t * end.x);
	origin.y = ((1 - t)*origin.y + t * end.y);

	return origin;
}

#endif