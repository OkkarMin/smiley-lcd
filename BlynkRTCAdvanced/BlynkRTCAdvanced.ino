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
 *************************************************************/

/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial


#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

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

void requestTime() {
  Blynk.sendInternal("rtc", "sync");
}

BLYNK_WRITE(InternalPinRTC) {
  long t = param.asLong();
  Serial.print("Unix time: ");
  Serial.print(t);
  Serial.println();
}

void setup()
{
  // Debug console
  Serial.begin(9600);

  Blynk.begin(auth, ssid, pass);
  // You can also specify server:
  //Blynk.begin(auth, ssid, pass, "blynk-cloud.com", 80);
  //Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,100), 8080);

  timer.setInterval(10000L, requestTime);
}

void loop()
{
  Blynk.run();
  timer.run();
}
