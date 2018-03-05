

#include <Arduino.h>
#include <U8g2lib.h>
#include "RTClib.h"
#include <Wire.h>
char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif

RTC_DS3231 rtc;
U8G2_SSD1306_128X64_NONAME_1_4W_SW_SPI u8g2(U8G2_R0, /* clock=*/ 13, /* data=*/ 11, /* cs=*/ 10, /* dc=*/ 9, /* reset=*/ 8);


void u8g2_prepare(void) {
  u8g2.setFont(u8g2_font_6x10_tf);
  u8g2.setFontRefHeightExtendedText();
  u8g2.setDrawColor(1);
  u8g2.setFontPosTop();
  u8g2.setFontDirection(0);
}

void u8g2_date() {
  u8g2.setFont(u8g2_font_ncenB14_tr);
  DateTime now = rtc.now();
  u8g2.setCursor(21, 16);
  u8g2.print(daysOfTheWeek[now.dayOfTheWeek()]);
  u8g2.setCursor(18, 40);
  if (now.day() < 10) {
    u8g2.print("0");
  }
  u8g2.print(now.day(), DEC);
  u8g2.print('/');
  if (now.month() < 10) {
    u8g2.print("0");
  }
  u8g2.print(now.month(), DEC);
  u8g2.print('/');
  u8g2.print(now.year(), DEC);
  u8g2.setCursor(30, 63);
  u8g2.print(now.hour(), DEC);
  u8g2.print(':');
  if (now.minute() < 10) {
    u8g2.print("0");
  }
  u8g2.print(now.minute(), DEC);
  u8g2.print(':');
  if (now.second() < 10) {
    u8g2.print("0");
  }
  u8g2.print(now.second(), DEC);
  delay(100);
}

void u8g2_time() {
  
  u8g2.setFont(u8g2_font_ncenB18_tr);
  DateTime now = rtc.now();
  u8g2.setCursor(1, 20);
  u8g2.print(now.hour(), DEC);
  u8g2.print(':');
  if (now.minute() < 10) {
    u8g2.print("0");
  }
  u8g2.print(now.minute(), DEC);
  u8g2.print(':');
  if (now.second() < 10) {
    u8g2.print("0");
  }
  u8g2.print(now.second(), DEC);
  delay(100);
}

void u8g2_day() {
  u8g2.setFont(u8g2_font_ncenB14_tr);
  u8g2.setCursor(1,1);
  u8g2.print("Running for:");
  u8g2.setCursor(1, 20);
  long time = millis();
  u8g2.print(time/1000);
  u8g2.setCursor(1,40);
  u8g2.print("seconds");
  delay(100);
}


uint8_t draw_state = 0;

void draw(void) {
  u8g2_prepare();
  switch (draw_state >> 3) {
    case 0: u8g2_date(); break;
    case 1: u8g2_time(); break;
    case 2: u8g2_day(); break;
  }
}


void setup(void) {
  u8g2.begin();
  rtc.begin();
}

void loop(void) {
  // picture loop
  u8g2.firstPage();
  do {
    draw();
  } while ( u8g2.nextPage() );

  // increase the state
  draw_state++;
  if ( draw_state >= 3 * 8 )
    draw_state = 0;

  // delay between each page
  delay(100);

}
