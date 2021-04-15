#include <Arduino.h>

#include <stdint.h>

#include <ili9341.h>
#include <SPI.h>
#include <SD.h>

#include "hal.h"
#include "game_object.h"

#define LCD_WIDTH  320
#define LCD_HEIGHT 240

//File dir;
File file;

//char* text;

extern tImage pacman_right_1;
extern tImage pacman_right_2;
extern tImage blinky_right_1;
extern tImage  clyde_right_1;
extern tImage   inky_right_1;
extern tImage  pinky_right_1;

game_object pacman;
game_object blinky;
game_object clyde;
game_object inky;
game_object pinky;

// list of objects for rendering
game_object* object_list[] = {&pacman, &blinky, &clyde, &inky, &pinky};


void render(game_object* self);
void render_game(void);

void setup(void)
{
    SysCtlClockSet(SYSCTL_SYSDIV_2_5|SYSCTL_USE_PLL|SYSCTL_OSC_MAIN|SYSCTL_XTAL_16MHZ);
    Serial.begin(9600);
    GPIOPadConfigSet(GPIO_PORTB_BASE, 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7, GPIO_STRENGTH_8MA, GPIO_PIN_TYPE_STD_WPU);
    Serial.println("Inicio");

    // SD setup
    SPI.setModule(0);
    Serial.print("Initializing SD card...");
    pinMode(10, OUTPUT);
    if(!SD.begin(32))
    {
        Serial.println("initialization failed!");
        return;
    }
    Serial.println("initialization done.");

    input_init();
    
    LCD_Init();
    LCD_Clear(0x00);
  
    game_object_init(&pacman, 100, 100, &pacman_right_1);
    game_object_init(&blinky, 150, 100, &blinky_right_1);
    game_object_init(&clyde , 100, 150,  &clyde_right_1);
    game_object_init(&inky  , 150, 150,   &inky_right_1);
    game_object_init(&pinky , 200, 100,  &pinky_right_1);

    //FillRect(0, 0, 319, 206, 0x421b);
    //String text1 = "Pacman!";
    //LCD_Print(text1, 20, 100, 2, 0xffff, 0x421b);

    //LCD_Sprite(50, 50, 100, 50, mario, 4, 1, 0, 0);
    
    //LCD_Bitmap(50, 50, 100, 100, mario);
    //LCD_Bitmap(0, 0, 320, 240, fondo);

}

void loop(void)
{
    read_inputs();

    //hal_debug();

    if (get_event(UP))
    {
        game_object_add_y(&pacman, -1, LCD_HEIGHT, 0);
    }

    if (get_event(DOWN))
    {
        game_object_add_y(&pacman, 1, LCD_HEIGHT, 0);
    }

    if (get_event(LEFT))
    {
        game_object_add_x(&pacman, -1, LCD_WIDTH, 0);
    }

    if (get_event(RIGHT))
    {
        game_object_add_x(&pacman, 1, LCD_WIDTH, 0);
    }

    render_game();
}

void render_game(void)
{
    for (int i = 0; i<5; i++)
    {
        render(object_list[i]);
    }
}

void render(game_object* self)
{
    if (self->hidden)
    {
        return;
    }

    LCD_Bitmap(self->x, self->y, self->sprite->w, self->sprite->h, (uint8_t*)self->sprite->data);
}
