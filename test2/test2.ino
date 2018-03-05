#include <Adafruit_NeoPixel.h>

#include <FastLED.h>

#define DATA_PIN    3
#define LED_TYPE    WS2811
#define COLOR_ORDER RGB
#define NUM_LEDS    10
CRGB leds[NUM_LEDS];
#define BRIGHTNESS          50
#define FRAMES_PER_SECOND  120
#define COUNTER 0

Adafruit_NeoPixel strip = Adafruit_NeoPixel(50, DATA_PIN, NEO_GRB + NEO_KHZ800);

// this constant won't change:
const int  buttonPin = 2;    // the pin that the pushbutton is attached to
const int ledPin = 13;       // the pin that the LED is attached to

// Variables will change:
int buttonPushCounter = 0;   // counter for the number of button presses
int buttonState = 0;         // current state of the button
int lastButtonState = 0;     // previous state of the button

void setup() {
  // initialize the button pin as a input:
  pinMode(buttonPin, INPUT);
  FastLED.addLeds<LED_TYPE,DATA_PIN,COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(BRIGHTNESS);
}


void loop() {
  // read the pushbutton input pin:
  buttonState = digitalRead(buttonPin);

  // compare the buttonState to its previous state
  if (buttonState != lastButtonState) {
    // if the state has changed, increment the counter
    if (buttonState == HIGH)
         buttonPushCounter++;
      leds[buttonPushCounter] = CRGB::Red;
    FastLED.show();
   
    
    }
    // Delay a little bit to avoid bouncing
    delay(50);
  
  // save the current state as the last state,
  //for next time through the loop
  lastButtonState = buttonState;
  if (buttonPushCounter > NUM_LEDS) {
      strip.begin();
  strip.show(); // Initialize all pixels to 'off'
      buttonPushCounter = 0;
  }
}









