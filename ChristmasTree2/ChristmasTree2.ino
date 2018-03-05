#include "FastLED.h"

FASTLED_USING_NAMESPACE

// FastLED "100-lines-of-code" demo reel, showing just a few 
// of the kinds of animation patterns you can quickly and easily 
// compose using FastLED.  
//
// This example also shows one easy way to define multiple 
// animations patterns and have them automatically rotate.
//
// -Mark Kriegsman, December 2014

#if defined(FASTLED_VERSION) && (FASTLED_VERSION < 3001000)
#warning "Requires FastLED 3.1 or later; check github for latest code."
#endif

#define DATA_PIN    3
//#define CLK_PIN   4
#define LED_TYPE    WS2811
#define COLOR_ORDER RGB
#define NUM_LEDS    82
CRGB leds[NUM_LEDS];

#define BRIGHTNESS          80
#define FRAMES_PER_SECOND  120
int centre = NUM_LEDS / 2;

void setup() {
  delay(3000); // 3 second delay for recovery
  
  // tell FastLED about the LED strip configuration
  FastLED.addLeds<LED_TYPE,DATA_PIN,COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);

  // set master brightness control
  FastLED.setBrightness(BRIGHTNESS);
}


// List of patterns to cycle through.  Each is defined as a separate function below.
typedef void (*SimplePatternList[])();
SimplePatternList gPatterns = { colour_chaser, mini_rainbows, colour_cycle, appearing_rainbow, rainbow, rainbowWithGlitter, blue_snow, confetti };

uint8_t gCurrentPatternNumber = 0; // Index number of which pattern is current
uint8_t gHue = 0; // rotating "base color" used by many of the patterns
  
void loop()
{
  // Call the current pattern function once, updating the 'leds' array
  gPatterns[gCurrentPatternNumber]();

  // send the 'leds' array out to the actual LED strip
  FastLED.show();  
  // insert a delay to keep the framerate modest
  FastLED.delay(1000/FRAMES_PER_SECOND); 

  // do some periodic updates
  EVERY_N_MILLISECONDS( 20 ) { gHue++; } // slowly cycle the "base color" through the rainbow
  EVERY_N_SECONDS( 20 ) { nextPattern(); } // change patterns periodically
}

#define ARRAY_SIZE(A) (sizeof(A) / sizeof((A)[0]))

void nextPattern()
{
  // add one to the current pattern number, and wrap around at the end
  gCurrentPatternNumber = (gCurrentPatternNumber + 1) % ARRAY_SIZE( gPatterns);
}

int colour=0;
int colour1=0;
int colour2=55;


void blue_snow()
{
  fadeToBlackBy( leds, NUM_LEDS, 5);
    int sat = random(255);
    leds[ random(NUM_LEDS) ] = CHSV(160, sat, 255);
    FastLED.show();
    delay(25);
}

int hue=0;

void colour_chaser() {
  for (int i=0;i<10;i++) {
    for (int j=i;j<NUM_LEDS;j+=10) {
        fill_solid(leds + j, 1, CHSV(hue, 255, 255));
        FastLED.show() ;
        fadeToBlackBy( leds, NUM_LEDS, 5);
        hue+=10;
    }
    delay(50);
  }
}

int MyHue=0;
void mini_rainbows()
{
  for (int i=0;i<NUM_LEDS-7;i+=8) {
    fill_gradient(leds,i,CHSV(MyHue,255,255),i+7,CHSV(MyHue+224,255,255),FORWARD_HUES);
  }
  fill_solid(leds+80, 1, CHSV(MyHue, 255, 255));
  fill_solid(leds+81, 1, CHSV(MyHue+32, 255, 255));
  FastLED.show();
  MyHue+=5;
  delay(10);
}

int aHue=0;
void appearing_rainbow()
{
  fill_gradient(leds, 0, CHSV(0, 255, 255), NUM_LEDS-1, CHSV(aHue, 255, 255), FORWARD_HUES);
  FastLED.show();
  aHue ++ ;
  delay(10);
}

void colour_cycle()
{
  for (int i=0;i<256;i++) {
    fill_solid(leds, NUM_LEDS,CHSV(i,255,255));
    FastLED.show();
    delay(30);
  }
}
void rainbow() 
{
  // FastLED's built-in rainbow generator
  fill_rainbow( leds, NUM_LEDS, gHue, 7);
}

void rainbowWithGlitter() 
{
  // built-in FastLED rainbow, plus some random sparkly glitter
  rainbow();
  addGlitter(80);
}

void addGlitter( fract8 chanceOfGlitter) 
{
  if( random8() < chanceOfGlitter) {
    leds[ random16(NUM_LEDS) ] += CRGB::White;
  }
}

void confetti() 
{
  // random colored speckles that blink in and fade smoothly
  fadeToBlackBy( leds, NUM_LEDS, 10);
  int pos = random16(NUM_LEDS);
  leds[pos] += CHSV( gHue + random8(64), 200, 255);
}



