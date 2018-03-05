
#include <Arduino.h>
#include <U8x8lib.h>
#include "RTClib.h"

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif


RTC_DS3231 rtc;
U8X8_SSD1306_128X64_NONAME_4W_SW_SPI u8x8(/* clock=*/ 13, /* data=*/ 11, /* cs=*/ 10, /* dc=*/ 9, /* reset=*/ 8);
char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};



void setup(void)
{
  u8x8.begin();
  rtc.begin();
}

void pre(void)
{
  u8x8.setFont(u8x8_font_amstrad_cpc_extended_f);    
  u8x8.clear();

  u8x8.inverse();
  u8x8.print(" Andy's Clock ");
  u8x8.setFont(u8x8_font_chroma48medium8_r);  
  u8x8.noInverse();
  u8x8.setCursor(0,1);
}

void draw_bar(uint8_t c, uint8_t is_inverse)
{	
  uint8_t r;
  u8x8.setInverseFont(is_inverse);
  for( r = 0; r < u8x8.getRows(); r++ )
  {
    u8x8.setCursor(c, r);
    u8x8.print(" ");
  }
}

void draw_ascii_row(uint8_t r, int start)
{
  int a;
  uint8_t c;
  for( c = 0; c < u8x8.getCols(); c++ )
  {
    u8x8.setCursor(c,r);
    a = start + c;
    if ( a <= 255 )
      u8x8.write(a);
  }
}

void loop(void)
{
//////////u8x8.draw2x2String(0, 5, "Big");
  pre();
  DateTime now = rtc.now();
    u8x8.draw2x2String(0, 5,daysOfTheWeek[now.dayOfTheWeek()]);
    delay(2000);
    draw_bar(0, 1);
  for(int c = 1; c < u8x8.getCols(); c++ )
  {
    draw_bar(c, 1);
    draw_bar(c-1, 0);
    delay(50);
  }
  draw_bar(u8x8.getCols()-1, 0);
  int DAY=(now.day(), DEC);
  u8x8.draw2x2String(0, 5, "DAY");
//    u8x8.print(daysOfTheWeek[now.dayOfTheWeek()]);
//    u8x8.setCursor(18, 40);
//    u8x8.print(now.day(), DEC);
//    u8x8.print('/');
//    if (now.month() < 10) {
//      u8x8.print("0");
//    }
//    //u8x8.print(printf("%02d",now.month()), DEC);
//    u8x8.print(now.month(), DEC);
//    u8x8.print('/');
//    u8x8.print(now.year(), DEC);
//    u8x8.setCursor(30, 63);
//    u8x8.print(now.hour(), DEC);
//    u8x8.print(':');
//    if (now.minute() < 10) {
//      u8x8.print("0");
//    }
//    u8x8.print(now.minute(), DEC);
//    u8x8.print(':');
//    if (now.second() < 10) {
//      u8x8.print("0");
//    }
//    u8x8.print(now.second(), DEC);
  delay(1000);
//////////
  
  delay(2000);
   
  pre();

  
  
  pre();
  u8x8.setFont(u8x8_font_amstrad_cpc_extended_f); 
  for(int d = 0; d < 8; d ++ )
  {
    for(int r = 1; r < u8x8.getRows(); r++ )
    {
      draw_ascii_row(r, (r-1+d)*u8x8.getCols() + 32);
    }
    delay(800);
  }

  draw_bar(u8x8.getCols()-1, 1);
  for(int c = u8x8.getCols()-1; c > 0; c--)
  {
    draw_bar(c-1, 1);
    draw_bar(c, 0);
    delay(50);
  }
  draw_bar(0, 0);

  pre();
  u8x8.drawString(0, 2, "Small");
  u8x8.draw2x2String(0, 5, "Big");
  delay(3000);

  pre();
  u8x8.fillDisplay();
  for(int r = 0; r < u8x8.getRows(); r++ )
  {
    u8x8.clearLine(r);
    delay(100);
  }
  delay(1000);

  pre();
  u8x8.print("print \\n\n");
  delay(500);
  u8x8.println("println");
  delay(500);
  u8x8.println("done");
  delay(1500);

}

