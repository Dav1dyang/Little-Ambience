/*
This code is for creating simple gradient with neopixel strips.
Made with the modification from Adafruit's NeoPixel Library Examples. 
This is definately not the most efficient way code gradient, but it get the job done. For more details, please visit: 

Details about neopixel setup: 
https://learn.adafruit.com/adafruit-neopixel-uberguide/

Created by David Yang with Shirley Wu's Help 03/29/2023
*/

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>  // Required for 16 MHz Adafruit Trinket
#endif

// Which pin on the Arduino is connected to the NeoPixels?
#define LED_PIN 38

// How many NeoPixels are attached to the Arduino?
#define LED_COUNT 50

// How many pixels are on the X and Y axis of therectangle?
#define LED_X 9
#define LED_Y 16
#define LED_Height 20
#define LED_Length 12

// How many colors the gradient will cycle through?
#define numColors 120

// Declare our NeoPixel strip object:
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);
// Argument 1 = Number of pixels in NeoPixel strip
// Argument 2 = Arduino pin number (most are valid)
// Argument 3 = Pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)

// define the array to storge the pixel position
int top[LED_X] = {};
int right[LED_Y] = {};
int left[LED_Y] = {};
int bottom[LED_X] = {};

int timestep = 0;
// Variables to control the changes in the gradient function
int increment = numColors / LED_Height;  // the increment of each pixels based on the total height on the LED grid

int colorsSunset[numColors][3] = { { 141, 192, 204 }, { 143, 189, 202 }, { 143, 188, 201 }, { 144, 185, 199 }, { 145, 183, 198 }, { 145, 180, 196 }, { 146, 177, 195 }, { 146, 175, 193 }, { 147, 172, 191 }, { 148, 170, 190 }, { 148, 168, 189 }, { 149, 165, 188 }, { 150, 163, 186 }, { 150, 160, 185 }, { 151, 158, 183 }, { 152, 155, 182 }, { 152, 152, 180 }, { 153, 150, 178 }, { 153, 148, 177 }, { 154, 146, 175 }, { 155, 143, 174 }, { 155, 140, 172 }, { 156, 138, 171 }, { 157, 135, 169 }, { 157, 132, 167 }, { 158, 130, 167 }, { 159, 127, 165 }, { 159, 126, 164 }, { 160, 123, 162 }, { 160, 120, 161 }, { 160, 118, 159 }, { 161, 115, 158 }, { 161, 113, 156 }, { 162, 110, 154 }, { 163, 107, 153 }, { 163, 105, 151 }, { 164, 102, 150 }, { 165, 100, 148 }, { 165, 97, 147 }, { 165, 94, 146 }, { 166, 92, 144 }, { 166, 89, 143 }, { 167, 87, 141 }, { 167, 84, 140 }, { 168, 81, 138 }, { 169, 79, 137 }, { 169, 76, 135 }, { 169, 74, 134 }, { 170, 70, 132 }, { 170, 67, 130 }, { 171, 65, 129 }, { 172, 61, 128 }, { 172, 59, 127 }, { 172, 55, 125 }, { 172, 52, 124 }, { 173, 49, 122 }, { 174, 45, 120 }, { 174, 42, 119 }, { 175, 38, 117 }, { 176, 33, 116 }, { 176, 33, 116 }, { 175, 38, 117 }, { 174, 42, 119 }, { 174, 45, 120 }, { 173, 49, 122 }, { 172, 52, 124 }, { 172, 55, 125 }, { 172, 59, 127 }, { 172, 61, 128 }, { 171, 65, 129 }, { 170, 67, 130 }, { 170, 70, 132 }, { 169, 74, 134 }, { 169, 76, 135 }, { 169, 79, 137 }, { 168, 81, 138 }, { 167, 84, 140 }, { 167, 87, 141 }, { 166, 89, 143 }, { 166, 92, 144 }, { 165, 94, 146 }, { 165, 97, 147 }, { 165, 100, 148 }, { 164, 102, 150 }, { 163, 105, 151 }, { 163, 107, 153 }, { 162, 110, 154 }, { 161, 113, 156 }, { 161, 115, 158 }, { 160, 118, 159 }, { 160, 120, 161 }, { 160, 123, 162 }, { 159, 126, 164 }, { 159, 127, 165 }, { 158, 130, 167 }, { 157, 132, 167 }, { 157, 135, 169 }, { 156, 138, 171 }, { 155, 140, 172 }, { 155, 143, 174 }, { 154, 146, 175 }, { 153, 148, 177 }, { 153, 150, 178 }, { 152, 152, 180 }, { 152, 155, 182 }, { 151, 158, 183 }, { 150, 160, 185 }, { 150, 163, 186 }, { 149, 165, 188 }, { 148, 168, 189 }, { 148, 170, 190 }, { 147, 172, 191 }, { 146, 175, 193 }, { 146, 177, 195 }, { 145, 180, 196 }, { 145, 183, 198 }, { 144, 185, 199 }, { 143, 188, 201 }, { 143, 189, 202 }, { 141, 192, 204 } };

// setup() function -- runs once at startup --------------------------------

void setup() {

// leaving this here just in case this is applied to ATTiny85.
// These lines are specifically to support the Adafruit Trinket 5V 16 MHz.
// Any other board, you can remove this part (but no harm leaving it):
#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif
  // END of Trinket-specific code.

  strip.begin();            // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.show();             // Turn OFF all pixels ASAP
  strip.setBrightness(30);  // Set BRIGHTNESS to about 1/5 (max = 255)

  // Generate Array for the LED Rectangle Setup - assign pixel positions base on 4 sides of the rect
  for (int xAxisShift = 0; xAxisShift < LED_X; xAxisShift += 1)  //Assigned LED on the x axis
  {
    top[xAxisShift] = LED_Y + xAxisShift;
    bottom[xAxisShift] = LED_Y * 2 + LED_X + xAxisShift;
  }

  for (int yAxisShift = 0; yAxisShift < LED_Y; yAxisShift += 1)  //Assigned LED on the y axis
  {
    right[yAxisShift] = yAxisShift;
    left[yAxisShift] = LED_Y * 2 + LED_X - 1 - yAxisShift;
  }
}

// loop() function -- runs repeatedly as long as board is on ---------------

void loop() {

  gradient(colorsSunset);
  timestep += 1;
  delay(15);
}

// functions for creating animated effects -----------------

void gradient(int colors[numColors][3]) {

  //strip.clear();  // Set all pixel colors to 'off'

  // for each pixel

  // for (int timestep = 0; timestep < numColors; timestep++) { // increased steps in each loop consistantly

  for (int pos = 0; pos < LED_Height; pos++) {

    int colorIndex = (pos * increment + timestep) % numColors; // NEEDS CHANGE
    colorIndex = max(min(colorIndex, numColors), 0); // bound to [0, 120]
    int color = strip.Color(colors[colorIndex][0], colors[colorIndex][1], colors[colorIndex][2]);

    if (pos == 0) {
      for (int pixel = 0; pixel < LED_X; pixel++) {
        strip.setPixelColor(top[pixel], color);
      }
    } else if (pos == 19) {
      for (int pixel = 0; pixel < LED_X; pixel++) {
        strip.setPixelColor(bottom[pixel], color);
      }
    }

    if (pos < LED_Y) {
      strip.setPixelColor(left[pos], color);
      strip.setPixelColor(right[pos], color);
    }

    // }
  }

  strip.show();
}
