#include <Arduino.h>

#include <ili9341.h>
#include <SPI.h>
#include <SD.h>

#include "hal.h"
#include "game_object.h"


//File dir;
//File file;

//char* text;

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

    input_init();
    
    LCD_Init();
    LCD_Clear(0x00);
  
    game_object_init(&pacman, 100, 100, 25, 25, 0xFFE0);
    game_object_init(&blinky, 150, 100, 25, 25, 0xF800);
    game_object_init(&clyde , 100, 150, 25, 25, 0xFBE0);
    game_object_init(&inky  , 150, 150, 25, 25, 0x07FF);
    game_object_init(&pinky , 200, 100, 25, 25, 0xFDDF);

    //FillRect(0, 0, 319, 206, 0x421b);
    //String text1 = "Pacman!";
    //LCD_Print(text1, 20, 100, 2, 0xffff, 0x421b);

    //LCD_Sprite(50, 50, 100, 50, mario, 4, 1, 0, 0);
    
    //LCD_Bitmap(50, 50, 100, 100, mario);
    //LCD_Bitmap(0, 0, 320, 240, fondo);
  
    //for(int x = 0; x <319; x++)
    //{
    //  LCD_Bitmap(x, 52, 16, 16, tile2);
    //  LCD_Bitmap(x, 68, 16, 16, tile);
    
    //  LCD_Bitmap(x, 207, 16, 16, tile);
    //  LCD_Bitmap(x, 223, 16, 16, tile);
    //  x += 15;
    //}
  
}

void loop(void)
{
    read_inputs();

    Serial.print(" UP: ");
    Serial.print(get_event(UP));

    Serial.print(" DOWN: ");
    Serial.print(get_event(DOWN));

    Serial.print(" LEFT: ");
    Serial.print(get_event(LEFT));

    Serial.print(" RIGHT: ");
    Serial.print(get_event(RIGHT));

    Serial.print(" SW1: ");
    Serial.print(get_event(SW1));

    Serial.print(" SW2: ");
    Serial.print(get_event(SW2));
    Serial.println("");

    if (get_event(UP))
    {
        pacman.y -= 5;
    }

    if (get_event(DOWN))
    {
        pacman.y += 5;
    }

    if (get_event(LEFT))
    {
        pacman.x -= 5;
    }

    if (get_event(RIGHT))
    {
        pacman.x += 5;
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

    FillRect(self->x, self->y, self->w, self->h, self->color);
}
