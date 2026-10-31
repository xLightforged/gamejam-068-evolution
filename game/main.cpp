#include "raylib.h"
#include "define.h"
#include "game.h"
#include "gfx.h"
#include <vector>
using namespace std;

Vector2 random_pos()
{
    float x = (float)GetRandomValue(WORLD_MARGIN, GAME_WIDTH - WORLD_MARGIN);
    float y = (float)GetRandomValue(WORLD_MARGIN, GAME_HEIGHT - WORLD_MARGIN);
    return {x, y};
}

World world;
vector<Blob> blobs;

void spawn()
{
    SetRandomSeed(WORLD_SEED);

    for (int num = 0; num < WORLD_TREES; ++num)
        world.add(OBJ_TREE, random_pos());
    for (int num = 0; num < WORLD_BUSHES; ++num)
        world.add(OBJ_BUSH, random_pos());

    for (int num = 0; num < START_BLOBS; ++num)
        blobs.push_back(Blob(random_pos(), 30.0f));
}

void spawn_food_around(Vector2 center, int amount)
{
    for (int num = 0; num < amount; ++num)
    {
        Vector2 spot = Vector2Add(center, {random_float(-FOOD_NEAR_RANGE, FOOD_NEAR_RANGE), random_float(-FOOD_NEAR_RANGE, FOOD_NEAR_RANGE)});
        spot.x = Clamp(spot.x, WORLD_MARGIN, GAME_WIDTH - WORLD_MARGIN);
        spot.y = Clamp(spot.y, WORLD_MARGIN, GAME_HEIGHT - WORLD_MARGIN);
        world.add(OBJ_FOOD, spot);
    }
}

void spawn_food()
{
    int total = world.size();
    for (int num = 0; num < total; ++num)
    {
        if (world.get_type(num) == OBJ_TREE)
            spawn_food_around(world.get_pos(num), GetRandomValue(TREE_FOOD_MIN, TREE_FOOD_MAX));
        if (world.get_type(num) == OBJ_BUSH)
            spawn_food_around(world.get_pos(num), GetRandomValue(BUSH_FOOD_MIN, BUSH_FOOD_MAX));
    }
    for (int num = 0; num < RANDOM_FOOD; ++num)
        world.add(OBJ_FOOD, random_pos());
}

int main()
{
    // WINDOW
    InitWindow(GAME_WIDTH, GAME_HEIGHT, GAME_TITLE);
    SetTargetFPS(BASE_FPS);
    SetExitKey(KEY_NULL);

    // SETUP
    float food_timer = FOOD_SPAWN_TIME;
    spawn();
    spawn_food();

    // GAME
    while (!WindowShouldClose())
    {
        float dt = GetFrameTime();
        food_timer -= dt;
        if (food_timer <= 0.0f)
        {
            food_timer = FOOD_SPAWN_TIME;
            spawn_food();
        }
        for (int num = 0; num < (int)blobs.size(); ++num)
        {
            blobs[num].update(dt);
            behavior(blobs[num], blobs, world, dt);
        }
        for (int num = (int)blobs.size() - 1; num >= 0; --num)
        {
            if (blobs[num].is_dead())
                blobs.erase(blobs.begin() + num);
        }
        BeginDrawing();
        ClearBackground(LIGHTGRAY);
        for (int num = 0; num < world.size(); ++num)
        {
            if (world.get_type(num) == OBJ_TREE)
                draw_tree(world.get_pos(num));
            if (world.get_type(num) == OBJ_BUSH)
                draw_bush(world.get_pos(num));
            if (world.get_type(num) == OBJ_FOOD)
                draw_food(world.get_pos(num));
        }
        for (Blob& blob : blobs)
        {
            if (blob.is_adult())
                draw_blob(blob.get_pos());
            else
                draw_blob_child(blob.get_pos());
        }
        for (Blob& blob : blobs)
        {
            if (blob.is_adult())
                draw_thought(blob.get_pos(), BLOB_SIZE, blob.get_action());
            else
                draw_thought(blob.get_pos(), BLOB_CHILD_SIZE, blob.get_action());
        }
        EndDrawing();
    }

    CloseWindow();
    return 0;
}