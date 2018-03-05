#include "FastLED.h"

FASTLED_USING_NAMESPACE



#define DATA_PIN    6
#define LED_TYPE    WS2811
#define COLOR_ORDER RGB
#define NUM_LEDS    100
CRGB leds[NUM_LEDS];

#define BRIGHTNESS         100
#define FRAMES_PER_SECOND  120


void setup() {
  delay(1000); // 3 second delay for recovery

  // tell FastLED about the LED strip configuration
  FastLED.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  Serial.begin(9600);
  // set master brightness control
  FastLED.setBrightness(BRIGHTNESS);
}



// List of patterns to cycle through.  Each is defined as a separate function below.
typedef void (*SimplePatternList[])();
SimplePatternList gPatterns = { my_pattern };

uint8_t gCurrentPatternNumber = 0; // Index number of which pattern is current
uint8_t gHue = 0; // rotating "base color" used by many of the patterns

void loop()
{
  // Call the current pattern function once, updating the 'leds' array
  gPatterns[gCurrentPatternNumber]();

  // send the 'leds' array out to the actual LED strip
  FastLED.show();
  // insert a delay to keep the framerate modest
  FastLED.delay(1000 / FRAMES_PER_SECOND);

  // do some periodic updates
  EVERY_N_MILLISECONDS( 20 ) {
    gHue++;  // slowly cycle the "base color" through the rainbow
  }
  EVERY_N_SECONDS( 20 ) {
    nextPattern();  // change patterns periodically
  }
}

#define ARRAY_SIZE(A) (sizeof(A) / sizeof((A)[0]))


void nextPattern()
{
  // add one to the current pattern number, and wrap around at the end
  gCurrentPatternNumber = (gCurrentPatternNumber + 1) % ARRAY_SIZE( gPatterns);
}

int col=0;
int centre=NUM_LEDS/2;
int colour=0;
int aHue=0;
int sat=255;

void my_pattern() {
fill_rainbow( leds, NUM_LEDS, gHue, 2);
}




//void loop() {
//   // Move a single white led
//   for(int whiteLed = 0; whiteLed < NUM_LEDS; whiteLed = whiteLed + 1) {
//      // Turn our current led on to white, then show the leds
//      leds[whiteLed] = CRGB::White;
//
//      // Show the leds (only one of which is set to white, from above)
//      FastLED.show();
//
//      // Wait a little bit
//      delay(100);
//
//      // Turn our current led back to black for the next loop around
//      leds[whiteLed] = CRGB::Black;
//   }


