#include <BME280I2C.h>
#include <Wire.h>

BME280I2C bme; 

void setup()
{
  Serial.begin(115200);

  while(!Serial) {} // Wait

  Wire.begin();
  bme.begin();

}

float temp(NAN), hum(NAN), pres(NAN);
BME280::TempUnit tempUnit(BME280::TempUnit_Celsius);
BME280::PresUnit presUnit(BME280::PresUnit_hPa);

void loop()
{
  bme.read(pres, temp, hum, tempUnit, presUnit);
  Serial.println(pres);
  delay(2000);
}

