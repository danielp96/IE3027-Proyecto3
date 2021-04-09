#include <Arduino.h>

#include <ili9341.h>
#include <SPI.h>
#include <SD.h>

File dir;
File file;

char* text;


void printDirectory(File dir);

void setup(void)
{
  SysCtlClockSet(SYSCTL_SYSDIV_2_5|SYSCTL_USE_PLL|SYSCTL_OSC_MAIN|SYSCTL_XTAL_16MHZ);
  Serial.begin(9600);
  GPIOPadConfigSet(GPIO_PORTB_BASE, 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7, GPIO_STRENGTH_8MA, GPIO_PIN_TYPE_STD_WPU);
  Serial.println("Inicio");
  LCD_Init();
  LCD_Clear(0x00);
  
  FillRect(0, 0, 319, 206, 0x421b);
  String text1 = "Super Mario World!";
  LCD_Print(text1, 20, 100, 2, 0xffff, 0x421b);
//LCD_Sprite(int x, int y, int width, int height, unsigned char bitmap[],int columns, int index, char flip, char offset);
    
  //LCD_Bitmap(unsigned int x, unsigned int y, unsigned int width, unsigned int height, unsigned char bitmap[]);
  //LCD_Bitmap(0, 0, 320, 240, fondo);
  
  //for(int x = 0; x <319; x++){
  //  LCD_Bitmap(x, 52, 16, 16, tile2);
  //  LCD_Bitmap(x, 68, 16, 16, tile);
    
  //  LCD_Bitmap(x, 207, 16, 16, tile);
  //  LCD_Bitmap(x, 223, 16, 16, tile);
  //  x += 15;
 //}
  
}

void loop(void) {
 /* for(int x = 0; x <320-32; x++){
    delay(15);
    int anim2 = (x/35)%2;
    
    LCD_Sprite(x,100,16,24,planta,2,anim2,0,1);
    V_line( x -1, 100, 24, 0x421b);
    
    //LCD_Bitmap(x, 100, 32, 32, prueba);
    
    int anim = (x/11)%8;
    

    int anim3 = (x/11)%4;
    
    LCD_Sprite(x, 20, 16, 32, mario,8, anim,1, 0);
    V_line( x -1, 20, 32, 0x421b);
 
    //LCD_Sprite(x,100,32,32,bowser,4,anim3,0,1);
    //V_line( x -1, 100, 32, 0x421b);
 
 
    LCD_Sprite(x, 140, 16, 16, enemy,2, anim2,1, 0);
    V_line( x -1, 140, 16, 0x421b);
  
    LCD_Sprite(x, 175, 16, 32, luigi,8, anim,1, 0);
    V_line( x -1, 175, 32, 0x421b);
  }
  for(int x = 320-32; x >0; x--){
    delay(5);
    int anim = (x/11)%8;
    int anim2 = (x/11)%2;
    
    LCD_Sprite(x,100,16,24,planta,2,anim2,0,0);
    V_line( x + 16, 100, 24, 0x421b);
    
    //LCD_Bitmap(x, 100, 32, 32, prueba);
    
    //LCD_Sprite(x, 140, 16, 16, enemy,2, anim2,0, 0);
    //V_line( x + 16, 140, 16, 0x421b);
    
    //LCD_Sprite(x, 175, 16, 32, luigi,8, anim,0, 0);
    //V_line( x + 16, 175, 32, 0x421b);

    //LCD_Sprite(x, 20, 16, 32, mario,8, anim,0, 0);
    //V_line( x + 16, 20, 32, 0x421b);
  } 
*/
}

