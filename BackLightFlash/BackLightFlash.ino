#include <LiquidCrystal_I2C.h>
#include <Wire.h>

// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2);

int switchPin = 16; // at D0
volatile bool pinChanged = false;
volatile int  pinValue   = 0;

void startBacklightFlash() {
  while (1) {
    lcd.noBacklight();
    delay(400);
    lcd.backlight();
    delay(400);

    if (!digitalRead(switchPin)) {
      stopBacklightFlash();
      break;
    }
  }
}

void stopBacklightFlash() {
  lcd.backlight();
  lcd.scrollDisplayLeft();
}

void setup()
{
  // initialize the LCD
  lcd.begin(4,5);  // sda=0, scl=2
  lcd.backlight();
  lcd.print("abcdefghijklmnop");
  lcd.setCursor(0,1);
  lcd.print("0123456789876543");

  // initialize the Switch
  pinMode(switchPin, INPUT_PULLUP);

  // start
  startBacklightFlash();
}

void loop()
{
}
