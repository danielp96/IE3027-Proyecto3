#ifndef __GAME_OBJECT__
#define __GAME_OBJECT__

#include <stdint.h>
#include <stdbool.h>

#ifndef __TIMAGE_STRUCT__
#define __TIMAGE_STRUCT__

typedef struct
{
    const uint8_t *data;
    uint16_t w;
    uint16_t h;
} tImage;

#endif // __TIMAGE_STRUCT__

typedef struct
{
    uint16_t x,y;
    uint16_t w,h;
    tImage* sprite; 
    bool hidden;
    
} game_object;

void game_object_init(game_object* object, uint16_t x, uint16_t y, tImage* sprite)
{
    object->x = x;
    object->y = y;
    object->w = sprite->w;
    object->h = sprite->h;
    object->sprite = sprite;
    object->hidden = false;
}

void game_object_add_x(game_object* object, int8_t x, uint16_t max, uint16_t min)
{
    int temp = object->x + x;

    if (temp > (max - object->w))
    {
        object->x = max - object->w;
        return;
    }

    if (temp < min)
    {
        object->x = min;
        return;
    }

    object->x = temp;
}

void game_object_add_y(game_object* object, int8_t y, uint16_t max, uint16_t min)
{
    int temp = object->y + y;

    if (temp > (max - object->w))
    {
        object->y = max - object->w;
        return;
    }

    if (temp < min)
    {
        object->y = min;
        return;
    }

    object->y = temp;
}

#endif // __GAME_OBJECT__