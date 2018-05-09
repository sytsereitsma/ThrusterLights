// NeoPixel Ring simple sketch (c) 2013 Shae Erisson
// released under the GPLv3 license to match the rest of the AdaFruit NeoPixel library

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

const int kThrusterAPin (4);
const int kThrusterBPin (5);
const int kThrusterCPin (6);
const uint8_t kPixelsPerThruster (7);

struct Thruster {
    Thruster (int inPin) :
        mPixels (Adafruit_NeoPixel (kPixelsPerThruster, inPin, NEO_GRB + NEO_KHZ800))
    {
        mPixels.begin();
    }

    void Update (uint16_t inIteration) {
        const uint8_t kCenterPixel (0);

        for(uint8_t pixel = 0; pixel < kPixelsPerThruster; ++pixel){
            if (pixel == kCenterPixel) {
                uint16_t intensity = (inIteration * 3) % 512;
                if (intensity > 255) {
                    intensity = 511 - intensity;
                }

                mPixels.setPixelColor(pixel, mPixels.Color(0, 0, intensity));
            }
            else {
                const uint8_t divisor ((rand () % 10) + 1);
                uint8_t red = 255 / divisor;
                uint8_t green = 0x30 / divisor;
                mPixels.setPixelColor(pixel, mPixels.Color(red, green, 0));
            }

            mPixels.show();
        }
    }

    Adafruit_NeoPixel mPixels;
};

Thruster thrusterA (kThrusterAPin);
Thruster thrusterB (kThrusterBPin);
Thruster thrusterC (kThrusterCPin);

int delayval = 500; // delay for half a second
uint16_t iteration = 0;

void setup() {
  // This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket
#if defined (__AVR_ATtiny85__)
  if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
#endif
  // End of trinket special code
}


void loop() {
  thrusterA.Update (iteration);
  thrusterB.Update (iteration);
  thrusterC.Update (iteration);
  ++iteration;
}