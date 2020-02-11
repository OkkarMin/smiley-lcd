#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2);


int switchPin = 16; // at D0
int switchValue;

void setup() {
  pinMode(switchPin, INPUT);
  
  lcd.begin(4,5);  // sda=0, scl=2
  lcd.backlight();
  lcd.print("Hello, world!");
}

void loop() {
  // Read the switch value
  switchValue = digitalRead(switchPin);
  lcd.print(switchValue);
}
