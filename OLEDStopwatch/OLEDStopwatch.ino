#include <Arduino.h>
#include <U8g2lib.h>
#include <Wire.h>


#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif

U8G2_SSD1306_128X64_NONAME_1_4W_SW_SPI u8g2(U8G2_R0, /* clock=*/ 13, /* data=*/ 11, /* cs=*/ 10, /* dc=*/ 9, /* reset=*/ 8);



void setup(void) {
  u8g2.begin();
}



void loop(void) {
  u8g2.setFont(u8g2_font_ncenB14_tr);
  u8g2.firstPage();
  do {
    u8g2.drawRFrame(0, 25, 125, 30, 10);
    u8g2.setCursor(15, 15);
    u8g2.print("Stopwatch");
    u8g2.setCursor(10, 46);
    long time = millis();
    int HH = time / 3600000;
    if (HH < 10) {
      u8g2.print("0");
    }
    u8g2.print(HH);
    u8g2.print(":");
    int MM = time / 60000 % 60;
    if (MM < 10) {
      u8g2.print("0");
    }
    u8g2.print(MM);
    u8g2.print(":");
    int SS = time / 1000 % 60;
    if (SS < 10) {
      u8g2.print("0");
    }
    u8g2.print(SS);
    u8g2.print(".");
    int HU = time / 10 % 100;
    if (HU < 10) {
      u8g2.print("0");
    }
    u8g2.print(HU);
    u8g2.drawLine(2, 60, SS * 2, 60);
    u8g2.drawLine(2, 63, HU * 1.5, 63);
  } while ( u8g2.nextPage() );
  delay(10);
}

