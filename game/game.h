#ifndef GAME_H
#define GAME_H

// includes
#include "define.h"
#include "raylib.h"
#include "raymath.h"
#include <vector>

// random float between low and high
inline float random_float(float low, float high)
{return low + GetRandomValue(0, 10000) / 10000.0f * (high - low);}

enum ObjectType {OBJ_TREE, OBJ_BUSH, OBJ_FOOD};
struct Object {ObjectType type; Vector2 pos;};

struct World
{
    private:
        std::vector<Object> objects;

    public:
        void add(ObjectType type, Vector2 pos)
        {objects.push_back({type, pos});}

        // removes the object at exactly this spot
        void remove(Vector2 pos)
        {
            for (int num = 0; num < (int)objects.size(); ++num)
            {
                if (Vector2Equals(objects[num].pos, pos))
                {
                    objects.erase(objects.begin() + num);
                    return;
                }
            }
        }

        int size()
        {return (int)objects.size();}

        ObjectType get_type(int index)
        {return objects[index].type;}

        Vector2 get_pos(int index)
        {return objects[index].pos;}

        int count(ObjectType type)
        {
            int total = 0;
            for (Object& object : objects)
                if (object.type == type)
                    ++total;
            return total;
        }

        Vector2 nearest(ObjectType type, Vector2 from, float range)
        {
            Vector2 found = {-1.0f, -1.0f};
            float best = range;
            for (Object& object : objects)
            {
                if (object.type != type)
                    continue;
                float dist = Vector2Distance(from, object.pos);
                if (dist < best)
                {
                    best = dist;
                    found = object.pos;
                }
            }
            return found;
        }
};

enum Action {ACT_WANDER, ACT_FOOD, ACT_MATE};

struct Blob
{
    private:
        Vector2 pos;
        Vector2 target;
        float hunger = 10.0f;
        float food = 0.0f;
        float adult = 30.0f;
        float lifespan = 120.0f;
        float age = 0.0f;
        float breed_timer = 0.0f;
        float think_timer = 0.0f;
        Action action = ACT_WANDER;

    public:
        // 2 blobs fucked and made a child. the wonder
        Blob(Blob& father, Blob& mother)
        {
            float father_mod = 0.5f;
            float mother_mod = 0.5f;
            float change = GetRandomValue(-50, 50) / 100.0f;
            pos = Vector2Scale(Vector2Add(father.pos, mother.pos), 0.5f);
            target = pos;
            hunger = father.hunger * father_mod + mother.hunger * mother_mod + change;
            if (hunger < 1.0f) hunger = 1.0f;
            food = hunger * 0.2f;
        }
        Blob(Vector2 spawn_pos, float spawn_age)
        {pos = spawn_pos; target = spawn_pos; age = spawn_age; food = hunger * 0.2f;}
        Blob(Vector2 spawn_pos)
        {pos = spawn_pos; target = spawn_pos; food = hunger * 0.2f;}
        ~Blob()
        {}

        Vector2 get_pos()
        {return pos;}
        Vector2 get_target()
        {return target;}
        void set_target(Vector2 new_target)
        {target = new_target;}
        bool at_target()
        {return Vector2Distance(pos, target) < 2.0f;}
        void move_pos(Vector2 move_to, float dt)
        {pos = Vector2MoveTowards(pos, move_to, 60.0f * dt);}

        float get_food()
        {return food;}
        void eat(float amount)
        {food += amount; if (food > hunger * 1.2f) food = hunger * 1.2f;}
        void spend_food(float amount)
        {food -= amount;}

        void update(float dt)
        {
            age += dt;
            food -= 0.5f * dt;
            if (breed_timer > 0.0f) breed_timer -= dt;
            if (think_timer > 0.0f) think_timer -= dt;
        }

        bool is_hungry()
        {return food < hunger * 0.8f;}
        bool is_adult()
        {return age >= adult;}
        bool can_breed()
        {return is_adult() && !is_hungry() && breed_timer <= 0.0f;}
        void start_cooldown()
        {breed_timer = BREED_COOLDOWN;}
        bool is_dead()
        {return age >= lifespan || food < -0.1f * hunger;}

        bool needs_think()
        {return think_timer <= 0.0f;}
        void start_think()
        {think_timer = THINK_TIME;}
        Action get_action()
        {return action;}
        void set_action(Action new_action)
        {action = new_action;}
};

inline void behavior(Blob& blob, std::vector<Blob>& blobs, World& world, float dt)
{
    // decide what to do, then stick with it for a second
    if (blob.needs_think())
    {
        if (blob.is_hungry())
            blob.set_action(ACT_FOOD);
        else if (blob.can_breed())
            blob.set_action(ACT_MATE);
        else
            blob.set_action(ACT_WANDER);
        blob.start_think();
    }

    // hungry: find the nearest food, walk to it, eat it
    if (blob.get_action() == ACT_FOOD && blob.is_hungry())
    {
        Vector2 food_pos = world.nearest(OBJ_FOOD, blob.get_pos(), SEARCH_RANGE);
        if (food_pos.x >= 0.0f)
        {
            if (Vector2Distance(blob.get_pos(), food_pos) < EAT_RANGE)
            {
                blob.eat(1000.0f);
                world.remove(food_pos);
            }
            else
                blob.move_pos(food_pos, dt);
            return;
        }
    }

    // can breed: find the nearest mate that can breed
    if (blob.get_action() == ACT_MATE && blob.can_breed())
    {
        int mate = -1;
        float best = SEARCH_RANGE;
        for (int num = 0; num < (int)blobs.size(); ++num)
        {
            if (&blobs[num] == &blob || !blobs[num].can_breed())
                continue;
            float dist = Vector2Distance(blob.get_pos(), blobs[num].get_pos());
            if (dist < best)
            {
                best = dist;
                mate = num;
            }
        }
        if (mate != -1)
        {
            if (best < BREED_RANGE)
            {
                blob.spend_food(blob.get_food() * BREED_COST);
                blobs[mate].spend_food(blobs[mate].get_food() * BREED_COST);
                blob.start_cooldown();
                blobs[mate].start_cooldown();
                Blob child(blob, blobs[mate]);
                blobs.push_back(child);
            }
            else
                blob.move_pos(blobs[mate].get_pos(), dt);
            return;
        }
    }

    // nothing else to do: wander
    if (blob.at_target())
    {
        Vector2 spot = Vector2Add(blob.get_pos(), {random_float(-WANDER_RANGE, WANDER_RANGE), random_float(-WANDER_RANGE, WANDER_RANGE)});
        spot.x = Clamp(spot.x, WORLD_MARGIN, GAME_WIDTH - WORLD_MARGIN);
        spot.y = Clamp(spot.y, WORLD_MARGIN, GAME_HEIGHT - WORLD_MARGIN);
        blob.set_target(spot);
    }
    blob.move_pos(blob.get_target(), dt);
}

#endif