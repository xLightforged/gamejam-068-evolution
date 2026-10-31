#ifndef GFX_H
#define GFX_H

#include "raylib.h"
#include "game.h"

// sizes
static const float  BLOB_SIZE           = 20.0f;
static const float  BLOB_CHILD_SIZE     = 12.0f;
static const float  FOOD_SIZE           = 6.0f;
static const float  BUSH_SIZE           = 22.0f;
static const float  TREE_SIZE           = 40.0f;

// thought bubble
static const float  THOUGHT_SIZE        = 12.0f;
static const float  THOUGHT_HEIGHT      = 26.0f;

// shared body and eyes for both blobs
inline void draw_blob_shape(Vector2 pos, float size, Color color)
{
    DrawEllipse((int)pos.x, (int)pos.y, size, size * 0.8f, color);
    DrawCircle((int)(pos.x - size * 0.35f), (int)(pos.y - size * 0.2f), size * 0.12f, BLACK);
    DrawCircle((int)(pos.x + size * 0.35f), (int)(pos.y - size * 0.2f), size * 0.12f, BLACK);
}

// pos is the middle of the blob
inline void draw_blob(Vector2 pos)
{
    draw_blob_shape(pos, BLOB_SIZE, BLUE);
}

// a smaller, lighter blob
inline void draw_blob_child(Vector2 pos)
{
    draw_blob_shape(pos, BLOB_CHILD_SIZE, SKYBLUE);
}

// pos is the middle of the blob, size is its size
// draws a small thought bubble above it with what it is doing
inline void draw_thought(Vector2 pos, float size, Action action)
{
    float top = pos.y - size * 0.8f;
    Vector2 bubble = {pos.x, top - THOUGHT_HEIGHT};

    // the little trail of circles leading up to the bubble
    DrawCircleV({pos.x, top - 5.0f}, 2.0f, WHITE);
    DrawCircleV({pos.x, top - 11.0f}, 3.5f, WHITE);

    // the bubble itself
    DrawCircleV(bubble, THOUGHT_SIZE, WHITE);
    DrawCircleLines((int)bubble.x, (int)bubble.y, THOUGHT_SIZE, DARKGRAY);

    // wander: three dots
    if (action == ACT_WANDER)
    {
        DrawCircleV({bubble.x - 5.0f, bubble.y}, 1.8f, DARKGRAY);
        DrawCircleV({bubble.x, bubble.y}, 1.8f, DARKGRAY);
        DrawCircleV({bubble.x + 5.0f, bubble.y}, 1.8f, DARKGRAY);
    }

    // food: a red berry with a stem
    if (action == ACT_FOOD)
    {
        DrawCircleV({bubble.x, bubble.y + 1.0f}, 5.0f, RED);
        DrawRectangle((int)bubble.x - 1, (int)bubble.y - 8, 2, 4, DARKGREEN);
    }

    // mate: a red heart
    if (action == ACT_MATE)
    {
        DrawCircleV({bubble.x - 3.0f, bubble.y - 2.0f}, 3.5f, RED);
        DrawCircleV({bubble.x + 3.0f, bubble.y - 2.0f}, 3.5f, RED);
        DrawTriangle({bubble.x - 6.5f, bubble.y - 1.0f}, {bubble.x, bubble.y + 6.0f}, {bubble.x + 6.5f, bubble.y - 1.0f}, RED);
    }
}

// pos is the middle of the food
inline void draw_food(Vector2 pos)
{
    DrawCircle((int)pos.x, (int)pos.y, FOOD_SIZE, RED);
}

// pos is the middle of the bush
inline void draw_bush(Vector2 pos)
{
    DrawCircle((int)(pos.x - BUSH_SIZE * 0.5f), (int)pos.y, BUSH_SIZE * 0.7f, DARKGREEN);
    DrawCircle((int)(pos.x + BUSH_SIZE * 0.5f), (int)pos.y, BUSH_SIZE * 0.7f, DARKGREEN);
    DrawCircle((int)pos.x, (int)(pos.y - BUSH_SIZE * 0.4f), BUSH_SIZE * 0.8f, GREEN);
}

// pos is the bottom of the trunk
inline void draw_tree(Vector2 pos)
{
    DrawRectangle((int)(pos.x - TREE_SIZE * 0.1f), (int)(pos.y - TREE_SIZE), (int)(TREE_SIZE * 0.2f), (int)TREE_SIZE, BROWN);
    DrawCircle((int)pos.x, (int)(pos.y - TREE_SIZE * 1.3f), TREE_SIZE * 0.7f, DARKGREEN);
    DrawCircle((int)(pos.x - TREE_SIZE * 0.4f), (int)(pos.y - TREE_SIZE), TREE_SIZE * 0.45f, DARKGREEN);
    DrawCircle((int)(pos.x + TREE_SIZE * 0.4f), (int)(pos.y - TREE_SIZE), TREE_SIZE * 0.45f, DARKGREEN);
}

#endif