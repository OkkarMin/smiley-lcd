#define BLYNK_PRINT Serial

#include <Wire.h>
#include <TimeLib.h>
#include <ESP8266WiFi.h>
#include <LiquidCrystal_I2C.h>
#include <BlynkSimpleEsp8266.h>

// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2);

BlynkTimer timer;

/***** Constants *****/

// For Blynk
char auth[] = "x9tDcNjDcBXq8qMhxm9HWVzrUEx-cbYZ";
char ssid[] = "Win's Family 2.4Ghz";
char pass[] = "phoehtaungwin";

// For Switch
int switchPin = 16; // at D0

// For Time and Day
String timeString = "hh:mm:ss";
String dateString = "dd:MMM:WDD";
String weekdayTable[] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
String monthTable[] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
int timeAndDateTimerID;

/***** END Constants *****/


/***** Helper Functions (Non Blynk Related) *****/

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

// Centralized Display
// Time on 1st Row
// Date on 2nd row
void timeAndDateDisplay() 
{
  timeString = getFormattedTimeString(hour(),minute(),second());
  lcd.setCursor(4,0);
  for (int i=0; i<timeString.length(); i++) {
    lcd.print(timeString[i]);
  }

  dateString = getFormattedDateString(day(), month(), weekday());
  lcd.setCursor(3,1);
  for (int i=0; i<dateString.length(); i++) {
    lcd.print(dateString[i]);
  }
}

/***** END Helper Functions (Non Blynk Related) *****/


/***** BLYNK Related Functions *****/

// To sync time every 10 sec
// Look in setup()
void requestTime() 
{
  Blynk.sendInternal("rtc", "sync");
}

// Attach virtual serial terminal to Virtual Pin V0
WidgetTerminal terminal(V0);

// When there is an input to VirtualPin 0 from Terminal Widget 
BLYNK_WRITE(V0) 
{
  // To check the status
  // Writes "Ready" to Terminal Widget
  if (String("/") == param.asStr()) {
    terminal.println("Ready!");
  } 
  else {
    // Pause Time & Date from displaying
    timer.disable(timeAndDateTimerID);
    
    // Parse message
    String message = param.asStr();

    // Display on Hardware LCD
    lcd.clear();
    lcd.home();
    lcd.print(message);

    // Display on BlynkApp Terminal
    terminal.print("Displayed: ");
    terminal.println(message);
    terminal.println();
    terminal.println("----Waiting For ACK----");

    // Ensure everything is sent to BlynkApp Terminal
    terminal.flush();

    // Flash Backlight till button press for acknowledgement
    while (1) {
      lcd.noBacklight();
      delay(400);
      lcd.backlight();
      delay(400);
      
      if (!digitalRead(switchPin)) {
        lcd.backlight();
        break;
      }
    }

    // Display acknowledgement on BlynkApp Terminal
    terminal.println("Acknowledged!");
    terminal.println("----------------");
    terminal.println("");
  }

  // Ensure everything is sent to BlynkApp Terminal
  terminal.flush();

  // Resume Time & Date from displaying
  timer.enable(timeAndDateTimerID);
}

/***** END BLYNK Related Functions *****/


void setup()
{
  // Debug console 
  Serial.begin(9600);

  // Init LCD
  // Hardware LCD. SDA=GPIO 4, SCL=GPIO 5
  lcd.begin(4,5);
  lcd.backlight();

  // Start the Blynk Magic
  Blynk.begin(auth, ssid, pass);

  // Sycn RTC time every 10 seconds
  timer.setInterval(10000L, requestTime);

  // Begin our first state. Centralized Time & Date display
  timeAndDateTimerID = timer.setInterval(1000L, timeAndDateDisplay);
}

void loop()
{
  Blynk.run();
  timer.run();
}
