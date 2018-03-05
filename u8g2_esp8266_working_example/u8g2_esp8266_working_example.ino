

#include <Arduino.h>
#include <U8g2lib.h>

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif


U8G2_SSD1306_128X64_NONAME_F_4W_SW_SPI u8g2(U8G2_R0, /* clock=*/ 13, /* data=*/ 14, /* cs=*/ 4, /* dc=*/ 0, /* reset=*/ 12);



void setup(void) {
  u8g2.begin();
}

void loop(void) {
  u8g2.clearBuffer();					// clear the internal memory
  //u8g2.setFont(u8g2_font_ncenB08_tr);	// choose a suitable font
  u8g2.setFont(u8g2_font_inr16_mf);
  u8g2.drawStr(0,20,"Line 1");	// write something to the internal memory
  u8g2.drawStr(0,42,"Line 2");
  u8g2.drawStr(80,25,"Over here");
  u8g2.sendBuffer();					// transfer internal memory to the display
  delay(1000);  
}

