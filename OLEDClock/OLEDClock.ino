

#include <Arduino.h>
#include <U8g2lib.h>
#include <Wire.h>
#include "RTClib.h"
char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif

RTC_DS3231 rtc;
U8G2_SSD1306_128X64_NONAME_1_4W_SW_SPI u8g2(U8G2_R0, /* clock=*/ 13, /* data=*/ 11, /* cs=*/ 10, /* dc=*/ 9, /* reset=*/ 8);



void setup(void) {
  u8g2.begin();
  rtc.begin();
}

void loop(void) {
  //u8g2.setFont(u8g2_font_amstrad_cpc_extended_8f);
  u8g2.setFont(u8g2_font_ncenB14_tr);

  u8g2.firstPage();
  do {
    DateTime now = rtc.now();
    u8g2.setCursor(21, 16);
    u8g2.print(daysOfTheWeek[now.dayOfTheWeek()]);
    u8g2.setCursor(18, 40);
    u8g2.print(now.day(), DEC);
    u8g2.print('/');
    if (now.month() < 10) {
      u8g2.print("0");
    }
    //u8g2.print(printf("%02d",now.month()), DEC);
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
  } while ( u8g2.nextPage() );
  delay(1000);
}

