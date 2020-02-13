#define BLYNK_PRINT Serial

#include <Wire.h>
#include <TimeLib.h>
#include <ESP8266WiFi.h>
#include <LiquidCrystal_I2C.h>
#include <BlynkSimpleEsp8266.h>
#include <WidgetRTC.h>

// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2);

BlynkTimer timer;
WidgetRTC rtc;

// Attach virtual serial terminal to Virtual Pin V0
WidgetTerminal terminal(V0);

/***** Constants *****/

// For Blynk
char auth[] = "x9tDcNjDcBXq8qMhxm9HWVzrUEx-cbYZ";
char ssid[] = "Win's Family 2.4Ghz";
char pass[] = "phoehtaungwin";

// For Switch
int switchPin = 14; // GPIO 14, at D5
int prevState = -1;
int currState = -1;
long lastChangeTime = 0;

// For Backlight
boolean flashBacklight = false;

// For LCD Display
String message = "";

// For Time and Day
int timeAndDateTimerID;
String timeString = "hh:mm:ss";
String dateString = "dd:MMM:WDD";
String weekdayTable[] = {"???", "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
String monthTable[] = {"???", "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};

/***** END Constants *****/


/***** Helper Functions (Non Blynk Related) *****/

String getFormattedTimeString() {
  String hh, mm, ss;
  
  if (hour() < 10) {
    hh = "0"+String(hour());
  } else {
    hh = String(hour());
  }
  
  if (minute() < 10) {
    mm = "0"+String(minute());
  } else {
    mm = String(minute());
  }
  
  if (second() < 10) {
    ss = "0"+String(second());
  } else {
    ss = String(second());
  }

  return hh+":"+mm+":"+ss;
}

String getFormattedDateString(){
  String dd, mmm, wdd;
  
  if (day() < 10) {
    dd = "0"+String(day());
  } else {
    dd = String(day());
  }

  mmm = monthTable[month()];

  wdd = weekdayTable[weekday()];

  return dd+" "+mmm+" "+wdd;
}

// Centralized Display
// Time on 1st Row
// Date on 2nd row
void timeAndDateDisplay() 
{
  timeString = getFormattedTimeString();
  lcd.setCursor(4,0);
  for (int i=0; i<timeString.length(); i++) {
    lcd.print(timeString[i]);
  }

  dateString = getFormattedDateString();
  lcd.setCursor(3,1);
  for (int i=0; i<dateString.length(); i++) {
    lcd.print(dateString[i]);
  }
}

void checkPin()
{
  // Invert state, since button is "Active LOW"
  int state = !digitalRead(switchPin);

  // Debounce mechanism
  long t = millis();
  if (state != prevState) {
    lastChangeTime = t;
  }
  if (t - lastChangeTime > 50) {
    if (state != currState) {
      currState = state;
      if (flashBacklight) {
        // Stop flashing backlight
        flashBacklight = false;
      } else {
        // Display acknowledgement on BlynkApp Terminal
        terminal.println("-----Acknowledged-----");
        terminal.println("");
        terminal.println(getFormattedTimeString());
        terminal.println("");
        terminal.flush();
  
        // Resume Time & Date display
        message = "";
        lcd.clear();
        timer.enable(timeAndDateTimerID);
      }
    }
  }
  prevState = state;
}

void backlightToggle()
{
  if (flashBacklight) {
    lcd.noBacklight();
    delay(400);
    lcd.backlight();
    delay(400);
  } else {
    lcd.backlight();
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

// When there is an input to VirtualPin 0 from Terminal Widget 
BLYNK_WRITE(V0) 
{
  // To check the status
  // Display "Ready" to Terminal Widget
  if (String("/") == param.asStr()) {
    terminal.println("-----Ready-----");
    terminal.println("");
    terminal.flush();
  } 
  else {
    // Parse message
    message = param.asStr();

    // Cannot fit at all... for now!
    if (message.length() >= 32) {
      terminal.println("-----Too Large-----");
      terminal.println("");
      terminal.flush();
      
      message = "";
      
      return;
    }

    // Pause Time & Date from displaying
    timer.disable(timeAndDateTimerID);
    lcd.clear();

    // Can' fit in one row
    // Break to two rows and display
    if (message.length() >= 16) {
      // First row
      lcd.home();
      for (int charIndex=0; charIndex<16; charIndex++) {
        lcd.print(message[charIndex]);
      }
      // Second row
      lcd.setCursor(0,1);
      for (int charIndex=16; charIndex<message.length(); charIndex++) {
        lcd.print(message[charIndex]);
      }
    }
    else { // Can fit into one row
      lcd.print(message);
    }

    flashBacklight = true;

    // Display on BlynkApp Terminal
    terminal.println("-----Waiting For ACK-----");
    terminal.println();
    terminal.println(getFormattedTimeString());
    terminal.println();
    terminal.flush();
  }
}

/***** END BLYNK Related Functions *****/


void setup()
{
  // Debug console 
  Serial.begin(9600);

  // Initialize LCD
  // Hardware LCD. SDA=GPIO 4, SCL=GPIO 5
  lcd.begin(4, 5);
  lcd.backlight();
  lcd.setCursor(2,0);
  lcd.print("Me izzu wait");
  lcd.setCursor(2,1);
  lcd.print("da interneto");

  // Initialize switch
  pinMode(switchPin, INPUT_PULLUP);

  // Start the Blynk Magic
  Blynk.begin(auth, ssid, pass);
  rtc.begin();

  // Sycn RTC time every 100 seconds
  timer.setInterval(100000L, requestTime);
  
  // Timers
  // Begin our first state. Centralized Time & Date display
  timeAndDateTimerID = timer.setInterval(1000L, timeAndDateDisplay);
  timer.setInterval(500L, checkPin);
  timer.setInterval(1000L, backlightToggle);
  
  lcd.clear();

  // Display to terminal widget
  terminal.println("-----Restarted-----");
  terminal.println("");
  terminal.flush();
  
}

void loop()
{
  Blynk.run();
  timer.run();
}
