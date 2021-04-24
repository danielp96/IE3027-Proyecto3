#include <Arduino.h>

#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include <ili9341.h>
#include <SPI.h>
#include <SD.h>

#include "hal.h"
#include "game_object.h"
#include "map.h"

#define LCD_WIDTH  320
#define LCD_HEIGHT 240

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

extern tImage eyes_side;
extern tImage eyes_up;
extern tImage eyes_down;

extern tImage blue_1;
extern tImage blue_2;

extern tImage test;

game_object pacman;
game_object blinky;
game_object clyde;
game_object inky;
game_object pinky;

// list of objects for rendering
game_object* object_list[] = {&pacman, &blinky, &clyde, &inky, &pinky};

tImage* pacman_sprites[] = {&pacman_side_1, &pacman_side_2, &pacman_up_1, &pacman_up_2, &pacman_down_1, &pacman_down_2};
tImage* blinky_sprites[] = {&blinky_side_1, &blinky_side_2, &blinky_up_1, &blinky_up_2, &blinky_down_1, &blinky_down_2, &eyes_side, &eyes_up, &eyes_down, &blue_1, &blue_2};
tImage*  clyde_sprites[] = { &clyde_side_1,  &clyde_side_2,  &clyde_up_1,  &clyde_up_2,  &clyde_down_1,  &clyde_down_2, &eyes_side, &eyes_up, &eyes_down, &blue_1, &blue_2};
tImage*   inky_sprites[] = {  &inky_side_1,   &inky_side_2,   &inky_up_1,   &inky_up_2,   &inky_down_1,   &inky_down_2, &eyes_side, &eyes_up, &eyes_down, &blue_1, &blue_2};
tImage*  pinky_sprites[] = { &pinky_side_1,  &pinky_side_2,  &pinky_up_1,  &pinky_up_2,  &pinky_down_1,  &pinky_down_2, &eyes_side, &eyes_up, &eyes_down, &blue_1, &blue_2};


void render(game_object* self);
void render_game(void);
void draw_sd_img(char* filename, uint16_t x, uint8_t y);


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

    // random setup
    pinMode(A3, INPUT); // dont connect anything here
    randomSeed(analogRead(A3));

    input_init();
    
    LCD_Init();
    LCD_Clear(0x00);
  
    map1_init();

    game_object_init(&pacman, map1_nodes[58]->x, map1_nodes[58]->y, pacman_sprites);
    game_object_init(&blinky, map1_nodes[24]->x, map1_nodes[24]->y, blinky_sprites);
    game_object_init(&clyde , map1_nodes[31]->x, map1_nodes[31]->y,  clyde_sprites);
    game_object_init(&inky  , map1_nodes[29]->x, map1_nodes[29]->y,   inky_sprites);
    game_object_init(&pinky , map1_nodes[0]->x, map1_nodes[0]->y,  pinky_sprites);


    game_object_set_node(&pacman, map1_nodes[58]);
    game_object_set_node(&blinky, map1_nodes[24]);
    game_object_set_node(&clyde , map1_nodes[31]);
    game_object_set_node(&inky  , map1_nodes[29]);
    game_object_set_node(&pinky , map1_nodes[0]);

    pinky.dead = true;
    inky.sick = true;

    //FillRect(0, 0, 319, 206, 0x421b);
    //String text1 = "Pacman!";
    //LCD_Print(text1, 20, 100, 2, 0xffff, 0x421b);

    //LCD_Sprite(50, 50, 100, 50, mario, 4, 1, 0, 0);
    
    //LCD_Bitmap(50, 50, 100, 100, mario);
    //LCD_Bitmap(0, 0, 320, 240, fondo);

    // cast because compiler warning
    draw_sd_img((char*)"map1_1-1.txt",   0,   0);
    draw_sd_img((char*)"map1_1-2.txt",  56,   0);
    draw_sd_img((char*)"map1_1-3.txt", 112,   0);
    draw_sd_img((char*)"map1_1-4.txt", 168,   0);
    draw_sd_img((char*)"map1_2-1.txt",   0,  30);
    draw_sd_img((char*)"map1_2-2.txt",  56,  30);
    draw_sd_img((char*)"map1_2-3.txt", 112,  30);
    draw_sd_img((char*)"map1_2-4.txt", 168,  30);
    draw_sd_img((char*)"map1_3-1.txt",   0,  60);
    draw_sd_img((char*)"map1_3-2.txt",  56,  60);
    draw_sd_img((char*)"map1_3-3.txt", 112,  60);
    draw_sd_img((char*)"map1_3-4.txt", 168,  60);
    draw_sd_img((char*)"map1_4-1.txt",   0,  90);
    draw_sd_img((char*)"map1_4-2.txt",  56,  90);
    draw_sd_img((char*)"map1_4-3.txt", 112,  90);
    draw_sd_img((char*)"map1_4-4.txt", 168,  90);
    draw_sd_img((char*)"map1_5-1.txt",   0, 120);
    draw_sd_img((char*)"map1_5-2.txt",  56, 120);
    draw_sd_img((char*)"map1_5-3.txt", 112, 120);
    draw_sd_img((char*)"map1_5-4.txt", 168, 120);
    draw_sd_img((char*)"map1_6-1.txt",   0, 150);
    draw_sd_img((char*)"map1_6-2.txt",  56, 150);
    draw_sd_img((char*)"map1_6-3.txt", 112, 150);
    draw_sd_img((char*)"map1_6-4.txt", 168, 150);
    draw_sd_img((char*)"map1_7-1.txt",   0, 180);
    draw_sd_img((char*)"map1_7-2.txt",  56, 180);
    draw_sd_img((char*)"map1_7-3.txt", 112, 180);
    draw_sd_img((char*)"map1_7-4.txt", 168, 180);
    draw_sd_img((char*)"map1_8-1.txt",   0, 210);
    draw_sd_img((char*)"map1_8-2.txt",  56, 210);
    draw_sd_img((char*)"map1_8-3.txt", 112, 210);
    draw_sd_img((char*)"map1_8-4.txt", 168, 210);
}

void loop(void)
{
    read_inputs();

    //hal_debug();

    if (get_event(UP_1))
    {
        game_object_move(&pacman, UP);
    }

    if (get_event(DOWN_1))
    {
        game_object_move(&pacman, DOWN);
    }

    if (get_event(LEFT_1))
    {
        game_object_move(&pacman, LEFT);
    }

    if (get_event(RIGHT_1))
    {
        game_object_move(&pacman, RIGHT);
    }

    game_object_ghost_move(&blinky);
    game_object_ghost_move(&clyde);
    game_object_ghost_move(&inky);
    game_object_ghost_move(&pinky);

    delay(5);

    game_object_update_index(&pacman);
    game_object_update_index(&blinky);
    game_object_update_index(&clyde);
    game_object_update_index(&inky);
    game_object_update_index(&pinky);

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

void draw_sd_img(char* filename, uint16_t x, uint8_t y)
{
    File file = SD.open(filename);

    // read file contents
    char data[file.size()];
    file.read(data, file.size()+1);
    file.close();

    // delimiters
    const char s1[2] = ",";
    const char s2[2] = ";";

    // get width and heigth
    uint8_t width = strtoul(strtok(data, s1), NULL, 10);
    uint8_t height = strtoul(strtok(NULL, s2), NULL, 10);

    // reserve space for parsed data
    uint8_t* temp_data = (uint8_t*)malloc(width*height*2*sizeof(uint8_t));

    // parse data
    for (int i = 0; i<(width*height*2); i++)
    {
        temp_data[i] = strtoul(strtok(NULL, s1), NULL, 16);
    }

    // render
    LCD_Bitmap(x, y, width, height, temp_data, false, false);

    // dont forget to free allocated memory
    free(temp_data);
}

