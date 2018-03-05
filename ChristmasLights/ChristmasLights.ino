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

#define DATA_PIN    6
#define LED_TYPE    WS2811
#define COLOR_ORDER RGB
#define NUM_LEDS    168
CRGB leds[NUM_LEDS];


#define BRIGHTNESS          150
#define FRAMES_PER_SECOND  120

int pos = 1;
int on = 0;
int aHue = 0;
int j = 0;
int centre = NUM_LEDS / 2;
int colour = 0;
CRGB clr1;
CRGB clr2;
uint8_t speed;
uint8_t loc1;
uint8_t loc2;
uint8_t ran1;
uint8_t ran2;

void setup() {
  delay(3000); // 3 second delay for recovery

  // tell FastLED about the LED strip configuration
  FastLED.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);

  // set master brightness control
  FastLED.setBrightness(BRIGHTNESS);

  Serial.begin(9600);
}


// List of patterns to cycle through.  Each is defined as a separate function below.
typedef void (*SimplePatternList[])();
SimplePatternList gPatterns = { colour_chaser, double_out, quad_rainbow, blendwave, rainbow_beat, blendme,
in_from_centre, sliding_rainbow, appearing_rainbow, rainbow, rainbowWithGlitter, blue_snow, confetti,
sinelon, half_cylon, cylon, juggle, bpm };

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
  gCurrentPatternNumber = (gCurrentPatternNumber + 1) % ARRAY_SIZE( gPatterns);;
}

int hue=0;

void colour_chaser() {
  for (int i=0;i<10;i++) {
    for (int j=i;j<NUM_LEDS;j+=10) {
        fill_solid(leds + j, 1, CHSV(hue, 255, 255));
        FastLED.show() ;
        fadeToBlackBy( leds, NUM_LEDS, 10);
        hue+=50;
    }
    delay(25);
  }
}


int colour1=0;
int colour2=55;

void double_out() {
  int j1 = NUM_LEDS * .25;
  int j2 = NUM_LEDS * .75;


  colour1 += 55;
  colour2 += 55;
  for (int i = 2; i <= NUM_LEDS / 2; i += 2) {
    j1--;
    j2--;

    fadeToBlackBy( leds, NUM_LEDS, 10);
    fill_solid(leds + j1, i, CHSV(colour1, 255, 255));
    fill_solid(leds + j2, i, CHSV(colour2, 255, 255));

    FastLED.show();
    delay(50);
  }
}

int sHue = 0;
int eHue = 200;

void quad_rainbow() {

  fill_gradient(leds, 0, CHSV(sHue, 255, 255), NUM_LEDS / 4 - 1, CHSV(eHue, 255, 255), FORWARD_HUES);
  fill_gradient(leds, NUM_LEDS / 4, CHSV(eHue, 255, 255), NUM_LEDS / 2 - 1, CHSV(sHue, 255, 255), BACKWARD_HUES);

  fill_gradient(leds, NUM_LEDS / 2, CHSV(sHue, 255, 255), NUM_LEDS * .75 - 1, CHSV(eHue, 255, 255), FORWARD_HUES);
  fill_gradient(leds, NUM_LEDS * .75, CHSV(eHue, 255, 255), NUM_LEDS - 1, CHSV(sHue, 255, 255), BACKWARD_HUES);

  FastLED.show();

  sHue += 2 ;
  eHue += 2;
}

void blendwave() {

  speed = beatsin8(6, 0, 255);

  clr1 = blend(CHSV(beatsin8(3, 0, 255), 255, 255), CHSV(beatsin8(4, 0, 255), 255, 255), speed);
  clr2 = blend(CHSV(beatsin8(4, 0, 255), 255, 255), CHSV(beatsin8(3, 0, 255), 255, 255), speed);

  loc1 = beatsin8(10, 0, NUM_LEDS - 1);

  fill_gradient_RGB(leds, 0, clr2, loc1, clr1);
  fill_gradient_RGB(leds, loc1, clr2, NUM_LEDS - 1, clr1);
  FastLED.show();

}

void rainbow_beat() {

  uint8_t beatA = beatsin8(17, 0, 255);                        // Starting hue
  uint8_t beatB = beatsin8(13, 0, 255);
  fill_rainbow(leds, NUM_LEDS, (beatA + beatB) / 2, 8);        // Use FastLED's fill_rainbow routine.

}

void blendme() {
  uint8_t starthue = beatsin8(20, 0, 255);
  uint8_t endhue = beatsin8(35, 0, 255);
  if (starthue < endhue) {
    fill_gradient(leds, NUM_LEDS, CHSV(starthue, 255, 255), CHSV(endhue, 255, 255), FORWARD_HUES); // If we don't have this, the colour fill will flip around
  } else {
    fill_gradient(leds, NUM_LEDS, CHSV(starthue, 255, 255), CHSV(endhue, 255, 255), BACKWARD_HUES);
  }
}

void in_from_centre()
{
  int j1 = centre;
  colour += 55;
  for (int i = 2; i <= NUM_LEDS; i += 2) {
    j1--;

    fadeToBlackBy( leds, NUM_LEDS, 10);
    fill_solid(leds + j1, i, CHSV(colour, 255, 255));

    FastLED.show();
    delay(20);
  }
}

void appearing_rainbow()
{
  fill_gradient(leds, 0, CHSV(0, 255, 255), NUM_LEDS-1, CHSV(aHue, 255, 255), FORWARD_HUES);
  FastLED.show();
  aHue ++ ;
  delay(10);
}

void sliding_rainbow()
{
  for (int i = 0; i < NUM_LEDS - 1; i++) {
    fill_gradient(leds, 0, CHSV(0, 255, 255), i, CHSV(255, 255, 255), FORWARD_HUES);
    FastLED.show();
    delay(40);
  }

  for (int i = 1; i < NUM_LEDS - 1; i++) {
    fill_gradient(leds, i, CHSV(0, 255, 255), NUM_LEDS-1, CHSV(255, 255, 255), FORWARD_HUES);
    FastLED.show();
    j = i - 1;
    leds[j] = CRGB::Black;
    FastLED.show();
    delay(40);
  }
  leds[NUM_LEDS - 1] = CRGB::Black;

  for (int i = NUM_LEDS - 1; i >= 0; i--) {
    fill_gradient(leds, i, CHSV(0, 255, 255), NUM_LEDS-1, CHSV(255, 255, 255), FORWARD_HUES);
    FastLED.show();
    delay(40);
  }

  for (int i = NUM_LEDS - 1; i >= 0; i--) {
    fill_gradient(leds, 0, CHSV(0, 255, 255), i, CHSV(255, 255, 255), FORWARD_HUES);
    FastLED.show();
    j = i + 1;
    leds[i] = CRGB::Black;
    FastLED.show();
    delay(40);
  }
  leds[NUM_LEDS - 1] = CRGB::Black;
}

void rainbow()
{
  // FastLED's built-in rainbow generator
  fill_rainbow( leds, NUM_LEDS, gHue, 2);
}

void rainbowWithGlitter()
{
  // built-in FastLED rainbow, plus some random sparkly glitter
  rainbow();
  addGlitter(80);
}

void addGlitter( fract8 chanceOfGlitter)
{
  if ( random8() < chanceOfGlitter) {
    leds[ random16(NUM_LEDS) ] += CRGB::White;
  }
}

void blue_snow()
{
  fadeToBlackBy( leds, NUM_LEDS, 5);
    int sat = random(255);
    leds[ random(NUM_LEDS) ] = CHSV(160, sat, 255);
    FastLED.show();
    delay(25);
}

void confetti()
{
  // random colored speckles that blink in and fade smoothly
  fadeToBlackBy( leds, NUM_LEDS, 10);
  int pos = random16(NUM_LEDS);
  leds[pos] += CHSV( gHue + random8(64), 200, 255);
}

void sinelon()
{
  // a colored dot sweeping back and forth, with fading trails
  fadeToBlackBy( leds, NUM_LEDS, 20);
  int pos = beatsin16(13, 0, NUM_LEDS);
  leds[pos] += CHSV( gHue, 255, 192);
}

void multi_sinelon()
{
  fadeToBlackBy( leds, NUM_LEDS, 20);
  int posi = beatsin16(15, 0, NUM_LEDS);
  leds[posi] += CHSV( gHue, 255, 255);
  leds[posi + 10] += CHSV( gHue + 40, 255, 255);
  leds[posi + 20] += CHSV( gHue + 80, 255, 255);
  leds[posi + 30] += CHSV( gHue + 120, 255, 255);
  leds[posi + 40] += CHSV( gHue + 160, 255, 255);
  //FastLED.show();
  //delay(10);
}

void bpm()
{
  // colored stripes pulsing at a defined Beats-Per-Minute (BPM)
  uint8_t BeatsPerMinute = 62;
  CRGBPalette16 palette = PartyColors_p;
  uint8_t beat = beatsin8( BeatsPerMinute, 64, 255);
  for ( int i = 0; i < NUM_LEDS; i++) { //9948
    leds[i] = ColorFromPalette(palette, gHue + (i * 2), beat - gHue + (i * 10));
  }
}

void juggle() {
  // eight colored dots, weaving in and out of sync with each other
  fadeToBlackBy( leds, NUM_LEDS, 20);
  byte dothue = 0;
  for ( int i = 0; i < 8; i++) {
    leds[beatsin16(i + 7, 0, NUM_LEDS)] |= CHSV(dothue, 200, 255);
    dothue += 32;
  }
}

void half_cylon(fract8 chanceOfGlitter)
{
  static uint8_t hue = 0;
  // First slide the led in one direction
  for (int i = 0; i < NUM_LEDS; i++) {
    // Set the i'th led to red
    leds[i] = CHSV(hue++, 255, 255);
    // Show the leds
    FastLED.show();
    // now that we've shown the leds, reset the i'th led to black
    // leds[i] = CRGB::Black;
    fadeToBlackBy( leds, NUM_LEDS, 10);
    // Wait a little bit before we loop around and do it again
    delay(10);
  }
}

void cylon( fract8 chanceOfGlitter)
{
  static uint8_t hue = 0;
  // First slide the led in one direction
  for (int i = 0; i < NUM_LEDS; i++) {
    // Set the i'th led to red
    leds[i] = CHSV(hue++, 255, 255);
    // Show the leds
    FastLED.show();
    // now that we've shown the leds, reset the i'th led to black
    // leds[i] = CRGB::Black;
    fadeToBlackBy( leds, NUM_LEDS, 10);
    // Wait a little bit before we loop around and do it again
    delay(10);
  }


  // Now go in the other direction.
  for (int i = (NUM_LEDS) - 1; i >= 0; i--) {
    // Set the i'th led to red
    leds[i] = CHSV(hue++, 255, 255);
    // Show the leds
    FastLED.show();
    // now that we've shown the leds, reset the i'th led to black
    // leds[i] = CRGB::Black;
    fadeToBlackBy( leds, NUM_LEDS, 10);
    // Wait a little bit before we loop around and do it again
    delay(10);
  }
}


