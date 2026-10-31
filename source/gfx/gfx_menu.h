#ifndef GFX_MENU_H
#define GFX_MENU_H

// raylib
#include "raylib.h"
// includes
#include "constants.h"

// ##############################
// █▄ ▄█ █▀▀▀ █▄  █ █   █
// █ ▀ █ █▀▀  █ ▀▄█ █   █
// ▀   ▀ ▀▀▀▀ ▀   ▀  ▀▀▀ 
// ##############################

// ####################
// █▀▄ █▀▀ █▀▀ █▀▀
// █▄▀ ██▄ █▀  ▄▄█
// ####################

// BACKGROUND
// ====================

// TITLE
// ====================
static const float     TITLE_X          = 100.0f;
static const float     TITLE_Y          = 120.0f;
static const float     TITLE_ORIGIN_X   = 0.0f;
static const float     TITLE_ORIGIN_Y   = 0.0f;
static const float     TITLE_TILT       = -6.0f;
static const float     TITLE_SIZE       = 90.0f;
static const float     TITLE_SPACING    = 4.0f;

// BUTTONS
// ====================
static const int       BUTTON_TEXT_SIZE = 36;
// Play Button
static const char*     PLAY_TEXT        = "Play";
static const float     PLAY_X           = 100.0f;
static const float     PLAY_Y           = 400.0f;
static const float     PLAY_WIDTH       = 300.0f;
static const float     PLAY_HEIGHT      = 80.0f;
static const Rectangle PLAY_BOX         = {PLAY_X, PLAY_Y, PLAY_WIDTH, PLAY_HEIGHT};
// Exit Button
static const char*     EXIT_TEXT        = "Exit";
static const float     EXIT_X           = 100.0f;
static const float     EXIT_Y           = 500.0f;
static const float     EXIT_WIDTH       = 300.0f;
static const float     EXIT_HEIGHT      = 80.0f;
static const Rectangle EXIT_BOX         = {EXIT_X, EXIT_Y, EXIT_WIDTH, EXIT_HEIGHT};

// ####################
// █▀▀ █ █ █▄ █ █▀▀ █▀▀
// █▀  █▄█ █ ▀█ █▄▄ ▄▄█
// ####################

inline void draw_background()
{
    ClearBackground(COLOR_BACKGROUND);
}

inline void draw_game_title()
{
    DrawTextPro(GetFontDefault(), GAME_TITLE, {TITLE_X, TITLE_Y}, {TITLE_ORIGIN_X, TITLE_ORIGIN_Y}, TITLE_TILT, TITLE_SIZE, TITLE_SPACING, COLOR_GAME_TITLE);
}

inline bool draw_button(const char* text, Rectangle box, Vector2 mouse, bool clicked)
{
    int text_width = MeasureText(text, BUTTON_TEXT_SIZE);
    int text_x = (int)(box.x + (box.width - text_width) / 2);
    int text_y = (int)(box.y + (box.height - BUTTON_TEXT_SIZE) / 2);
    bool hover = CheckCollisionPointRec(mouse, box);
    Color color = COLOR_BUTTON_NORMAL;
    if (hover)
        color = COLOR_BUTTON_HOVER;
    DrawText(text, text_x, text_y, BUTTON_TEXT_SIZE, color);
    return hover && clicked;
}

inline int draw_menu(Vector2 mouse, bool clicked)
{
    int choice = MENU_CHOICE_NONE;
    draw_background();
    draw_game_title();
    if (draw_button(PLAY_TEXT, PLAY_BOX, mouse, clicked))
        choice = MENU_CHOICE_PLAY;
    if (draw_button(EXIT_TEXT, EXIT_BOX, mouse, clicked))
        choice = MENU_CHOICE_EXIT;
    return choice;
}

#endif