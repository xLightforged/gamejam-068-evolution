// raylib
#include "raylib.h"

// game files
#include "config.h"
#include "gfx/gfx.h"

int main()
{
    // open window
    InitWindow(BASE_WIDTH, BASE_HEIGHT, GAME_TITLE);
    SetTargetFPS(BASE_FPS);
    SetExitKey(KEY_NULL);

    // game running?
    bool running = true;
    
    // MENU
    while (!WindowShouldClose() && running)
    {
        Vector2 mouse_pos = GetMousePosition();
        bool mouse_clicked = IsMouseButtonPressed(MOUSE_BUTTON_LEFT);

        BeginDrawing();
        int choice = draw_menu(mouse_pos, mouse_clicked);
        EndDrawing();

        if (choice == MENU_CHOICE_PLAY)
            break;
        if (choice == MENU_CHOICE_EXIT)
            running = false;
    }

    // GAME
    while (!WindowShouldClose() && running)
    {
        BeginDrawing();
        // GAME HAPPENS HERE
        EndDrawing();
    }

    // Exit
    CloseWindow();
    return 0;
}