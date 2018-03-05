/* IRremoteESP8266: IRsendDemo - demonstrates sending IR codes with IRsend.
 *
 * Version 1.0 April, 2017
 * Based on Ken Shirriff's IrsendDemo Version 0.1 July, 2009,
 * Copyright 2009 Ken Shirriff, http://arcfn.com
 *
 * An IR LED circuit *MUST* be connected to ESP8266 pin 4 (D2).
 *
 * TL;DR: The IR LED needs to be driven by a transistor for a good result.
 *
 * Suggested circuit:
 *     https://github.com/markszabo/IRremoteESP8266/wiki#ir-sending
 *
 * Common mistakes & tips:
 *   * Don't just connect the IR LED directly to the pin, it won't
 *     have enough current to drive the IR LED effectively.
 *   * Make sure you have the IR LED polarity correct.
 *     See: https://learn.sparkfun.com/tutorials/polarity/diode-and-led-polarity
 *   * Typical digital camera/phones can be used to see if the IR LED is flashed.
 *     Replace the IR LED with a normal LED if you don't have a digital camera
 *     when debugging.
 *   * Avoid using the following pins unless you really know what you are doing:
 *     * Pin 0/D3: Can interfere with the boot/program mode & support circuits.
 *     * Pin 1/TX/TXD0: Any serial transmissions from the ESP8266 will interfere.
 *     * Pin 3/RX/RXD0: Any serial transmissions to the ESP8266 will interfere.
 *   * ESP-01 modules are tricky. We suggest you use a module with more GPIOs
 *     for your first time. e.g. ESP-12 etc.
 */

#ifndef UNIT_TEST
#include <Arduino.h>
#endif
#include <IRremoteESP8266.h>
#include <IRsend.h>

IRsend irsend(4);  // An IR LED is controlled by GPIO pin 4 (D2)

// Example of data captured by IRrecvDumpV2.ino
uint16_t rawData[67] = {9000, 4500, 650, 550, 650, 1650, 600, 550, 650, 550,
                        600, 1650, 650, 550, 600, 1650, 650, 1650, 650, 1650,
                        600, 550, 650, 1650, 650, 1650, 650, 550, 600, 1650,
                        650, 1650, 650, 550, 650, 550, 650, 1650, 650, 550,
                        650, 550, 650, 550, 600, 550, 650, 550, 650, 550,
                        650, 1650, 600, 550, 650, 1650, 650, 1650, 650, 1650,
                        650, 1650, 650, 1650, 650, 1650, 600};
uint16_t on_rawData[19] = {896, 882,  1782, 1794,  898, 882,  892, 882,  1782, 1766,  1784, 882,  894, 1768,  896, 910,  1782, 878,  894};  // RC5 74C};
uint16_t down_rawData[19] = {920, 880,  1784, 1764,  896, 880,  896, 880,  1812, 1764,  1786, 1764,  1786, 878,  896, 878,  898, 1764,  924};  // RC5 751
uint16_t up_rawData[21] = {898, 880,  896, 882,  894, 880,  894, 882,  892, 882,  1812, 1766,  1784, 1768,  1786, 880,  892, 882,  894, 880,  924};  // RC5 F50
uint16_t off_rawData[23] = {898, 880,  894, 880,  924, 880,  896, 880,  894, 880,  1784, 1766,  1786, 880,  896, 880,  892, 910,  894, 882,  894, 880,  896};  // RC5 F40
uint16_t min_rawData[21] = {916, 862,  914, 906,  896, 880,  896, 860,  914, 878,  1786, 1766,  1786, 878,  896, 1794,  896, 878,  1784, 1762,  900};  // RC5 F4D
uint16_t max_rawData[21] = {918, 860,  1832, 1746,  916, 860,  916, 858,  1804, 1748,  1804, 858,  918, 1774,  914, 860,  916, 860,  916, 860,  914};  // RC5 74F


void setup() {
  irsend.begin();
  Serial.begin(115200, SERIAL_8N1, SERIAL_TX_ONLY);
}

void loop() {
#if SEND_RAW
  Serial.println("on");
  irsend.sendRaw(on_rawData, 19, 38);
//#endif  // SEND_NEC
  delay(2000);
//#if SEND_SONY
  Serial.println("up");
  irsend.sendRaw(up_rawData, 21, 38);
//#endif  // SEND_SONY
  delay(2000);
//#if SEND_RAW
  Serial.println("down");
  irsend.sendRaw(down_rawData, 19, 38);  // Send a raw data capture at 38kHz.
  delay(2000);
  Serial.println("max");
  irsend.sendRaw(max_rawData, 21, 38);
  delay(5000);
  Serial.println("min");
  irsend.sendRaw(min_rawData, 21, 38);
  delay(5000);
  Serial.println("off");
  irsend.sendRaw(off_rawData, 23, 38);
  delay(2000);
#endif  // SEND_RAW
  //delay(2000);
}
