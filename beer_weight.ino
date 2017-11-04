#include <Wire.h>
#include "rgb_lcd.h"
#define FULL_LOAD 775 //This will change with whatever a full keg on the load cell is
#define EMPTY_LOAD 0  //This will change to whatever an empty keg on the load cell is
#define FULL_COLOR 255
#define LOADPIN A1
#define BEER_NAME "Dopplebock"
#define LINE_CLEAR "                " //16 Spaces for length of display
rgb_lcd lcd;

const int colorR = 255;
const int colorG = 0;
const int colorB = 0;
void set_color_slider( long load){
  
  /*Full should be all green and empty should be all red. Blue shouldn't be involved*/
  int scaled = (load *  FULL_COLOR)/ FULL_LOAD ;
  lcd.setRGB(FULL_COLOR - scaled, scaled, 0);
}  

void clear_second_line(){ //Not sure this is the best way to do this
  lcd.setCursor(0,1);
  lcd.print(LINE_CLEAR);
}
void setup() 
{
    // set up the LCD's number of columns and rows:
    lcd.begin(16, 2);
        
    // Print a message to the top row of the LCD.
    lcd.print(BEER_NAME);

    //Setup the Load Cell (Right now it is a photoresistor shhhhhh...)
    
    delay(1000);
}

void loop() 
{
    long load;    
    load = analogRead(LOADPIN);
    set_color_slider(load);
    clear_second_line();
    lcd.setCursor(0,1); //Onto Second line so we don't override the name
    lcd.print( (load * 100) / FULL_LOAD );
    lcd.print("% left");
    delay(100);
}
