// raylib
#include "raylib.h"
#include "raymath.h"

// game files
#include "config.h"
#include "gfx/gfx.h"

int main()
{
    // open window
    InitWindow(BASE_WIDTH, BASE_HEIGHT, BASE_TITLE);
    SetTargetFPS(BASE_FPS);

    // game loop
    bool running = true;
    while (!WindowShouldClose() && running)
    {
        BeginDrawing();
        
        // nothing
        
        EndDrawing();
    }
    CloseWindow();
    return 0;
}