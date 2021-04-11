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

void game_object_add_x(game_object* object, int8_t x)
{
    int temp = object->x + x;

    if (temp > (320 - object->w))
    {
        object->x = 320 - object->w;
        return;
    }

    if (temp < 0)
    {
        object->x = 0;
        return;
    }

    object->x = temp;
}

void game_object_add_y(game_object* object, int8_t y)
{
    int temp = object->y + y;

    if (temp > (240 - object->w))
    {
        object->y = 240 - object->w;
        return;
    }

    if (temp < 0)
    {
        object->y = 0;
        return;
    }

    object->y = temp;
}

#endif // __GAME_OBJECT__