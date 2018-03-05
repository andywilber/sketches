#include "FastLED.h"

FASTLED_USING_NAMESPACE

#define DATA_PIN    6
#define LED_TYPE    WS2811
#define COLOR_ORDER RGB
#define NUM_LEDS    50
CRGB leds[NUM_LEDS];

#define BRIGHTNESS          50
#define FRAMES_PER_SECOND  120



// the setup routine runs once when you press reset:
void setup() {
  delay(3000); // 3 second delay for recovery
    // tell FastLED about the LED strip configuration
  FastLED.addLeds<LED_TYPE,DATA_PIN,COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);

  // set master brightness control
  FastLED.setBrightness(BRIGHTNESS);
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
}

// the loop routine runs over and over again forever:
void loop() {
  fadeToBlackBy( leds, NUM_LEDS, 1000);
  // read the input on analog pin 0:
  int sens1 = analogRead(A0);
  int sens2 = analogRead(A1);
  int colour = sens1 * (256.0 / 1023.0);
  int pos = sens2 * (NUM_LEDS / 1023.0);
// print data
  Serial.print("Colour pot: ");
  Serial.println(colour);
  Serial.print("Pos pot: ");
  Serial.println(pos);

//fill_solid (struct CRGB *leds, int numToFill, const struct CRGB &color)
//fill_solid(leds, 5, rgbval)
fill_solid(leds, pos, CHSV(colour, 255, 255));
  FastLED.show();
  delay(100);
}
