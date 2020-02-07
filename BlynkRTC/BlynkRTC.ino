/*************************************************************
  Download latest Blynk library here:
    https://github.com/blynkkk/blynk-library/releases/latest

  Blynk is a platform with iOS and Android apps to control
  Arduino, Raspberry Pi and the likes over the Internet.
  You can easily build graphic interfaces for all your
  projects by simply dragging and dropping widgets.

    Downloads, docs, tutorials: http://www.blynk.cc
    Sketch generator:           http://examples.blynk.cc
    Blynk community:            http://community.blynk.cc
    Follow us:                  http://www.fb.com/blynkapp
                                http://twitter.com/blynk_app

  Blynk library is licensed under MIT license
  This example code is in public domain.

 *************************************************************

  Blynk can provide your device with time data, like an RTC.
  Please note that the accuracy of this method is up to several seconds.

  App project setup:
    RTC widget (no pin required)
    Value Display widget on V1
    Value Display widget on V2

  WARNING :
  For this example you'll need Time keeping library:
    https://github.com/PaulStoffregen/Time

  This code is based on an example from the Time library:
    https://github.com/PaulStoffregen/Time/blob/master/examples/TimeSerial/TimeSerial.ino
 *************************************************************/

/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial


#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <BlynkSimpleEsp8266.h>
#include <NTPClient.h>
#include <TimeLib.h>
#include <WidgetRTC.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "x9tDcNjDcBXq8qMhxm9HWVzrUEx-cbYZ";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "Win's Family 2.4Ghz";
char pass[] = "phoehtaungwin";

BlynkTimer timer;

WidgetRTC rtc;

WiFiUDP ntpUDP;

// You can specify the time server pool and the offset, (in seconds)
// additionaly you can specify the update interval (in milliseconds).
NTPClient timeClient(ntpUDP);

// Digital clock display of the time
void clockDisplay()
{
  timeClient.update();
  time_t utcCalc = timeClient.getEpochTime();
  
  String currentTime = String(timeClient.getFormattedTime());
  String currentDate = String(String(weekday(utcCalc)) + " " + String(day(utcCalc)) + " " + String(month(utcCalc)));
  
  Serial.print("Current time: ");
  Serial.print(currentTime);
  Serial.print(" ");
  Serial.print(currentDate);
  Serial.println(" ");

  // Send time to the App
  Blynk.virtualWrite(V1, currentTime);
  Blynk.virtualWrite(V2, currentDate);
}

void setup()
{
  // Debug console
  Serial.begin(9600);

  Blynk.begin(auth, ssid, pass);

  // Begin synchronizing time
  timeClient.begin();
  timeClient.setTimeOffset(28800);
  timeClient.update();

  // Display digital clock every 10 seconds
  timer.setInterval(5000L, clockDisplay);
}

void loop()
{
  Blynk.run();
  timer.run();
}
