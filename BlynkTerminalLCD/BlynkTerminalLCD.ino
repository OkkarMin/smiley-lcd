#include <Wire.h>
#include <ESP8266WiFi.h>
#include <LiquidCrystal_I2C.h>
#include <BlynkSimpleEsp8266.h>

char auth[] = "x9tDcNjDcBXq8qMhxm9HWVzrUEx-cbYZ";

// Set password to "" for open networks.
char ssid[] = "Win's Family 2.4Ghz";
char pass[] = "phoehtaungwin";

// Attach virtual serial terminal to Virtual Pin V0
WidgetTerminal terminal(V0);

// Sends to BlynkApp V0
// When there is an input to V0 from Terminal Widget 
BLYNK_WRITE(V0) {
  // Display 'Ready!' on BlynkApp Terminal
  if (String("/") == param.asStr()) {
    terminal.println("Ready!");
  } else {
    // Display on Hardware LCD
    lcd.clear();
    lcd.home();
    lcd.print(param.asStr());

    // Display on BlynkApp Terminal
    String text = param.asStr();
    terminal.print("Displayed: ");
    terminal.println(text);
    terminal.println();
  }

  // Ensure everything is sent
  terminal.flush();
}

void setup()
{
  // Debug console
  Serial.begin(9600);

  // Hardware LCD. SDA=4, SCL=5
  lcd.begin(4,5);
  lcd.backlight();

  // Start the Blynk Magic
  Blynk.begin(auth, ssid, pass);

  // This will print Blynk Software version to the Terminal Widget when
  // your hardware gets connected to Blynk Server
  terminal.println(F("Blynk v" BLYNK_VERSION ": Device started"));
  terminal.println(F("****----****"));
  terminal.flush();
}

void loop()
{
  Blynk.run();
}
