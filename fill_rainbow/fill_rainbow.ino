#include "FastLED.h"

FASTLED_USING_NAMESPACE

#define DATA_PIN    6
#define LED_TYPE    WS2811
#define COLOR_ORDER RGB
#define NUM_LEDS    50
CRGB leds[NUM_LEDS];

#define BRIGHTNESS          50
#define FRAMES_PER_SECOND  120

//uint8_t gHue = 0;
int gHue = 0;
int pos = 1;
int on = 0;

void setup() {
  delay(1000); // 3 second delay for recovery
  FastLED.addLeds<LED_TYPE,DATA_PIN,COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);

  // set master brightness control
  FastLED.setBrightness(BRIGHTNESS);
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
}

// the loop routine runs over and over again forever:
void loop() {
  

  //fadeToBlackBy( leds, NUM_LEDS, 100);
  for(int led = NUM_LEDS; led >= 0; led = led - 1) {
      gHue = gHue+10;
      leds[led] = CHSV(gHue, 255, 255);
      FastLED.show();

      delay(10);

      if (led < pos) {
        continue;
      } else {
      leds[led] = CRGB::Black;
      }

   }
  pos ++ ;
  if (pos > NUM_LEDS) {
    pos = 1;
    fadeToBlackBy( leds, NUM_LEDS, 100);
  }
}
