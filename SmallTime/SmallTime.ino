  // ESP8266 with 16x2 i2c LCD
  // Compatible with the Arduino IDE 1.6.6
  // Library https://github.com/agnunez/ESP8266-I2C-LCD1602
  // Original Library https://github.com/fdebrabander/Arduino-LiquidCrystal-I2C-library
  // Modified for ESP8266 with GPIO0-SDA GPIO2-SCL and LCD1206 display
  // edit library and change Wire.begin() by Wire.begin(sda,scl) or other GPIO's used for I2C
  // and access from lcd.begin(sda,scl)
  
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <TimeLib.h>

// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2);

// For Time and Day
String timeString = "";
String dateString = "";
String weekdayTable[] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
String monthTable[] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};

String getFormattedTimeString(int hour, int minute, int second) {
  String hh, mm, ss;
  
  if (hour < 10) {
    hh = "0"+String(hour);
  } else {
    hh = String(hour);
  }
  
  if (minute < 10) {
    mm = "0"+String(minute);
  } else {
    mm = String(minute);
  }
  
  if (second < 10) {
    ss = "0"+String(second);
  } else {
    ss = String(second);
  }

  return hh+":"+mm+":"+ss;
}

String getFormattedDateString(int day, int month, int weekday) {
  String dd, mmm, wdd;
  
  if (day < 10) {
    dd = "0"+String(day);
  } else {
    dd = String(day);
  }

  mmm = monthTable[month];

  wdd = weekdayTable[weekday];

  return dd+" "+mmm+" "+wdd;
}

void setup()
{
	// initialize the LCD
	lcd.begin(4,5);  // sda=0, scl=2
	lcd.backlight();
}

void loop()
{
  timeString = getFormattedTimeString(hour(),minute(),second());
  lcd.setCursor(4,0);
  for (int i=0; i<timeString.length(); i++) {
    lcd.print(timeString[i]);
  }

  dateString = String(day())+" "+String(monthTable[month()])+" "+String(weekdayTable[weekday()]);
  lcd.setCursor(3,1);
  for (int i=0; i<dateString.length(); i++) {
    lcd.print(dateString[i]);
  }
}
