#include <EEPROM.h>

byte value;
byte plusInLitres = 10;
byte afterLockAdding = 3;
int coldWaterAmount = 3024510;
int hotWaterAmount = 0;
struct{
  int cold = 0;
  int hot = cold + sizeof(cold);
} EEAddress;
const int coldWaterPin = 2;
const int hotWaterPin = 0;
struct{
  boolean isColdWaterLocked = false;
  boolean isHotWaterLocked = false;
} SignalStatus;

void writeEEPROM(int waterPin, int waterAmount, boolean signalStatus, int EEAddress){  
  if (!signalStatus && digitalRead(waterPin) == LOW) {
    signalStatus = true;
    EEPROM.put(EEAddress, waterAmount + plusInLitres);
    EEPROM.commit();
    delay(200);
  }

  if (signalStatus && digitalRead(waterPin) == HIGH) {
    signalStatus = false;
    EEPROM.put(EEAddress, waterAmount + afterLockAdding);
    EEPROM.commit();
    delay(200);
  }
}

void updateCounters(int waterPin){
  switch (waterPin) {
      case 0:
        writeEEPROM(waterPin, hotWaterAmount, SignalStatus.isHotWaterLocked, EEAddress.hot);
        break;
      case 2:
        writeEEPROM(waterPin, coldWaterAmount, SignalStatus.isColdWaterLocked, EEAddress.cold);
         EEPROM.get(EEAddress.cold, coldWaterAmount);
         Serial.print(EEAddress.cold);
         Serial.println("\t");
         Serial.println(coldWaterAmount, DEC);
         delay(200);
        break;
      default:
        Serial.println("Writing to EEPROM is failed");
  }
}

void updateColdWaterCounters(){
  updateCounters(coldWaterPin);
}

void updateHotWaterCounters(){
  updateCounters(hotWaterPin);
}

void setup()
{
  Serial.begin(115200);
  EEPROM.begin(8);
  EEPROM.put(EEAddress.cold, coldWaterAmount);
  EEPROM.commit();
  pinMode(coldWaterPin, INPUT_PULLUP);
  pinMode(hotWaterPin, INPUT_PULLUP);
}

void loop(){
  
  attachInterrupt(coldWaterPin, updateColdWaterCounters, CHANGE);

  // EEPROM.get(EEAddress.cold, coldWaterAmount);
  // Serial.print(EEAddress.cold);
  // Serial.print("\t");
  // Serial.print(coldWaterAmount, DEC);
  // Serial.println(digitalPinToInterrupt(coldWaterPin));

//  digitalPinToInterrupt(coldWaterPin);
  
  // delay(200);
}
