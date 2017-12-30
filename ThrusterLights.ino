// NeoPixel Ring simple sketch (c) 2013 Shae Erisson
// released under the GPLv3 license to match the rest of the AdaFruit NeoPixel library

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

// Which pin on the Arduino is connected to the NeoPixels?
// On a Trinket or Gemma we suggest changing this to 1
#define PIN            6

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS      7

// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
// Note that for older NeoPixel strips you might need to change the third parameter--see the strandtest
// example for more information on possible values.
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

int delayval = 500; // delay for half a second
uint16_t iteration = 0;

void setup() {
  // This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket
#if defined (__AVR_ATtiny85__)
  if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
#endif
  // End of trinket special code

  pixels.begin(); // This initializes the NeoPixel library.
}

void loop() {
  const uint8_t kIntensity [6] = {0, 25, 51, 76, 102, 127};

  // For a set of NeoPixels the first NeoPixel is 0, second is 1, all the way up to the count of pixels minus one.
  for(int pixel = 0; pixel < NUMPIXELS; ++pixel){
    if (pixel == 0) {
        uint16_t intensity = (iteration * 2) % 512;
        if (intensity > 255) {
            intensity = 511 - intensity;
        }

        pixels.setPixelColor(pixel, pixels.Color(0, 0, intensity));
    }
    else {
        int intensityIndex = ((pixel - 1) + iteration) % 6;
        int intensity = kIntensity [intensityIndex];
        pixels.setPixelColor(pixel, pixels.Color(intensity, 0, 0));
    }
    pixels.show(); // This sends the updated pixel color to the hardware.
    delay(20);
  }

  ++iteration;
}