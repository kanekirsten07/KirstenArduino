#include <Adafruit_NeoPixel.h>

// 
/*
    Name:       RagnarosEyes.ino
    Created:	10/2/2018 1:18:53 AM
    Author:     LF-A\Kirsten
*/
//fades all pixels subtly
//code by Tony Sherwood for Adafruit Industries


#define PIN 1
// Parameter 1 = number of pixels in strip
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(14, PIN, NEO_GRB + NEO_KHZ800);

int alpha; // Current value of the pixels
int dir = 1; // Direction of the pixels... 1 = getting brighter, 0 = getting dimmer
int flip; // Randomly flip the direction every once in a while
int minAlpha = 25; // Min value of brightness
int maxAlpha = 100; // Max value of brightness
int alphaDelta = 5; // Delta of brightness between times through the loop
long randNumber;

void setup() {
	strip.begin();
	strip.show(); // Initialize all pixels to 'off'
}

void flicker()
{
  flip = random(32);
  if(flip > 20) {
    dir = 1 - dir;
  }
  // Some example procedures showing how to display to the pixels:
  if (dir == 1) {
    alpha += alphaDelta;
  }
  if (dir == 0) {
    alpha -= alphaDelta;
  }
  if (alpha < minAlpha) {
    alpha = minAlpha;
    dir = 1;
  }
  if (alpha > maxAlpha) {
    alpha = maxAlpha;
    dir = 0;
  }
}

void loop() {

flicker();

  //colorSet(strip.Color(alpha, 0, 0)); // Red

  //colorSet(strip.Color(alpha, alpha/2, 0)); // Yellow
  
 colorSet(strip.Color(alpha, alpha/5, 0)); // Orange 

 
}

// Fill the dots one after the other with a color
void colorSet(uint32_t c) {
	for (uint16_t i = 0; i<strip.numPixels(); i++) {
		strip.setPixelColor(i, c);
		strip.show();
	}
}



