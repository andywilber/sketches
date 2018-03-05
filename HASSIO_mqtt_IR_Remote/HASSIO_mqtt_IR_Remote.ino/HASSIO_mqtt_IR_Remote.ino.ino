/*

Receives mqtt and send IR code to varilight.
Also reads DHT 22 and BME280 (pressure only) and sends temo/humidity back to HA via MQTT

*/

#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <Arduino.h>
#include <IRremoteESP8266.h>
#include <IRsend.h>
//#include <DHT.h>
#include <BME280I2C.h>
#include <Wire.h>

IRsend irsend(4);
BME280I2C bme; 

#define humidity_topic "sensor/humidity"
#define temperature_topic "sensor/temperature"
#define pressure_topic "sensor/pressure"

#define DHTTYPE DHT22
#define DHTPIN  5 //Pin D1

uint16_t on_rawData[19] = {896, 882,  1782, 1794,  898, 882,  892, 882,  1782, 1766,  1784, 882,  894, 1768,  896, 910,  1782, 878,  894};  // RC5 74C};
uint16_t down_rawData[19] = {920, 880,  1784, 1764,  896, 880,  896, 880,  1812, 1764,  1786, 1764,  1786, 878,  896, 878,  898, 1764,  924};  // RC5 751
uint16_t up_rawData[21] = {898, 880,  896, 882,  894, 880,  894, 882,  892, 882,  1812, 1766,  1784, 1768,  1786, 880,  892, 882,  894, 880,  924};  // RC5 F50
uint16_t off_rawData[23] = {922, 880,  894, 882,  894, 880,  896, 882,  894, 878,  1812, 1770,  1782, 878,  894, 880,  894, 882,  894, 878,  896, 882,  894};  // RC5 F40
uint16_t min_rawData[21] = {916, 862,  914, 906,  896, 880,  896, 860,  914, 878,  1786, 1766,  1786, 878,  896, 1794,  896, 878,  1784, 1762,  900};  // RC5 F4D
uint16_t max_rawData[21] = {918, 860,  1832, 1746,  916, 860,  916, 858,  1804, 1748,  1804, 858,  918, 1774,  914, 860,  916, 860,  916, 860,  914};  // RC5 74F
uint16_t sc1_rawData[19] = {900,800, 1850,1700, 900,850, 950,800, 1800,1750, 950,800, 950,800, 1850,1700, 1800,1700, 950};
uint16_t sc2_rawData[21] = {950,850, 1800,1700, 950,850, 900,850, 1800,1700, 900,850, 950,800, 950,850, 1800,850, 900,850, 900};
uint16_t sc3_rawData[21] = {950,900, 900,850, 900,850, 900,850, 900,850, 1800,1750, 900,850, 900,900, 900,850, 1800,1700, 1800};
uint16_t sc4_rawData[23] = {950,850, 900,850, 900,850, 900,850, 900,850, 1800,1700, 950,850, 950,800, 950,800, 950,850, 1800,850, 900};

// Update these with values suitable for your network.

const char* ssid = "xxx xxx";
const char* password = "xxx";
const char* mqtt_server = "192.168.1.113";

WiFiClient espClient;
PubSubClient client(espClient);
//DHT dht(DHTPIN, DHTTYPE, 11);
long lastMsg = 0;
char msg[50];
int value = 0;

void setup() {
  pinMode(BUILTIN_LED, OUTPUT);     // Initialize the BUILTIN_LED pin as an output
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
  irsend.begin();
  //dht.begin();
  Wire.begin(D3, D4);
  bme.begin();
}

void setup_wifi() {

  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

bool checkBound(float newValue, float prevValue, float maxDiff) {
  return !isnan(newValue) &&
         (newValue < prevValue - maxDiff || newValue > prevValue + maxDiff);
}


float temp = 0.0;
float hum = 0.0;
float pres = 0.0;
float t_diff = 0.1;
float h_diff = 1.0;
float p_diff = 0.5;
float tempo(NAN), humo(NAN), preso(NAN);
BME280::TempUnit tempUnit(BME280::TempUnit_Celsius);
BME280::PresUnit presUnit(BME280::PresUnit_hPa);

void callback(char* topic, byte* payload, unsigned int length) {
//  Serial.print("Message arrived [");
//  Serial.print(topic);
//  Serial.print("] ");
  for (int i = 0; i < length; i++) {
 //   Serial.print((char)payload[i]);
  }
  Serial.println();

  // Switch on the LED if an 1 was received as first character
  if ((char)payload[0] == '0') {
    irsend.sendRaw(off_rawData, 23, 38); 
  } else if ((char)payload[0] == '1')  {
    irsend.sendRaw(on_rawData, 19, 38);
  } else if ((char)payload[0] == '2')  {
    irsend.sendRaw(up_rawData, 21, 38);
  } else if ((char)payload[0] == '3')  {
    irsend.sendRaw(down_rawData, 19, 38);
  } else if ((char)payload[0] == '4')  {
    irsend.sendRaw(min_rawData, 21, 38);
  } else if ((char)payload[0] == '5')  {
    irsend.sendRaw(max_rawData, 21, 38);
  } else if ((char)payload[0] == '6')  {
    irsend.sendRaw(sc1_rawData, 19, 38);
  } else if ((char)payload[0] == '7')  {
    irsend.sendRaw(sc2_rawData, 21, 38);
  } else if ((char)payload[0] == '8')  {
    irsend.sendRaw(sc3_rawData, 21, 38);
  } else if ((char)payload[0] == '9')  {
    irsend.sendRaw(sc4_rawData, 23, 38);
  }
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    //Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("THP_IR")) {
     // Serial.println("connected");
      // Once connected, publish an announcement...
      //client.publish("outTopic", "hello world");
      // ... and resubscribe
      client.subscribe("inTopic");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}
void loop() {

  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  long now = millis();
  if (now - lastMsg > 30000) {
    lastMsg = now;
    ++value;
    bme.read(preso, tempo, humo, tempUnit, presUnit);
    //float newTemp = dht.readTemperature();
    //float newHum = dht.readHumidity();
    float newTemp = tempo;
    float newHum = humo;
    float newPres = preso;

    if (checkBound(newPres, pres, p_diff)) {
      pres=newPres;
      client.publish(pressure_topic, String(pres).c_str(), true);
    }
    
    if (checkBound(newTemp, temp, t_diff)) {
      temp = newTemp;
      client.publish(temperature_topic, String(temp).c_str(), true);
    }

    if (checkBound(newHum, hum, h_diff)) {
      hum = newHum;
      client.publish(humidity_topic, String(hum).c_str(), true);
    }
  }
}
