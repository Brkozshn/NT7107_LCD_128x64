
/**********************************************************************************
 * 
 * Interfacing Arduino with KS0108 Monochrome GLCD.
 * This example is for KS0108 GLCD modules with 128x64 Pixel resolution (two CS pins).
 * This is a free software with NO WARRANTY - Use it at your own risk!
 * https://simple-circuit.com/
 *
***********************************************************************************
 Written by Limor Fried/Ladyada for Adafruit Industries,
 with contributions from the open source community.
 BSD license, check license.txt for more information
 All text above, and the splash screen below must be
 included in any redistribution.
************************************************************************************
* Modified to work with KS0108 monochrome GLCD. More information including circuit
*   diagram on:
* https://simple-circuit.com/
* 
 **********************************************************************************/

#include <Adafruit_GFX.h>   // include adafruit GFX library
#include "KS0108_GLCD.h"    // include KS0108 GLCD library


// KS0108 GLCD library initialization according to the following connection:
// KS0108_GLCD(DI, RW, E, DB0, DB1, DB2, DB3, DB4, DB5, DB6, DB7, CS1, CS2, RES);
KS0108_GLCD display = KS0108_GLCD(A0, A1, A2, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12);


// 'orion logo black', 128x64px

const unsigned char myBitmap [] PROGMEM = {
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0x00, 0x03, 0xfc, 0x00, 0x07, 0xe0, 0x00, 0x0e, 0x1e, 0x00, 0x01, 0xe0, 0x00, 0x1f, 
	0xff, 0xfd, 0x00, 0x01, 0xf8, 0x00, 0x03, 0xc0, 0x00, 0x1e, 0x1e, 0x00, 0x00, 0xe0, 0x00, 0x0f, 
	0xff, 0xfc, 0x80, 0x01, 0xf0, 0x00, 0x03, 0x80, 0x00, 0x1c, 0x1c, 0x00, 0x00, 0xe0, 0x00, 0x0f, 
	0xff, 0xf8, 0x40, 0x01, 0xf0, 0x00, 0x03, 0x80, 0x00, 0x1c, 0x3c, 0x00, 0x01, 0xc0, 0x00, 0x0f, 
	0xff, 0xf8, 0x00, 0x01, 0xf0, 0x7f, 0x87, 0x87, 0xff, 0xf8, 0x3c, 0x3f, 0xc1, 0xc1, 0xfe, 0x0f, 
	0xff, 0xf8, 0x20, 0x03, 0xe0, 0xff, 0x07, 0x07, 0xff, 0xf8, 0x38, 0x3f, 0xc1, 0xc3, 0xfe, 0x1f, 
	0xff, 0xf0, 0x10, 0x03, 0xe0, 0xff, 0x07, 0x0f, 0xff, 0xf8, 0x78, 0x7f, 0xc3, 0x83, 0xfc, 0x1f, 
	0xff, 0xf0, 0x00, 0x03, 0xe1, 0xff, 0x0e, 0x0f, 0xff, 0xf0, 0x78, 0x7f, 0x83, 0x87, 0xfc, 0x1f, 
	0xff, 0xf0, 0x08, 0x07, 0xc1, 0xfe, 0x0e, 0x0f, 0xff, 0xf0, 0x70, 0x7f, 0x83, 0x87, 0xfc, 0x3f, 
	0xff, 0xe0, 0x04, 0x07, 0xc1, 0xfe, 0x0e, 0x1f, 0xff, 0xf0, 0xf0, 0xff, 0x87, 0x07, 0xf8, 0x3f, 
	0xff, 0xe0, 0x00, 0x0f, 0xc3, 0xfe, 0x1c, 0x1f, 0xff, 0xe0, 0xe0, 0xff, 0x07, 0x0f, 0xf8, 0x3f, 
	0xff, 0xe0, 0x02, 0x0f, 0x83, 0xfc, 0x1c, 0x1f, 0xff, 0xe0, 0xe0, 0xff, 0x07, 0x0f, 0xf8, 0x7f, 
	0xff, 0xc0, 0x01, 0x0f, 0x83, 0xfc, 0x1c, 0x3f, 0xff, 0xe1, 0xe0, 0xfe, 0x0e, 0x0f, 0xf0, 0x7f, 
	0xff, 0xc0, 0x00, 0x1f, 0x80, 0x00, 0x38, 0x3f, 0xff, 0xc1, 0xc0, 0x00, 0x0e, 0x1f, 0xf0, 0xff, 
	0xff, 0xc0, 0x00, 0x9f, 0x80, 0x00, 0x38, 0x3f, 0xff, 0xc1, 0xc0, 0x00, 0x0c, 0x1f, 0xe0, 0xff, 
	0xff, 0xc0, 0x00, 0x5f, 0x80, 0x00, 0x78, 0x7f, 0xff, 0xc3, 0xc0, 0x00, 0x1c, 0x1f, 0xe0, 0xff, 
	0xff, 0xe0, 0x00, 0x3f, 0xc0, 0x00, 0xf0, 0x7f, 0xff, 0x83, 0xe0, 0x00, 0x3c, 0x3f, 0xe1, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0x80, 0x00, 0xfc, 0x00, 0x01, 0xe0, 0x00, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xfe, 0x40, 0x00, 0xfc, 0x00, 0x01, 0xc0, 0x00, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xfe, 0x20, 0x00, 0xf8, 0x00, 0x01, 0xc0, 0x00, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xfc, 0x20, 0x00, 0xf8, 0x1f, 0x01, 0xc0, 0xf8, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xfc, 0x10, 0x00, 0xf8, 0x7f, 0xc3, 0x83, 0xfc, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xfc, 0x08, 0x01, 0xf0, 0x7f, 0x83, 0x87, 0xfc, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xf8, 0x08, 0x01, 0xf0, 0x00, 0x03, 0x80, 0x00, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xf8, 0x04, 0x01, 0xe0, 0x00, 0x07, 0x00, 0x00, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xf8, 0x02, 0x03, 0xe0, 0x00, 0x07, 0x00, 0x00, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xf0, 0x02, 0x03, 0xe0, 0x00, 0x0f, 0x00, 0x00, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xf0, 0x01, 0x03, 0xc1, 0xff, 0xfe, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xf0, 0x00, 0x87, 0xc1, 0xff, 0xfe, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xe0, 0x00, 0x07, 0xc0, 0x00, 0x1e, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xe0, 0x00, 0x47, 0xc0, 0x00, 0x1c, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xe0, 0x00, 0x2f, 0xc0, 0x00, 0x1c, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xe0, 0x00, 0x1f, 0xc0, 0x00, 0x3e, 0x00, 0x01, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff
};


// 'lightning', 32x32px

const unsigned char lightningBitmap [] PROGMEM = {
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x3f, 0xff, 
	0xff, 0xf7, 0xbf, 0xff, 0xff, 0xf7, 0xbf, 0xff, 0xff, 0xe7, 0xbf, 0xff, 0xff, 0xe7, 0x3f, 0xff, 
	0xff, 0xef, 0x3f, 0xff, 0xff, 0xef, 0x7f, 0xff, 0xff, 0xef, 0x7f, 0xff, 0xff, 0xcf, 0x01, 0xff, 
	0xff, 0xdf, 0xf9, 0xff, 0xff, 0xdf, 0xfb, 0xff, 0xff, 0xdf, 0xf7, 0xff, 0xff, 0x9f, 0xe7, 0xff, 
	0xff, 0x80, 0xef, 0xff, 0xff, 0xfd, 0xcf, 0xff, 0xff, 0xfd, 0xdf, 0xff, 0xff, 0xfd, 0x9f, 0xff, 
	0xff, 0xf9, 0xbf, 0xff, 0xff, 0xfb, 0x3f, 0xff, 0xff, 0xfb, 0x7f, 0xff, 0xff, 0xfa, 0x7f, 0xff, 
	0xff, 0xf2, 0xff, 0xff, 0xff, 0xf5, 0xff, 0xff, 0xff, 0xf1, 0xff, 0xff, 0xff, 0xe3, 0xff, 0xff, 
	0xff, 0xf3, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff
};



// 'lightning-131983802348435912', 16x16px    calculated by hand.

const unsigned char lightningBitmap16 [] PROGMEM = {
	0x00, 0x40, 0x00, 0xc0, 0x00, 0xc0, 0x01, 0x40, 0x02, 0x40, 0x04, 0x40, 0x08, 0x7c, 0x10, 0x08, 
	0x3e, 0x10, 0x02, 0x20, 0x02, 0x40, 0x02, 0x80, 0x03, 0x00, 0x03, 0x00, 0x02, 0x00, 0x00, 0x00
};



// 32x24px  Not Equal Phase icon Bitmap    

const unsigned char phaseCompBitmap [] PROGMEM = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0xcc, 0x00, 0x00, 0x01, 0x32, 0x00, 0x00, 0x01, 0x32, 0x00, 0x00, 0x02, 0x31, 0x00, 0x00, 0x02, 0x31, 0x00, 0x00, 
  0x04, 0x48, 0x80, 0x00, 0x04, 0x48, 0x80, 0x00, 0x04, 0x48, 0x80, 0x00, 0x08, 0x84, 0x40, 0x00, 0x08, 0x84, 0x40, 0x00, 0x08, 0x84, 0x40, 0x00, 
  0x00, 0x02, 0x21, 0x10, 0x00, 0x02, 0x21, 0x10, 0x00, 0x02, 0x21, 0x10, 0x00, 0x01, 0x12, 0x20, 0x00, 0x01, 0x12, 0x20, 0x00, 0x01, 0x12, 0x20,
  0x00, 0x00, 0x8c, 0x40, 0x00, 0x00, 0x8c, 0x40, 0x00, 0x00, 0x4c, 0x80, 0x00, 0x00, 0x4c, 0x80, 0x00, 0x00, 0x33, 0x00, 0x00, 0x00, 0x00, 0x00

};



// 32x24px Equal Phase bitmap icon. Calculated by hand. It works fine.

const unsigned char phaseBitmap [] PROGMEM = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00, 0x48, 0x00, 0x00, 0x00, 0x48, 0x00, 0x00, 0x00, 0x84, 0x00, 0x00, 0x00, 0x84, 0x00, 0x00,
  0x01, 0x02, 0x00, 0x00, 0x01, 0x02, 0x00, 0x00, 0x01, 0x02, 0x00, 0x00, 0x02, 0x01, 0x00, 0x00, 0x02, 0x01, 0x00, 0x00, 0x02, 0x01, 0x00, 0x00,
  0x00, 0x00, 0x80, 0x40, 0x00, 0x00, 0x80, 0x40, 0x00, 0x00, 0x80, 0x40, 0x00, 0x00, 0x40, 0x80, 0x00, 0x00, 0x40, 0x80, 0x00, 0x00, 0x40, 0x80,
  0x00, 0x00, 0x21, 0x00, 0x00, 0x00, 0x21, 0x00, 0x00, 0x00, 0x12, 0x00, 0x00, 0x00, 0x12, 0x00, 0x00, 0x00, 0x0C, 0x00, 0x00, 0x00, 0x00, 0x00 

};



// '270px-Check_mark, 16x16px

const unsigned char Check_Mark_Bitmap [] PROGMEM = {
	0xff, 0xff, 0xff, 0xff, 0xff, 0xf9, 0xff, 0xf3, 0xff, 0xe7, 0xff, 0xc7, 0xff, 0xcf, 0xff, 0x9f, 
	0xff, 0x1f, 0xff, 0x3f, 0xde, 0x7f, 0xcc, 0x7f, 0xc0, 0xff, 0xe1, 0xff, 0xf3, 0xff, 0xff, 0xff
};



// 'false mark', 16x16px

const unsigned char False_Mark_Bitmap [] PROGMEM = {
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf3, 0xcf, 0xe1, 0x87, 0xe0, 0x07, 0xf0, 0x0f, 0xf8, 0x1f, 
	0xf8, 0x1f, 0xf0, 0x0f, 0xe0, 0x07, 0xe1, 0x87, 0xf3, 0xcf, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff
};




void setup()   {                
  Serial.begin(9600);

  // initialize KS0108 GLCD module with active high CS pins
  if ( display.begin(KS0108_CS_ACTIVE_HIGH) == false ) {
    //Serial.println( F("display initialization failed!") );    // lack of RAM space
    while(true);  // stay here forever!
  }

  display.display();
  delay(2000); // Pause for 2 seconds

  // Clear the buffer
  display.clearDisplay();

  // Show the display buffer on the screen. You MUST call display() after
  // drawing commands to make them visible on screen!

  display.display();
  delay(2000);

  // display.display() is NOT necessary after every single drawing command,
  // unless that's what you want...rather, you can batch up a bunch of
  // drawing operations and then update the screen all at once by calling
  // display.display(). These examples demonstrate both approaches...


  //test_char_hello();   // Print some string (Orion AR-GE)

  drawbitmap_Orionee_logo();    //Orion EE Logo

  templatedraw();     // template for phase comparator


}

// main loop (nothing here!)
void loop() {

}



///////////////////// LCD Phase Comparator  Interface     ////////////////////


void test_char_hello() {

  display.clearDisplay();

  display.setTextSize(2);      // Normal 1:1 pixel scale
  display.setTextColor(KS0108_ON); // Draw white text
  display.setCursor(0, 0);     // Start at top-left corner
  display.write("Orion EE");

 display.setTextSize(2);      // Normal 1:1 pixel scale
 display.setTextColor(KS0108_OFF, KS0108_ON); // Draw 'inverse' text
  display.setCursor(0, 18);     // Start at top-left corner
  display.write("Tech-Dev");


  display.setTextColor(KS0108_ON);        // Draw white text
  display.setCursor(10,40);             // Start at top-left corner
  display.println(F("HELLO!"));

  display.display();
  delay(1000);
}



// Orion EE  Logo 

void drawbitmap_Orionee_logo(void) {

  display.clearDisplay();

 display.drawBitmap(0, 0,  myBitmap, 128, 64, 1);
 display.display();
 delay(4000);

}


// Drawing an arrow to show Phase difference 

// Default values for drawing an arrow.

// Uzun çizgi için x0 -> 80, y0 -> 15, x1-> 60, y1-> 15
// Kısa yan çizgi üst x0 -> 80, y0 -> 15, x1-> 75, y1-> 10
// Kısa yan çizgi alt x0 -> 80, y0 -> 15, x1-> 75, y1-> 20 


void arrow(int x0, int y0) {

    display.drawLine(x0, y0, x0-20, y0, KS0108_ON);
    display.display();
    
    display.drawLine(x0, y0, x0-10, y0-5, KS0108_ON);
    display.display();

    display.drawLine(x0, y0, x0-10, y0+5, KS0108_ON);
    display.display();

}


// Drawing a Check Mark

void checkMark(int x, int y) {

 display.drawBitmap(x, y,  Check_Mark_Bitmap, 16, 16, 1);
 display.display();

}


// Drawing a False Mark 

void falseMark(int x, int y) {

 display.drawBitmap(x, y,  False_Mark_Bitmap, 16, 16, 1);
 display.display();

}


// Drawing an empty lightning icon for Phase A

void lightning_drawbitmap_PhaseA(void) {

 display.drawBitmap(45, 0,  lightningBitmap16, 16, 16, 1);
 display.display();

}


// Drawing an empty lightning icon for Phase B

void lightning_drawbitmap_PhaseB(void) {

 display.drawBitmap(108, 0,  lightningBitmap16, 16, 16, 1);
 display.display();

}

// Phase Equal sin waves.

void phaseEqual_drawbitmap(void) {

 display.drawBitmap(25, 15,  phaseBitmap, 32, 24, 1);
 display.display();

}


// Phase Not Equal sin waves.

void phaseNotEqual_drawbitmap(void) {

 display.drawBitmap(20, 16,  phaseCompBitmap, 32, 24, 1);
 display.display();

}



void twoPhaseConnected() {

 // We have to fill inside the all lightning icons.

lightning_drawbitmap_PhaseA();      // lightning for phase A
lightning_drawbitmap_PhaseB();      // Lightning for phase B

Lightning_Fill_B();         // filling lightning icon for Phase B.

Lightning_Fill_A();         // filling lightning icon for Phase A. 

}


/// Phase B is connected and shows an filled lightning icon.

void Phase_BConnectedLightning() {

 // We have to fill inside the Phase B lightning icons.

lightning_drawbitmap_PhaseA();      // lightning for phase A

lightning_drawbitmap_PhaseB();      // Lightning for phase B

Lightning_Fill_B();         // filling lightning icon for Phase B.

}


/// Phase A is connected and shows an filled lightning icon.

void Phase_AConnectedLightning() {

 // We have to fill inside the Phase A lightning icons.

lightning_drawbitmap_PhaseA();      // lightning for phase A

lightning_drawbitmap_PhaseB();      // Lightning for phase B

Lightning_Fill_A();         // filling lightning icon for Phase A.

}



/// Fill function for Phase A

void Lightning_Fill_A() {


display.writePixel(53, 3, KS0108_ON);   // Write just one pixel.


display.writePixel(52, 4, KS0108_ON);   // Write just one pixel.
display.writePixel(53, 4, KS0108_ON);   // Write just one pixel.


display.writePixel(51, 5, KS0108_ON);   // Write just one pixel.
display.writePixel(52, 5, KS0108_ON);   // Write just one pixel.
display.writePixel(53, 5, KS0108_ON);   // Write just one pixel.


display.writePixel(50, 6, KS0108_ON);   // Write just one pixel.
display.writePixel(51, 6, KS0108_ON);   // Write just one pixel.
display.writePixel(52, 6, KS0108_ON);   // Write just one pixel.
display.writePixel(53, 6, KS0108_ON);   // Write just one pixel.


display.writePixel(49, 7, KS0108_ON);   // Write just one pixel.
display.writePixel(50, 7, KS0108_ON);   // Write just one pixel.
display.writePixel(51, 7, KS0108_ON);   // Write just one pixel.
display.writePixel(52, 7, KS0108_ON);   // Write just one pixel.
display.writePixel(53, 7, KS0108_ON);   // Write just one pixel.
display.writePixel(54, 7, KS0108_ON);   // Write just one pixel.
display.writePixel(55, 7, KS0108_ON);   // Write just one pixel.
display.writePixel(56, 7, KS0108_ON);   // Write just one pixel.


display.writePixel(52, 8, KS0108_ON);   // Write just one pixel.
display.writePixel(53, 8, KS0108_ON);   // Write just one pixel.
display.writePixel(54, 8, KS0108_ON);   // Write just one pixel.
display.writePixel(55, 8, KS0108_ON);   // Write just one pixel.

display.writePixel(52, 9, KS0108_ON);   // Write just one pixel.
display.writePixel(53, 9, KS0108_ON);   // Write just one pixel.
display.writePixel(54, 9, KS0108_ON);   // Write just one pixel.

display.writePixel(52, 10, KS0108_ON);   // Write just one pixel.
display.writePixel(53, 10, KS0108_ON);   // Write just one pixel.

display.writePixel(52, 11, KS0108_ON);   // Write just one pixel.

}


/// Fill function for Phase B

void Lightning_Fill_B() {


display.writePixel(116, 3, KS0108_ON);   // Write just one pixel.


display.writePixel(115, 4, KS0108_ON);   // Write just one pixel.
display.writePixel(116, 4, KS0108_ON);   // Write just one pixel.


display.writePixel(114, 5, KS0108_ON);   // Write just one pixel.
display.writePixel(115, 5, KS0108_ON);   // Write just one pixel.
display.writePixel(116, 5, KS0108_ON);   // Write just one pixel.


display.writePixel(113, 6, KS0108_ON);   // Write just one pixel.
display.writePixel(114, 6, KS0108_ON);   // Write just one pixel.
display.writePixel(115, 6, KS0108_ON);   // Write just one pixel.
display.writePixel(116, 6, KS0108_ON);   // Write just one pixel.


display.writePixel(112, 7, KS0108_ON);   // Write just one pixel.
display.writePixel(113, 7, KS0108_ON);   // Write just one pixel.
display.writePixel(114, 7, KS0108_ON);   // Write just one pixel.
display.writePixel(115, 7, KS0108_ON);   // Write just one pixel.
display.writePixel(116, 7, KS0108_ON);   // Write just one pixel.
display.writePixel(117, 7, KS0108_ON);   // Write just one pixel.
display.writePixel(118, 7, KS0108_ON);   // Write just one pixel.
display.writePixel(119, 7, KS0108_ON);   // Write just one pixel.


display.writePixel(115, 8, KS0108_ON);   // Write just one pixel.
display.writePixel(116, 8, KS0108_ON);   // Write just one pixel.
display.writePixel(117, 8, KS0108_ON);   // Write just one pixel.
display.writePixel(118, 8, KS0108_ON);   // Write just one pixel.

display.writePixel(115, 9, KS0108_ON);   // Write just one pixel.
display.writePixel(116, 9, KS0108_ON);   // Write just one pixel.
display.writePixel(117, 9, KS0108_ON);   // Write just one pixel.

display.writePixel(115, 10, KS0108_ON);   // Write just one pixel.
display.writePixel(116, 10, KS0108_ON);   // Write just one pixel.

display.writePixel(115, 11, KS0108_ON);   // Write just one pixel.

}


// Function for self test pending message downside of the screen.

void selfTestPending() {

  display.drawRect(0, 43, 128, 10, KS0108_ON);
  display.display(); // Update screen with each newly-drawn rectangle

  display.setTextSize(0.5);      // Normal 1:1 pixel scale
  display.setCursor(5, 44);     // Start at top-left corner
  display.write("Self Test Pending");

}


// Function to printing 50 hz in downside of the screen.

void FiftyHz() {

  display.drawRect(0, 53, 64, 10, KS0108_ON);
  display.display(); // Update screen with each newly-drawn rectangle

  display.setTextSize(1);      // Normal 1:1 pixel scale
  display.setCursor(10, 55);     // Start at top-left corner
  display.write("50 HZ");
}



// Function to printing 60 hz in downside of the screen.

void SixtyHz() {

  display.drawRect(0, 53, 64, 10, KS0108_ON);
  display.display(); // Update screen with each newly-drawn rectangle

  display.setTextSize(1);      // Normal 1:1 pixel scale
  display.setCursor(10, 55);     // Start at top-left corner
  display.write("60 HZ");

}


// Function to create empty box on bottom of the screen.

void empty_box_Downside() {

  display.drawRect(64, 53, 64, 10, KS0108_ON);
  display.display(); // Update screen with each newly-drawn rectangle

}


// Battery charge rect with rounded and empty

void battery_icon() {

  display.drawRect(85, 55, 15, 7, KS0108_ON);
  display.display(); // Update screen with each newly-drawn rectangle

}

 // Writing PhaseA string.

void PhaseA_String(){

  display.setTextSize(1);      // Normal 1:1 pixel scale
  display.setTextColor(KS0108_ON);
  display.setCursor(3, 3);     // Start at top-left corner
  display.println(F("Phase A"));

}

 // Writing PhaseB string.

void PhaseB_String() {

  display.setTextSize(1);      // Normal 1:1 pixel scale
  display.setTextColor(KS0108_ON);
  display.setCursor(66, 3);     // Start at top-left corner
  display.println(F("Phase B"));
}

// Writing check probe string

void checkProbeString () {

//display.setTextSize(1);      // Normal 1:1 pixel scale
display.setTextSize(1, 2);     // Set pixel size with two axis. 

display.setTextColor(KS0108_ON);
display.setCursor(24, 18);     // Start at top-left corner
display.write("Check Probe");

}


void phaseDiff_B_overA() {

  display.setTextSize(1);      // Normal 1:1 pixel scale
  display.setTextColor(KS0108_ON);
  display.setCursor(60, 25);     // Start at top-left corner
  display.println(F("B"));

  arrow(90,30);

  display.setTextSize(1);      // Normal 1:1 pixel scale
  display.setTextColor(KS0108_ON);
  display.setCursor(100, 25);     // Start at top-left corner
  display.println(F("A"));

}


///// Two Phase are connected. No Phase difference.

void twoPhaseConnected_NoDiff () {

 display.clearDisplay();

// 1 st part of the begining 

  delay(2000);

  PhaseB_String();            // Writing Phase B string

// 2 nd Part of the begining

  PhaseA_String();            // Writing Phase A string


  twoPhaseConnected();          // Filled lightning icon.

  //// Middle of the Screen.

  phaseEqual_drawbitmap();         // Phase equal  

  checkMark(75,20);        // Add check mark (using bitmap if it is needed).

////// Downside of the screen.  //////

// Part of the 1st downside

  selfTestPending();          // Self test pending 

// Part of the 2nd downside's 1st part

  FiftyHz();

// Part of the 2nd downside's 2nd part

  empty_box_Downside();

// Battery charge rect with rounded and empty

  battery_icon();

  // Showing battery level.

  display.fillRoundRect(85, 55, 10, 7, 1, KS0108_ON);
  display.display();

  delay(4000);

}



// Two Phase are connected.  Phase difference.

void twoPhaseConnected_Diff () {

 display.clearDisplay();

// Rect parts of the template

// 1 st part of the begining 

  delay(2000);

  display.clearDisplay();

  PhaseB_String();                     // Writing Phase B string
   
// 2 nd Part of the begining

  PhaseA_String();                     // Writing Phase A string


  // When two phase are connected. Add a lightning icon which is filled.

  twoPhaseConnected();          // Filled lightning icon.


  //// Middle of the Screen.

  phaseNotEqual_drawbitmap();   // Phase difference


  //// Add phase difference between B -> A. 

  phaseDiff_B_overA();

////// Downside of the screen.  //////


// Part of the 1st downside

  selfTestPending();          // Self test pending 

// Part of the 2nd downside's 1st part

  FiftyHz();

// Part of the 2nd downside's 2nd part

  empty_box_Downside();

// Battery charge rect with rounded and empty

   battery_icon();

  // Showing battery level.

  display.fillRoundRect(85, 55, 10, 7, 1, KS0108_ON);
  display.display();

  delay(4000);

}




// Template for check probe connection screen. No phase is connected.

void checkProbe_NoPhase() {

  display.clearDisplay();

// 1 st part of the begining 

  delay(2000);

  display.display();

  delay(1000);

  PhaseB_String();
  
  
  lightning_drawbitmap_PhaseB();        /// Drawing lightning icon


// 2 nd Part of the begining


  PhaseA_String();


  lightning_drawbitmap_PhaseA();        /// Drawing lightning icon


///// Middle of the screen.  /////

  checkProbeString();

////// Downside of the screen.  //////


// Part of the 1st downside

  selfTestPending();          // Self test pending 

// Part of the 2nd downside's 1st part

  FiftyHz();

// Part of the 2nd downside's 2nd part

  empty_box_Downside();

// Battery charge rect with rounded and empty

  battery_icon();

  // Showing battery level.

  display.fillRoundRect(85, 55, 10, 7, 1, KS0108_ON);
  display.display();

  delay(4000);

}



// Template for check probe connection screen. Phase A is connected.

void Phase_A_Connected() {

  display.clearDisplay();

// 1 st part of the begining 

  delay(2000);

  display.clearDisplay();


  PhaseB_String();


// 2 nd Part of the begining


  PhaseA_String();


  Phase_AConnectedLightning();

///// Middle of the screen.  /////

  checkProbeString();


////// Downside of the screen.  //////


// Part of the 1st downside

  selfTestPending();          // Self test pending 

// Part of the 2nd downside's 1st part

  FiftyHz();

// Part of the 2nd downside's 2nd part

  empty_box_Downside();

// Battery charge rect with rounded and empty

  battery_icon();

  // Showing battery level.

  display.fillRoundRect(85, 55, 10, 7, 1, KS0108_ON);
  display.display();

  delay(4000);

}



// Template for check probe connection screen. Phase B is connected.

void Phase_B_Connected() {

  display.clearDisplay();

// 1 st part of the begining 

  delay(2000);

  display.clearDisplay();

  PhaseB_String();                     // Phase B string 

// 2 nd Part of the begining

  PhaseA_String();                     // Phase A string 


  Phase_BConnectedLightning();         // Phase B lightning filled icon.

///// Middle of the screen.  /////
 
  checkProbeString();                 // Writing  "check probe" string.


////// Downside of the screen.  //////

// Part of the 1st downside

  selfTestPending();          // Self test pending 

// Part of the 2nd downside's 1st part

  FiftyHz();

// Part of the 2nd downside's 2nd part

  empty_box_Downside();

// Battery charge rect with rounded and empty

  battery_icon();

  // Showing battery level.

  display.fillRoundRect(85, 55, 10, 7, 1, KS0108_ON);
  display.display();

  delay(4000);

}


// First page of the self test page.

void selfTest_False_firstPage() {

display.clearDisplay();

delay(2000);

display.drawRect(0, 0, 128, 10, KS0108_ON);
display.display(); // Update screen with each newly-drawn rectangle

display.setTextSize(0.5);      // Normal 1:1 pixel scale
display.setCursor(40, 2);     // Start at top-left corner
display.write("Self Test");


display.setTextSize(0.5);      // Normal 1:1 pixel scale

display.setTextColor(KS0108_ON);
display.setCursor(0, 15);     // Start at top-left corner
display.write("L1 Voltage");

falseMark(95,10);


display.setTextSize(0.5);      // Normal 1:1 pixel scale

display.setTextColor(KS0108_ON);
display.setCursor(0, 30);     // Start at top-left corner
display.write("L2 Voltage");

falseMark(95,25);

display.setTextSize(0.5);      // Normal 1:1 pixel scale

display.setTextColor(KS0108_ON);
display.setCursor(0, 45);     // Start at top-left corner
display.write("Correct Phase");

falseMark(95,40);

delay(2000);

}


// Second page of the self test page.

void selfTest_False_secondPage() {

display.clearDisplay();

delay(2000);

display.drawRect(0, 0, 128, 10, KS0108_ON);
display.display(); // Update screen with each newly-drawn rectangle

display.setTextSize(0.5);      // Normal 1:1 pixel scale
display.setCursor(40, 2);     // Start at top-left corner
display.write("Self Test");


display.setTextSize(0.5);      // Normal 1:1 pixel scale

display.setTextColor(KS0108_ON);
display.setCursor(0, 15);     // Start at top-left corner
display.write("Incorrect Phase");

falseMark(95,10);

display.setTextSize(0.5);      // Normal 1:1 pixel scale

display.setTextColor(KS0108_ON);
display.setCursor(0, 30);     // Start at top-left corner
display.write("Relationship");

falseMark(95,25);

display.setTextSize(0.5);      // Normal 1:1 pixel scale

display.setTextColor(KS0108_ON);
display.setCursor(0, 45);     // Start at top-left corner
display.write("No Voltage");

falseMark(95,40);

delay(2000);

}



// Self Test false main function

void selfTest_False_Main() {

selfTest_False_firstPage();
delay(2000);
selfTest_False_secondPage();

}


// First page of True self test page.

void selfTest_True_firstPage() {

display.clearDisplay();

delay(2000);

display.drawRect(0, 0, 128, 10, KS0108_ON);
display.display(); // Update screen with each newly-drawn rectangle

display.setTextSize(0.5);      // Normal 1:1 pixel scale
display.setCursor(40, 2);     // Start at top-left corner
display.write("Self Test");

display.setTextSize(0.5);      // Normal 1:1 pixel scale

display.setTextColor(KS0108_ON);
display.setCursor(0, 15);     // Start at top-left corner
display.write("L1 Voltage");

checkMark(95,10);


display.setTextSize(0.5);      // Normal 1:1 pixel scale

display.setTextColor(KS0108_ON);
display.setCursor(0, 30);     // Start at top-left corner
display.write("L2 Voltage");

checkMark(95,25);


display.setTextSize(0.5);      // Normal 1:1 pixel scale

display.setTextColor(KS0108_ON);
display.setCursor(0, 45);     // Start at top-left corner
display.write("Correct Phase");

checkMark(95,40);

delay(2000);

}



// Second page of True self test page.

void selfTest_True_secondPage() {

display.clearDisplay();

delay(2000);

display.drawRect(0, 0, 128, 10, KS0108_ON);
display.display(); // Update screen with each newly-drawn rectangle

display.setTextSize(0.5);      // Normal 1:1 pixel scale
display.setCursor(40, 2);     // Start at top-left corner
display.write("Self Test");


display.setTextSize(0.5);      // Normal 1:1 pixel scale

display.setTextColor(KS0108_ON);
display.setCursor(0, 15);     // Start at top-left corner
display.write("Incorrect Phase");

checkMark(95,10);


display.setTextSize(0.5);      // Normal 1:1 pixel scale

display.setTextColor(KS0108_ON);
display.setCursor(0, 30);     // Start at top-left corner
display.write("Relationship");

checkMark(95,25);


display.setTextSize(0.5);      // Normal 1:1 pixel scale

display.setTextColor(KS0108_ON);
display.setCursor(0, 45);     // Start at top-left corner
display.write("No Voltage");

checkMark(95,40);

delay(2000);

}



// Self Test True main function

void selfTest_True_Main() {

selfTest_True_firstPage();
delay(2000);
selfTest_True_secondPage();

}




// Template for Phase Comparator

void templatedraw(void) {

  display.clearDisplay();

  delay(2000);

  checkProbe_NoPhase();

  Phase_A_Connected();

  Phase_B_Connected();

  twoPhaseConnected_Diff();

  twoPhaseConnected_NoDiff();

  selfTest_False_Main();

  selfTest_True_Main();

  delay(4000);

  display.clearDisplay();


}
