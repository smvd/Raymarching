#include <Raylib.h>
#include "Constants.c"
#include "Vector.c"

#ifndef CLIENT_HEADER
#define CLIENT_HEADER

typedef struct
{
    Vector2 pos;
    Vector2 mouse;
    float radius;
}CLIENT;

CLIENT NewClient()
{
    CLIENT client;

    client.pos.x = WINDOW_WIDTH / 2;
    client.pos.y = WINDOW_HEIGHT / 2;
    client.mouse = GetMousePosition();
    client.radius = DEFAULT_RADIUS;

    return client;
}

CLIENT UpdateClient(CLIENT client)
{
    client.mouse = GetMousePosition();

    client.mouse = MoveAlongVector(client.pos, client.mouse, WINDOW_WIDTH);

    return client;
}

void DrawClient(CLIENT client)
{
    DrawCircleV(client.pos, client.radius, RED);
    DrawLineEx(client.pos, client.mouse, DEFAULT_LINE_THICKNESS, WHITE);
}

#endif