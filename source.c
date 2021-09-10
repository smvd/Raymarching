#include <Raylib.h>
#include <Time.h>
#include <StdLib.h>
#include "Constants.c"
#include "Client.c"
#include "Circle.c"
#include "Raymarching.c"

#define RANDOM(a, b) rand() % b + a

int main()
{
    // Setup
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE);
    SetTargetFPS(RENDER_FPS);
    srand(time(0));

    CLIENT user = NewClient();

    CIRCLE world[WORLD_SIZE];

    for (int i = 0; i < WORLD_SIZE; i++)
    {
        world[i].pos.x = RANDOM(0, WINDOW_WIDTH);
        world[i].pos.y = RANDOM(0, WINDOW_HEIGHT);
        world[i].radius = RANDOM(WORLD_MIN_RADIUS, WORLD_MAX_RADIUS);

        if (CircleCircleCollision(world[i], (CIRCLE){user.pos, user.radius}))
        {
            i--;
        }
    }

    // Main loop
    while (!WindowShouldClose())
    {
        BeginDrawing();

        user = UpdateClient(user);

        DrawClient(user);
        DrawWorld(world);

        Raymarching(user, world);

        ClearBackground(BLACK);
        DrawFPS(RENDER_FPS_X, RENDER_FPS_Y);

        EndDrawing();
    }

    // Cleanup
    CloseWindow();
    return 0;
}