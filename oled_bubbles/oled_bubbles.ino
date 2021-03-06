
#include <Arduino.h>
#include <U8g2lib.h>

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif

U8G2_SSD1306_128X64_NONAME_1_SW_I2C u8g2(U8G2_R0, /* clock=*/ 2, /* data=*/ 1, /* reset=*/ U8X8_PIN_NONE);


void setup() {
  u8g2.begin();
}

int y3 = random(54,60);
int x3 = random(0, 128);
int size1=random(5,20);
int y2 = random(54,60);
int x2 = random(0, 128);
int size2=random(5,20);
//int x=50;
//void U8G2:drawCircle(u8g2_uint_t x0, u8g2_uint_t y0, u8g2_uint_t rad, uint8_t opt = U8G_DRAW_ALL)

void loop() {
  u8g2.firstPage();
  do {
    u8g2.clearBuffer();
    u8g2.drawCircle(x3, y3, size1);
    u8g2.drawCircle(x2, y2, size2);
    y3--;
    y3--;
    if (y1 == 0) {
      y3 = random(54,60);
      x3 = random(0, 128);
      size1=random(5,20);
    }
    if (y2 == 0) {
      y2 = random(54,60);
      x2 = random(0, 128);
      size2=random(5,20);
    }
  } while ( u8g2.nextPage() );

    //delay(10);
}
