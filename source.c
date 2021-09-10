/*   <++++[PRE-PROCESSORS]++++>    */
    // Headers
    #include <Raylib.h> // https://www.raylib.com
    #include <Stdlib.h> // https://www.tutorialspoint.com/c_standard_library/stdlib_h.htm
    #include <Time.h>   // https://www.tutorialspoint.com/c_standard_library/time_h.htm
    #include <Math.h>   // https://www.tutorialspoint.com/c_standard_library/math_h.htm

    // Window config
    #define WINDOW_TITLE  "Raymarching | Eclips-Coding"
    #define WINDOW_WIDTH  1000
    #define WINDOW_HEIGHT 1000

    // Render config
    #define RENDER_FPS 60
    #define RENDER_FPS_X 10
    #define RENDER_FPS_Y 10

    // World config
    #define WORLD_SIZE 20
    #define WORLD_MIN_RADIUS 10
    #define WORLD_MAX_RADIUS 100

    // Default constants
    #define DEFAULT_USER_RADIUS 10
    #define DEFAULT_LINE_THICKNESS 1
    #define DEFAULT_USER_ZONE 200
    #define DEFAULT_POINT_RADIUS 4
    #define DEFAULT_MINIMUM_RAY_LENGTH 2

    // Macros
    #define RANDOM(a, b) rand() % b + a // random number from a to b

/*       <++++[STRUCTS]++++>       */
    // Client
    typedef struct
    {
        Vector2 pos;
        Vector2 mouse;
        float radius;
    }CLIENT;

    // Circle
    typedef struct
    {
        Vector2 pos;
        float radius;
    }CIRCLE;

/* <++++[FUNCTION PROTOTYPES]++++> */
    // Circle
    int   CircleCircleCollision (CIRCLE a, CIRCLE b);
    float SDFCircle             (Vector2 s, CIRCLE c);

    // Vector
    Vector2 MoveAlongVector (Vector2 origin, Vector2 end, float distance);
    float   VectorDistance  (Vector2 origin, Vector2 end);

    // Render
    void Raymarching (CLIENT user, CIRCLE world[WORLD_SIZE]);

/*        <++++[MAIN]++++>         */
    // Main entry point
    int main()
    {
        // Make window
        InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE);

        // Lock the FPS to make it more smooth and not take up to many resources
        SetTargetFPS(RENDER_FPS);

        // Seed the random number generator (https://en.wikipedia.org/wiki/Pseudorandom_number_generator)
        srand(time(0)); 

        // Variable setup
        CLIENT user = {{WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2}, GetMousePosition(), DEFAULT_USER_RADIUS};
        CIRCLE world[WORLD_SIZE];

        // Loop over each slot in the world
        for (int i = 0; i < WORLD_SIZE; i++)
        {
            // Give the circle random properties
            world[i].pos.x = RANDOM(0, WINDOW_WIDTH);
            world[i].pos.y = RANDOM(0, WINDOW_HEIGHT);
            world[i].radius = RANDOM(WORLD_MIN_RADIUS, WORLD_MAX_RADIUS);

            // If it overlaps with the user
            if (CircleCircleCollision(world[i], (CIRCLE){user.pos, user.radius}) || CircleCircleCollision(world[i], (CIRCLE){user.pos, DEFAULT_USER_ZONE}))
            {
                // Try again
                i--;
            }
        }

        // Main loop
        while (!WindowShouldClose())
        {
            BeginDrawing();

            // Get the mouse position
            user.mouse = GetMousePosition();

            // Move the mouse position out from the center
            user.mouse = MoveAlongVector(user.pos, user.mouse, WINDOW_WIDTH);

            // Draw the user
            DrawCircleV(user.pos, user.radius, RED);

            // Loop over each circle in the world
            for (int i = 0; i < WORLD_SIZE; i++)
            {
                // Draw the circle
                DrawCircleV(world[i].pos, world[i].radius, DARKBLUE);
            }

            // Run the raymarching algorithm
            Raymarching(user, world);

            // Set the background
            ClearBackground(BLACK);

            // Show the current FPS
            DrawFPS(RENDER_FPS_X, RENDER_FPS_Y);

            EndDrawing();
        }

        // Cleanup
        CloseWindow();
        return 0;
    }

/*      <++++[FUNCTIONS]++++>      */
    // Circle 
    int CircleCircleCollision(CIRCLE a, CIRCLE b) // https://www.petercollingridge.co.uk/tutorials/computational-geometry/circle-circle-intersections/
    {
        // Find the X, Y & radius difference
        a.pos.x -= b.pos.x;
        a.pos.y -= b.pos.y;
        a.radius -= b.radius;

        // If the XY difference squared is less then the radius difference squared we dont have overlap
        return a.pos.x * a.pos.x + a.pos.y * a.pos.y <= a.radius * a.radius;
    }

    float SDFCircle(Vector2 s, CIRCLE c) // https://www.iquilezles.org/www/articles/distfunctions2d/distfunctions2d.htm
    {
        return VectorDistance(s, c.pos) - c.radius; // The distance from the circle is the distance between the point minus the radius
    }
    
    // Vector
    float VectorDistance(Vector2 origin, Vector2 end) // https://www.w3resource.com/c-programming-exercises/basic-declarations-and-expressions/c-programming-basic-exercises-15.php
    {
        return sqrt(pow(end.x - origin.x, 2) + pow(end.y - origin.y, 2)); // Find the x and y components then use pythagoras to find the distance
    }

    Vector2 MoveAlongVector(Vector2 origin, Vector2 end, float distance) // https://math.stackexchange.com/questions/175896/finding-a-point-along-a-line-a-certain-distance-away-from-another-point
    {
        float fraction = distance / VectorDistance(origin, end); // Find the fraction the distance will be

        origin.x = ((1 - fraction)*origin.x + fraction * end.x); // Calculate the X component based on the fraction
        origin.y = ((1 - fraction)*origin.y + fraction * end.y); // Calculate the y component based on the fraction

        return origin; // Return the new point
    }

    // Render
    void Raymarching(CLIENT user, CIRCLE world[WORLD_SIZE]) // https://medium.com/@ArmstrongCS/raymarching-1-the-basics-d6f3e70fb430
    {
        float currentDistance = WINDOW_WIDTH; // Variable for the current distance
        float distance = WINDOW_WIDTH; // Variable for the shortest distance

        Vector2 origin = user.pos; // Point from wich to run the calculation

        // While you havn't collided and are still on screen
        while (distance >= DEFAULT_MINIMUM_RAY_LENGTH && origin.x < WINDOW_WIDTH && origin.x > 0 && origin.y < WINDOW_HEIGHT && origin.y > 0)
        {
            distance = WINDOW_WIDTH; // Max out the distance
            for (int i = 0; i < WORLD_SIZE; i++) // Loop over each segment in the world
            {
                currentDistance = SDFCircle(origin, world[i]); // Find the distance to the circle

                // min distance & currentDistance
                if (currentDistance < distance)
                {
                    distance = currentDistance;
                }
            }

            // Visualize the output
            DrawCircleLines(origin.x, origin.y, distance, WHITE);
            DrawCircleV(origin, DEFAULT_POINT_RADIUS, RED);

            // March along the ray
            origin = MoveAlongVector(origin, user.mouse, distance);
        }

        // Visualize the ray direction
        DrawLineEx(user.pos, origin, DEFAULT_LINE_THICKNESS, GREEN);
    }