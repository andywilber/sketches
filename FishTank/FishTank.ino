#include "FastLED.h"
#include <PubSubClient.h>
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ArduinoOTA.h>
#include <U8g2lib.h>
#include <FlowMeter.h>
#include <DallasTemperature.h>

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif



#define flow_topic "aquarium/flow"
#define temperature_topic "aquarium/temperature"


U8G2_SSD1306_128X64_NONAME_F_4W_SW_SPI u8g2(U8G2_R0, /* clock=*/ 13, /* data=*/ 14, /* cs=*/ 4, /* dc=*/ 0, /* reset=*/ 12);
FlowMeter Meter = FlowMeter(2);
#define ONE_WIRE_BUS 2

OneWire oneWire(ONE_WIRE_BUS);
 
DallasTemperature sensors(&oneWire);

char* temp_oled = "";
char* flow_oled = "";
char* IP_oled = "";

#define MQTT_SERVER "192.168.1.113"  //you MQTT IP Address
const char* ssid = "xxx xxx";
const char* password = "xxx";
const char* mqtt_server = "192.168.1.113";
// Flow
const unsigned long period = 1000;
// define an 'interrupt service handler' (ISR) for every interrupt pin you use
void MeterISR() {
  // let our flow meter count the pulses
  Meter.count();
}

WiFiClient espClient;
PubSubClient client(espClient);


#define DATA_PIN    8
#define LED_TYPE    WS2811
#define COLOR_ORDER RGB
#define NUM_LEDS    50
CRGB leds[NUM_LEDS];
int sHue=0;

#define BRIGHTNESS         255
#define FRAMES_PER_SECOND  120

FASTLED_USING_NAMESPACE

long lastMsg = 0;
char msg[50];
//int value = 0;
int displayOn = 1;


void setup() {
  //delay(3000); // 3 second delay for recovery
  sensors.begin(); 
  Serial.begin(115200);
  u8g2.begin();
  // interupt for flowmeter GPIO5 pin D1
  attachInterrupt(5, MeterISR, RISING);
  FastLED.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(BRIGHTNESS);
  fill_solid (leds, NUM_LEDS, CHSV(0,0,0));
  FastLED.show();
  
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
  Meter.reset();
}

void setup_wifi() {

  delay(10);

  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_inr16_mf);
  u8g2.drawStr(0,20,"Wifi");
  u8g2.drawStr(0,45,"Connecting");
  u8g2.sendBuffer();
  
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    //Serial.print(".");
  }

    u8g2.setFont(u8g2_font_inr16_mf);
    u8g2.drawStr(0,45,"Connected ");
    u8g2.sendBuffer();
    delay(1000);
}

bool checkBound(float newValue, float prevValue, float maxDiff) {
  return !isnan(newValue) &&
         (newValue < prevValue - maxDiff || newValue > prevValue + maxDiff);
}

void callback(char* topic, byte* payload, unsigned int length) {
  //Serial.print("Message arrived [");
  //Serial.print(topic);
  //Serial.print("] ");
  for (int i = 0; i < length; i++) {
  //Serial.print((char)payload[i]);
  }
  //Serial.println();

  // Switch on the LED if an 1 was received as first character
  if ((char)payload[0] == '0') {
    // Off
    fill_solid (leds, NUM_LEDS, CRGB(0,0,0));
    FastLED.show();
    u8g2.clearBuffer();
    Serial.println("Off");
    u8g2.drawStr(0,20,"Lights Off");
    u8g2.sendBuffer();
  } else if ((char)payload[0] == '1')  {
    // Day
    fill_solid (leds, NUM_LEDS, CRGB(255,150,255));
    FastLED.show(); 
    u8g2.clearBuffer();
    u8g2.drawStr(0,20,"Natural");
    u8g2.sendBuffer();
  } else if ((char)payload[0] == '2')  {
    //Rainbow
    fill_rainbow( leds, NUM_LEDS, sHue, 3);
    FastLED.show();
    u8g2.clearBuffer();
    u8g2.drawStr(0,20,"Rainbow");
    u8g2.sendBuffer();
    } else if ((char)payload[0] == '4')  {
    //Night
    fill_solid (leds, NUM_LEDS, CRGB(100,100,255));
    FastLED.show();
    u8g2.clearBuffer();
    u8g2.drawStr(0,20,"Night");
    u8g2.sendBuffer();
  } else if ((char)payload[0] == '3')  {
    // Dim
    fadeToBlackBy( leds, NUM_LEDS, 50);
    FastLED.show();
  } else if ((char)payload[0] == '8')  {
    u8g2.clearBuffer();
    u8g2.drawStr(0,20,"Hello");
    u8g2.sendBuffer();
    displayOn = 1;
  } else if ((char)payload[0] == '9')  {
    u8g2.clearBuffer();
    u8g2.drawStr(0,20,"Good night");
    u8g2.sendBuffer();
    displayOn = 0;
  } 
    
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    u8g2.clearBuffer();
    u8g2.drawStr(0,20,"MQTT");
    u8g2.drawStr(0,45,"Connecting");
    u8g2.sendBuffer();
    // Attempt to connect
    if (client.connect("AquariumClient")) {
      u8g2.drawStr(0,45,"Connected  ");
      u8g2.sendBuffer();
      // Once connected, publish an announcement...
      //client.publish("aquarium_out", "hello world");
      // ... and resubscribe
      client.subscribe("aquarium_in");
      //client.subscribe("time/hour");
    } else {
      //Serial.print("failed, rc=");
      u8g2.drawStr(0,45,"Failed    ");
      u8g2.sendBuffer();
      //Serial.print(client.state());
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

float temp = 0.0;
float flow = 0.0;
float t_diff = 0.1;
float f_diff = 0.1;
int y=0;

void loop()
{
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
   long now = millis();
  if (now - lastMsg > 30000) {
    lastMsg = now;
    //++value;
    sHue+=10;
    // AJW snprintf (msg, 75, "hello world #%ld", value);
    sensors.requestTemperatures();
    Meter.tick(period);
    float newFlow = Meter.getCurrentFlowrate()/30; // divide by lastMsg delay above (in secs)
    float newTemp = sensors.getTempCByIndex(0);

    if (checkBound(newTemp, temp, t_diff)) {
      temp = newTemp;
      client.publish(temperature_topic, String(temp).c_str(), true);
      //dtostrf(temp, 2, 1, temp_oled);
    }

    if (checkBound(newFlow, flow, f_diff)) {
      flow = newFlow;
      client.publish(flow_topic, String(flow).c_str(), true);
      //dtostrf(flow, 2, 1, flow_oled);
    }

    if (displayOn == 1) {   
      u8g2.clearBuffer();
      u8g2.setFont(u8g2_font_logisoso18_tf);
      u8g2.drawStr(0,y+20,"Temp  Flow");
      u8g2.drawStr(0,y+50,String(temp).c_str());
      u8g2.drawStr(80,y+50,String(flow).c_str());
      u8g2.sendBuffer();
      y++;
      if (y>10) { y=0; }
    } else if (displayOn == 0) {
      u8g2.clearBuffer();
      u8g2.sendBuffer();
    }
  }
}

