#include <FastLED.h>
#define DATA_PIN    3

#define LED_TYPE    WS2811
#define COLOR_ORDER RGB
#define NUM_LEDS    50
CRGB leds[NUM_LEDS];
#define BRIGHTNESS          50
#define FRAMES_PER_SECOND  120
#define COUNTER 0
const int buttonPin = 2;
int buttonState = 0;
int lastButtonState = 0;  

void setup() {
 delay(3000); // 3 second delay for recovery
 pinMode(buttonPin, INPUT);
  
  // tell FastLED about the LED strip configuration
  FastLED.addLeds<LED_TYPE,DATA_PIN,COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);

  // set master brightness control
  FastLED.setBrightness(BRIGHTNESS);

}

void loop() {

// read the state of the pushbutton value:
  buttonState = digitalRead(buttonPin);

  // check if the pushbutton is pressed.
  // if it is, the buttonState is HIGH:
  if (buttonState == HIGH) {
    // turn LED on:
    leds[1] = CRGB::Red;
    FastLED.show();
  } else {
    // turn LED off:
    leds[0] = CRGB::Green;
  FastLED.show();
  }

}
