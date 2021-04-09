#ifndef __GAME_OBJECT__
#define __GAME_OBJECT__

#include <stdint.h>
#include <stdbool.h>

typedef struct
{
    unsigned int x,y;
    unsigned int w,h;
    unsigned int color;
    bool hidden;
    
} game_object;

void game_object_init(game_object* object, unsigned int x, unsigned int y, unsigned int w, unsigned int h, unsigned int color)
{
    object->x = x;
    object->y = y;
    object->w = w;
    object->h = h;
    object->color = color;
    object->hidden = false;
}

#endif // __GAME_OBJECT__