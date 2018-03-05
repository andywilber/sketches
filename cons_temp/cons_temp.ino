#include <PubSubClient.h>
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ArduinoOTA.h>
#include <DallasTemperature.h>
#include "DHT.h"

#define out_temperature_topic "cons/out_temperature"
#define in_temperature_topic "cons/in_temperature"
#define in_humidity_topic "cons/in_humidity"
#define ONE_WIRE_BUS 2
#define DHTPIN 4
#define DHTTYPE DHT22

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
WiFiClient espClient;
PubSubClient client(espClient);
DHT dht(DHTPIN, DHTTYPE);

const char* ssid = "xxx";
const char* password = "xxx";
const char* mqtt_server = "192.168.1.113";
long lastMsg = 0;

void setup() {
  Serial.begin(115200);
  sensors.begin();
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  dht.begin();
  //client.setCallback(callback);
}

void setup_wifi() {

  delay(10);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
}

bool checkBound(float newValue, float prevValue, float maxDiff) {
  return !isnan(newValue) &&
         (newValue < prevValue - maxDiff || newValue > prevValue + maxDiff);
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    // Attempt to connect
    if (client.connect("ConsClient")) {
      //Serial.println("connected");
      client.subscribe("Cons_in");
    } else {
      //Serial.print("failed, rc=");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

float t_diff = 0.1;
float h_diff = 0.5;
float temp = 0.0;
float t = 0;
float h = 0;

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
  long now = millis();
  if (now - lastMsg > 30000) {
    lastMsg = now;
    sensors.requestTemperatures();
    float newTemp = sensors.getTempCByIndex(0);
    float newH = dht.readHumidity();
    float newT = dht.readTemperature();
    if (checkBound(newTemp, temp, t_diff)) {
      temp = newTemp;
      client.publish(out_temperature_topic, String(temp).c_str(), true);
      //Serial.println(temp);
    }
    if (checkBound(newT, t, t_diff)) {
      t = newT;
      client.publish(in_temperature_topic, String(t).c_str(), true);
      //Serial.println(temp);
    }
    if (checkBound(newH, h, t_diff)) {
      h = newH;
      client.publish(in_humidity_topic, String(h).c_str(), true);
      //Serial.println(temp);
    }
  }
}
