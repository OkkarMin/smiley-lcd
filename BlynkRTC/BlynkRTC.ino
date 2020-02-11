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
//char ssid[] = "Win's Family 2.4Ghz";
//char pass[] = "phoehtaungwin";
char ssid[] = "JiaJun's iPhone";
char pass[] = "g7kx5rx1hiqfg";

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
