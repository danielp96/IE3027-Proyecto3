#ifndef __HARDWARE_ABSTRACTION_LAYER__
#define __HARDWARE_ABSTRACTION_LAYER__

#include <Arduino.h>

#include <stdint.h>
#include <stdbool.h>

enum EventType {UP_E, DOWN_E, LEFT_E, RIGHT_E, SW1_E, SW2_E};

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
const unsigned int DEAD_ZONE = 250;
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
        case UP_E:
            return events.UP;

        case DOWN_E:
            return events.DOWN;

        case LEFT_E:
            return events.LEFT;

        case RIGHT_E:
            return events.RIGHT;

        case SW1_E:
            return events.SW1;

        case SW2_E:
            return events.SW2;

    }
}

// Extra slow
void hal_debug()
{
    Serial.print(" UP: ");
    Serial.print(events.UP);
    
    Serial.print(" DOWN: ");
    Serial.print(events.DOWN);

    Serial.print(" LEFT: ");
    Serial.print(events.LEFT);

    Serial.print(" RIGHT: ");
    Serial.print(events.RIGHT);

    Serial.print(" SW1: ");
    Serial.print(events.SW1);

    Serial.print(" SW2: ");
    Serial.print(events.SW2);

    Serial.println("");
}

#endif // __HARDWARE_ABSTRACTION_LAYER__