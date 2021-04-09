#ifndef __HARDWARE_ABSTRACTION_LAYER__
#define __HARDWARE_ABSTRACTION_LAYER__

#include <Arduino.h>

#include <stdint.h>
#include <stdbool.h>

enum EventType {UP, DOWN, LEFT,  RIGHT, SW1, SW2};

typedef struct Events
{
    bool UP;
    bool DOWN;
    bool LEFT;
    bool RIGHT;
    bool SW1;
    bool SW2;

} Event_struct;

Event_struct events;

// adjust deadzone as required
const unsigned int DEAD_ZONE = 200;
const unsigned int MID_POINT = 2048;

void input_init()
{
    pinMode(PF_4, INPUT_PULLUP);
    pinMode(PF_0, INPUT_PULLUP);
    pinMode(A0, INPUT);
    pinMode(A1, INPUT);
}

void read_inputs()
{
    events.SW1 = !digitalRead(PF_4);
    events.SW2 = !digitalRead(PF_0);

    unsigned int temp_y = analogRead(A0);
    unsigned int temp_x = analogRead(A1);

    events.DOWN = temp_y > (MID_POINT + DEAD_ZONE);
    events.UP   = temp_y < (MID_POINT - DEAD_ZONE);

    events.RIGHT = temp_x > (MID_POINT + DEAD_ZONE);
    events.LEFT  = temp_x < (MID_POINT - DEAD_ZONE);

}

bool get_event(EventType e)
{
    switch (e)
    {
        case UP:
            return events.UP;

        case DOWN:
            return events.DOWN;

        case LEFT:
            return events.LEFT;

        case RIGHT:
            return events.RIGHT;

        case SW1:
            return events.SW1;

        case SW2:
            return events.SW2;

    }
}



#endif // __HARDWARE_ABSTRACTION_LAYER__