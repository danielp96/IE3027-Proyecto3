#include <Arduino.h>

#include <stdint.h>

#include <ili9341.h>
#include <SPI.h>
#include <SD.h>

#include "hal.h"
#include "game_object.h"
#include "map.h"

#define LCD_WIDTH  320
#define LCD_HEIGHT 240

//File dir;
File file;

//char* text;

extern tImage pacman_side_1;
extern tImage pacman_side_2;
extern tImage pacman_up_1;
extern tImage pacman_up_2;
extern tImage pacman_down_1;
extern tImage pacman_down_2;

extern tImage blinky_side_1;
extern tImage blinky_side_2;
extern tImage blinky_up_1;
extern tImage blinky_up_2;
extern tImage blinky_down_1;
extern tImage blinky_down_2;

extern tImage clyde_side_1;
extern tImage clyde_side_2;
extern tImage clyde_up_1;
extern tImage clyde_up_2;
extern tImage clyde_down_1;
extern tImage clyde_down_2;

extern tImage inky_side_1;
extern tImage inky_side_2;
extern tImage inky_up_1;
extern tImage inky_up_2;
extern tImage inky_down_1;
extern tImage inky_down_2;

extern tImage pinky_side_1;
extern tImage pinky_side_2;
extern tImage pinky_up_1;
extern tImage pinky_up_2;
extern tImage pinky_down_1;
extern tImage pinky_down_2;

extern tImage test;

game_object pacman;
game_object blinky;
game_object clyde;
game_object inky;
game_object pinky;

// list of objects for rendering
game_object* object_list[] = {&pacman, &blinky, &clyde, &inky, &pinky};

tImage* pacman_sprites[] = {&pacman_side_1, &pacman_side_2, &pacman_up_1, &pacman_up_2, &pacman_down_1, &pacman_down_2};
tImage* blinky_sprites[] = {&blinky_side_1, &blinky_side_2, &blinky_up_1, &blinky_up_2, &blinky_down_1, &blinky_down_2};
tImage*  clyde_sprites[] = { &clyde_side_1,  &clyde_side_2,  &clyde_up_1,  &clyde_up_2,  &clyde_down_1,  &clyde_down_2};
tImage*   inky_sprites[] = {  &inky_side_1,   &inky_side_2,   &inky_up_1,   &inky_up_2,   &inky_down_1,   &inky_down_2};
tImage*  pinky_sprites[] = { &pinky_side_1,  &pinky_side_2,  &pinky_up_1,  &pinky_up_2,  &pinky_down_1,  &pinky_down_2};


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
  
    game_object_init(&pacman, 68, 204, pacman_sprites);
    game_object_init(&blinky, 150, 100, blinky_sprites);
    game_object_init(&clyde , 100, 150,  clyde_sprites);
    game_object_init(&inky  , 150, 150,   inky_sprites);
    game_object_init(&pinky , 200, 100,  pinky_sprites);

    map1_init();

    game_object_set_node(&pacman, map1_nodes[58]);

    //FillRect(0, 0, 319, 206, 0x421b);
    //String text1 = "Pacman!";
    //LCD_Print(text1, 20, 100, 2, 0xffff, 0x421b);

    //LCD_Sprite(50, 50, 100, 50, mario, 4, 1, 0, 0);
    
    //LCD_Bitmap(50, 50, 100, 100, mario);
    //LCD_Bitmap(0, 0, 320, 240, fondo);
    // DEBUG
    for (int i = 0; i<68; i++)
    {
        Node* n = map1_nodes[i];
        FillRect(n->x, n->y, 2, 2, 0xFFFF);

        if (n->up != NULL)
        {
            V_line(n->up->x, n->up->y, n->y - n->up->y, 0xFFFF);
        }

        if (n->down != NULL)
        {
            V_line(n->x, n->y, n->up->y - n->y, 0xFFFF);
        }

        if (n->left != NULL)
        {
            H_line(n->left->x, n->left->y, n->x - n->left->x, 0xFFFF);
        }

        if (n->right != NULL)
        {
            H_line(n->x, n->y, n->right->x - n->x, 0xFFFF);
        }
    } // end debug

}

void loop(void)
{
    read_inputs();

    //hal_debug();

    if (get_event(UP_1))
    {
        game_object_move(&pacman, UP);

        game_object_direction(&blinky, UP);
    }

    if (get_event(DOWN_1))
    {
        game_object_move(&pacman, DOWN);

        game_object_direction(&blinky, DOWN);
    }

    if (get_event(LEFT_1))
    {
        game_object_move(&pacman, LEFT);

        game_object_direction(&blinky, LEFT);
    }

    if (get_event(RIGHT_1))
    {
        game_object_move(&pacman, RIGHT);
        
        game_object_direction(&blinky, RIGHT);
    }

    delay(5);

    game_object_update_index(&pacman);
    game_object_update_index(&blinky);

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

    tImage* temp_sprite = self->sprite_list[self->sprite_index];

    LCD_Bitmap( self->x, self->y,
                temp_sprite->w, temp_sprite->h,
                (uint8_t*)temp_sprite->data,
                self->x_flip, self->y_flip);
}
