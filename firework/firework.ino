#include "FastLED.h"

FASTLED_USING_NAMESPACE



#define DATA_PIN    6
#define LED_TYPE    WS2811
#define COLOR_ORDER RGB
#define NUM_LEDS    100
CRGB leds[NUM_LEDS];

#define BRIGHTNESS          200
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


void my_pattern() {
  //Ignition
  for (int ig=1;ig<15;ig++) {
    fill_gradient(leds, 0, CHSV(0, 255, 255), random(0,5), CHSV(160, 255, 255), FORWARD_HUES);
    FastLED.show() ;
    delay(50);
    fadeToBlackBy( leds, NUM_LEDS, 155);
  } 
   
  //Rocket trail
  int dly=0;
  int val=255;
  int hue=random(255);
  for (int i = 0; i < NUM_LEDS-25; i++) {
    fill_solid(leds + i, 5, CHSV(32, 255, val));
    FastLED.show() ;
    dly+=1;
    val-=2;
    fadeToBlackBy( leds, NUM_LEDS, 155);
    delay(dly);
  }
  int i=NUM_LEDS-25;
  dly=5;
  int sat=255;
  val=255;
  //Rocket explosion
  for (int j=1; j<30;j+=2) {
    fill_solid(leds + i, j, CHSV(hue, sat, val));
    
    //sparkle
    leds[ random(NUM_LEDS/3,NUM_LEDS) ] += CRGB::White;
    fadeToBlackBy( leds, NUM_LEDS, 25);
    FastLED.show();
    i--;
    hue+=5;
    sat-=10;
    val-=20;
    dly+=15;
    delay(dly);
  }
  //Fade out all
  for (int k=1; k<20; k++) {
    fadeToBlackBy( leds, NUM_LEDS, 50);
    FastLED.show();
    delay(30);
  }
  delay(100);
}


