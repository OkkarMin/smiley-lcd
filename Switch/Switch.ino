int switchPin = 16; // at D0
int switchValue;

void setup() {
  Serial.begin(9600);
  pinMode(switchPin, INPUT_PULLUP);
}

void loop() {
  // Read the switch value
  switchValue = digitalRead(switchPin);
  /* Set the LED output pin the opposit of what is read on the switch
   * input pin  
   */
  Serial.println(switchValue);
}
