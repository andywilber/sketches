#include "FastLED.h"

#define DATA_PIN    6

#define LED_TYPE    WS2811
#define COLOR_ORDER RGB
#define NUM_LEDS    50
CRGB leds[NUM_LEDS];

#define BRIGHTNESS          50
#define FRAMES_PER_SECOND  120

void setup() {
  delay(3000); // 3 second delay for recovery
  
  // tell FastLED about the LED strip configuration
  FastLED.addLeds<LED_TYPE,DATA_PIN,COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);

  // set master brightness control
  FastLED.setBrightness(BRIGHTNESS);
}

//const gHue = 0;


void loop() {
   fill_gradient(leds,0,CHSV(10,255,255),NUM_LEDS,CHSV(255,155,255),SHORTEST_HUES);
   FastLED.show(); 
   delay(1000);
   fill_gradient(leds,0,CHSV(255,255,255),NUM_LEDS,CHSV(10,25,155),SHORTEST_HUES);
   FastLED.show(); 
   delay(1000);
   fill_gradient(leds,0,CHSV(55,205,155),NUM_LEDS,CHSV(155,255,255),SHORTEST_HUES);
   FastLED.show(); 
   delay(1000);

}
