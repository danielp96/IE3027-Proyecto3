#ifndef __GAME_OBJECT__
#define __GAME_OBJECT__

#include <stdint.h>
#include <stdbool.h>

#include "map.h"

#ifndef __TIMAGE_STRUCT__
#define __TIMAGE_STRUCT__

typedef struct
{
    const uint8_t *data;
    uint16_t w;
    uint16_t h;
} tImage;

#endif // __TIMAGE_STRUCT__


enum SpriteID {SIDE1, SIDE2, UP1, UP2, DOWN1, DOWN2};
enum Direction {UP, DOWN, LEFT, RIGHT};


typedef struct
{
    uint16_t x,y;
    uint16_t w,h;

    uint16_t max_x, min_x;
    uint16_t max_y, min_y;

    bool enable_x, enable_y;

    bool walk_sprite; // which walking sprite show
    bool x_flip, y_flip;

    tImage** sprite_list; 
    uint8_t sprite_index;

    Direction direction;
    uint8_t steps;
    uint8_t steps_max; // amount of steps before changing sprite

    Node* node;

    bool hidden;

    
} game_object;


void game_object_init(game_object* self, uint16_t x, uint16_t y, tImage* sprite_list[])
{
    self->x = x;
    self->y = y;

    self->enable_x = false;
    self->enable_y = false;

    self->w = sprite_list[0]->w;
    self->h = sprite_list[0]->h;

    self->max_x = 0;
    self->min_x = 0;
    self->max_y = 0;
    self->min_y = 0;

    self->x_flip = false;
    self->y_flip = false;

    self->sprite_list = sprite_list;
    self->sprite_index = 0;

    self->hidden = false;

    self->direction = RIGHT;
    self->steps = 0;
    self->steps_max = 5;

    self->node = NULL;
}

void game_object_add_x(game_object* self, int8_t x, uint16_t max, uint16_t min)
{
    int temp = self->x + x;

    if (temp > (max - self->w))
    {
        self->x = max - self->w;
        return;
    }

    if (temp < min)
    {
        self->x = min;
        return;
    }

    self->x = temp;
}

void game_object_add_y(game_object* self, int8_t y, uint16_t max, uint16_t min)
{
    int temp = self->y + y;

    if (temp > (max - self->w))
    {
        self->y = max - self->w;
        return;
    }

    if (temp < min)
    {
        self->y = min;
        return;
    }

    self->y = temp;
}

void game_object_set_sprite(game_object* self, SpriteID id, bool x_flip, bool y_flip)
{
    self->sprite_index = id;

    self->w = self->sprite_list[id]->w;
    self->h = self->sprite_list[id]->h;

    self->x_flip = x_flip;
    self->y_flip = y_flip;
}

void game_object_direction(game_object* self, Direction d)
{
    self->direction = d;
}

void game_object_move(game_object* self, Direction d)
{
    game_object_direction(self, d);
    switch (d)
    {
        case UP:
            game_object_add_y(self, -1, self->max_y, self->min_y);
            break;

        case DOWN:
            game_object_add_y(self, 1, self->max_y, self->min_y);
            break;

        case LEFT:
            game_object_add_x(self, -1, self->max_x, self->min_x);
            break;

        case RIGHT:
            game_object_add_x(self, 1, self->max_x, self->min_x);
            break;
    }

    // for now this will be here
    self->steps++;

    if (self->steps > self->steps_max)
    {
        self->steps = 0;
        self->walk_sprite = !self->walk_sprite;
    }
}

void game_object_update_index(game_object* self)
{
    SpriteID tempID = SIDE1;
    bool temp_x_flip = false;
    bool temp_y_flip = false;

    switch (self->direction)
    {
        case UP:
            tempID = self->walk_sprite?UP1:UP2;
            temp_x_flip = false;
            temp_y_flip = false;
            game_object_set_sprite(self, tempID, temp_x_flip, temp_y_flip);
            break;

        case DOWN:
            tempID = self->walk_sprite?DOWN1:DOWN2;
            temp_x_flip = false;
            temp_y_flip = false;
            game_object_set_sprite(self, tempID, temp_x_flip, temp_y_flip);
            break;

        case LEFT:
            tempID = self->walk_sprite?SIDE1:SIDE2;
            temp_x_flip = true;
            temp_y_flip = false;
            game_object_set_sprite(self, tempID, temp_x_flip, temp_y_flip);
            break;

        case RIGHT:
            tempID = self->walk_sprite?SIDE1:SIDE2;
            temp_x_flip = false;
            temp_y_flip = false;
            game_object_set_sprite(self, tempID, temp_x_flip, temp_y_flip);
            break;
    }
}

void game_object_set_node(game_object* self, Node* n)
{
    self->node = n;

    self->enable_x = true;
    self->enable_y = true;

    if (n->up != NULL)
    {
        self->min_y = n->up->y;
    }
    else
    {
        self->min_y = n->y;
    }

    if (n->down != NULL)
    {
        self->max_y = n->down->y + self->h;
    }
    else
    {
        self->max_y = n->y + self->h;
    }


    if (n->left != NULL)
    {
        self->min_x = n->left->x;
    }
    else
    {
        self->min_x = n->x;
    }

    if (n->right != NULL)
    {
        self->max_x = n->right->x + self->w;
    }
    else
    {
        self->max_x = n->x + self->w;
    }
}

#endif // __GAME_OBJECT__