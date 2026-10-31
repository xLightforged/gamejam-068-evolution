#ifndef DEFINE_H
#define DEFINE_H

// window
#define GAME_WIDTH          1600
#define GAME_HEIGHT         900
#define GAME_TITLE          "Blobvolution"
#define BASE_FPS            60

// world
#define WORLD_SEED          20060418 // [test seed]
#define WORLD_MARGIN        80
#define WORLD_TREES         12
#define WORLD_BUSHES        20
#define START_BLOBS         10

// food
#define FOOD_SPAWN_TIME     20.0f
#define FOOD_NEAR_RANGE     60.0f
#define TREE_FOOD_MIN       2
#define TREE_FOOD_MAX       4
#define BUSH_FOOD_MIN       1
#define BUSH_FOOD_MAX       2
#define RANDOM_FOOD         0

// blobs
#define SEARCH_RANGE        400.0f
#define EAT_RANGE           20.0f
#define BREED_RANGE         20.0f
#define WANDER_RANGE        120.0f
#define BREED_COST          0.3f
#define BREED_COOLDOWN      0.0f
#define THINK_TIME          3.0f

#endif // DEFINE_H