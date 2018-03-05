
#include <NTPtimeESP.h>
#include "LedControl.h"
#define DEBUG_ON

LedControl lc=LedControl(12,16,14,1);
unsigned long delaytime=250;

NTPtime NTPch("ch.pool.ntp.org");   // Choose server pool as required
char *ssid      = "xxx xxx";               // Set you WiFi SSID
char *password  = "xxx";               // Set you WiFi password

/*
 * The structure contains following fields:
 * struct strDateTime
{
  byte hour;
  byte minute;
  byte second;
  int year;
  byte month;
  byte day;
  byte dayofWeek;
  boolean valid;
};
 */
strDateTime dateTime;

void setup() {
  Serial.begin(115200);
  Serial.println();
  Serial.println("Booted");
  Serial.println("Connecting to Wi-Fi");

  lc.shutdown(0,false);
  /* Set the brightness to a medium values */
  lc.setIntensity(0,8);
  /* and clear the display */
  lc.clearDisplay(0);

  WiFi.mode(WIFI_STA);
  WiFi.begin (ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println("WiFi connected");
}

void printLCD(int v, int a, int b) {
    int ones;
    int tens;
    
    ones=v%10;
    v=v/10;
    tens=v%10;

    lc.setDigit(0,a,(byte)ones,false);
    lc.setDigit(0,b,(byte)tens,false);
}

void loop() {

  // first parameter: Time zone in floating point (for India); second parameter: 1 for European summer time; 2 for US daylight saving time; 0 for no DST adjustment; (contributed by viewwer, not tested by me)
  dateTime = NTPch.getNTPtime(0.0, 1);

  // check dateTime.valid before using the returned time
  // Use "setSendInterval" or "setRecvTimeout" if required
  if(dateTime.valid){
    //NTPch.printDateTime(dateTime);

//    byte actualHour = dateTime.hour;
//    byte actualMinute = dateTime.minute;
//    byte actualsecond = dateTime.second;
//    int actualyear = dateTime.year;
//    byte actualMonth = dateTime.month;
//    byte actualday =dateTime.day;
//    byte actualdayofWeek = dateTime.dayofWeek;
    

  printLCD(dateTime.second, 0, 1);
  lc.setChar(0,2,'-',false);
  printLCD(dateTime.minute, 3, 4);  
  lc.setChar(0,5,'-',false);
  printLCD(dateTime.hour, 6, 7); 
  delay(1000);


  }
}
