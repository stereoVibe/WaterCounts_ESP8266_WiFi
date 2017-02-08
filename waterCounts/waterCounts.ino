#include <EEPROM.h>

const int coldWaterPin = 1;
const int hotWaterPin = 2;

boolean isColdWaterCounts = false;
boolean isHotWaterCounts = false;

void increaseCount() {
  
  }

void setup() {
  Serial.begin(9600);
  pinMode(coldWaterPin, INPUT);
  pinMode(hotWaterPin, INPUT);
}

void loop() {
  if (isColdWaterCounts && digitalWrite(coldWaterPin) == HIGH) {
    attachInterrupt(pin, function, RISING);
  }
}
