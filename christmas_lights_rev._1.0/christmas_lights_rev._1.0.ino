/*
 * LED Strip - Christmas Theme
 *
 * by: Andrei Grichine
 * 12/21/2015
 * CC by-sa v3.0 - http://creativecommons.org/licenses/by-sa/3.0/

 * Portions of this code from:
 * "strandtest" by Adafruit - https://github.com/adafruit/LPD8806
 *
 */

#include "LPD8806.h"
#include "SPI.h"

int i,j;

// Number of RGB LEDs in strand:
int nLEDs = 52; // or 160, each meter has 32 LEDs, and I use this code for a 1 meter strip as well, so I just change the # of strips here

// Chose 2 pins for output; can be any valid output pins:
int dataPin  = 2; // blue wire
int clockPin = 3; // green wire
LPD8806 strip = LPD8806(nLEDs, dataPin, clockPin);

void setup() {
  // Start up the LED strip
  strip.begin();

  // Update the strip, to start they are all 'off'
  strip.show();
}

void loop() {

  cylonEye(2,0); //red
//  delay(1000);
  cylonEye(2,1); //green
//  delay(1000);
  cylonEye(2,2); //blue
//  delay(1000);

  colorChase(strip.Color(127,   0,   0), 25, 1, 1); // Red
  colorChase(strip.Color(127,   0,   0), 25, -1, 1); // Red
  colorChase(strip.Color(  0, 127,   0), 25, 1, 1); // Green
  colorChase(strip.Color(  0, 127,   0), 25, -1, 1); // Green
  colorChase(strip.Color(  0, 0,   127), 25, 1, 1); // Blue
  colorChase(strip.Color(  0, 0,   127), 25, -1, 1); // Blue
  
//  colorWipe(strip.Color(127,   0,   0), 5, 1, 1);  // Red
  colorWipe(strip.Color(0,   0,   127), 5, -1, 2); // Blue
  colorWipe(strip.Color(  0, 127,   0), 5, -1, 1);  // Green
  colorWipe(strip.Color(127,   0,   0), 5, 1, 2); // Red
  delay(1000);
  
//  alternateBlink(500, 50);
  fadeRedtoGreen(100);
  fadeGreentoBlue(100);
  fadeBluetoRed(100);
  delay(200);
}

/* Sketch functions */

// Chase one dot down the full strip.
void colorChase(uint32_t c, uint8_t wait, int dir, int interval) {
  int i;

  // Start by turning all pixels off:
  for(i=0; i<strip.numPixels(); i++) strip.setPixelColor(i, 0);

  // Then display one pixel at a time:
  if (dir == 1) {
    for(i=0; i<strip.numPixels(); i += interval) {
      strip.setPixelColor(i, c); // Set new pixel 'on'
      strip.show();              // Refresh LED states
      strip.setPixelColor(i, 0); // Erase pixel, but don't refresh!
      delay(wait);
    }  
  } else {
    for(i=(strip.numPixels()-1); i>=0; i -= interval) { // We take one off the value to eliminate a 'double flash'
      strip.setPixelColor(i, c); // Set new pixel 'on'
      strip.show();              // Refresh LED states
      strip.setPixelColor(i, 0); // Erase pixel, but don't refresh!
      delay(wait);
    }     
  }

  strip.show(); // Refresh to turn off last pixel
}

// Fill the dots progressively along the strip.
void colorWipe(uint32_t c, uint8_t wait, int dir, int interval) {
  int i;

  if (dir == 1) {
    for (i=0; i < strip.numPixels(); i += interval) {
      strip.setPixelColor(i, c);
      strip.show();
      delay(wait);
    }
  } else {
    for(i=(strip.numPixels()-1); i>=0; i -= interval) { // We take one off the value to eliminate a 'double flash'
      strip.setPixelColor(i, c);
      strip.show();
      delay(wait);
    }
  }
}

void alternateBlink (uint8_t wait, int duration) {
  uint32_t stripColorArray[strip.numPixels()]; // We need somewhere to store the LEDs
  uint32_t pixelTest;
  
  for (i=0; i<strip.numPixels(); i++) {
    stripColorArray[i] = strip.getPixelColor(i);
  }
  
  // first pass thru to turn off alternate pixels
  for (i=0; i<strip.numPixels(); i += 2) {
        strip.setPixelColor(i, 0); // Erase pixel, but don't refresh!
  }
  strip.show();
  delay(wait);
  
  // now keep passing thru alternating blinks
  for (j=0; j<duration; j++) {
    // pass thru the strip and check if the pixel is on or off and flip accordingly
    for (i=0; i<strip.numPixels(); i++) {
      pixelTest = strip.getPixelColor(i);
      if (pixelTest == 0) {
        strip.setPixelColor(i, stripColorArray[i]); // restore the color from the array
      } else {
        strip.setPixelColor(i, 0); // erase pixel
      }
    }
    strip.show();
    delay(wait);
  }
}

void fadeRedtoGreen(uint8_t wait) {
  for (i=0; i < 127; i++) {
    for (j=0; j < strip.numPixels(); j++){
      strip.setPixelColor(j, 127-i,i,0);
    }
    strip.show();
    delay(wait);
  }
}
void fadeGreentoBlue(uint8_t wait) {
  for (i=0; i < 127; i++) {
    for (j=0; j < strip.numPixels(); j++){
      strip.setPixelColor(j, 0,127-i,i);
    }
    strip.show();
    delay(wait);
  }
}
void fadeBluetoRed(uint8_t wait) {
  for (i=0; i < 127; i++) {
    for (j=0; j < strip.numPixels(); j++){
      strip.setPixelColor(j, i,0,127-i);
    }
    strip.show();
    delay(wait);
  }
}  

void cylonEye(uint8_t numberOfCicles, int color) {

int pos = 0, dir = 1; // Position, direction of "eye"
  strip.show();

int jjj;
      for (jjj=0; jjj < strip.numPixels()*numberOfCicles-9; jjj++){ //-9 is a hack :( to alter lights position

  int jj;

  // Draw 5 pixels centered on pos.  setPixelColor() will clip any
  // pixels off the ends of the strip, we don't need to watch for that.
 switch (color) {
    case 1:
  strip.setPixelColor(pos - 2, 0,1,0); // Dark green
  strip.setPixelColor(pos - 1, 0,20,0); // Medium green
  strip.setPixelColor(pos    , 0,127,0); // Center pixel is brightest
  strip.setPixelColor(pos + 1, 0,20,0); // Medium green
  strip.setPixelColor(pos + 2, 0,1,0); // Dark green
      break;
    case 2:
  strip.setPixelColor(pos - 2, 0,0,1); // Dark blue
  strip.setPixelColor(pos - 1, 0,0,20); // Medium blue
  strip.setPixelColor(pos    , 0,0,127); // Center pixel is brightest
  strip.setPixelColor(pos + 1, 0,0,20); // Medium blue
  strip.setPixelColor(pos + 2, 0,0,1); // Dark blue
      break;
    default: 
  strip.setPixelColor(pos - 2, 1,0,0); // Dark red
  strip.setPixelColor(pos - 1, 20,0,0); // Medium red
  strip.setPixelColor(pos    , 127,0,0); // Center pixel is brightest
  strip.setPixelColor(pos + 1, 20,0,0); // Medium red
  strip.setPixelColor(pos + 2, 1,0,0); // Dark red
    break;
  }
 
  strip.show();
  delay(30);
 
  // Rather than being sneaky and erasing just the tail pixel,
  // it's easier to erase it all and draw a new one next time.
  for(jj=-2; jj<= 2; jj++) strip.setPixelColor(pos+jj, 0);
 
  // Bounce off ends of strip
  pos += dir;
  if(pos < 0) {
    pos = 1;
    dir = -dir;
  } else if(pos >= strip.numPixels()) {
    pos = strip.numPixels() - 2;
    dir = -dir;
  }
      }
}

