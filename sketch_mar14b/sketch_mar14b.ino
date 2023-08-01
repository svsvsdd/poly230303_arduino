#include <EEPROM.h>

int address = 0;
unsigned char value;

void setup() {
  Serial.begin(9600);

  }


void loop() {
  value = EEPROM.read(address);
  Serial.print(address);
  Serial.print("\t");
  Serial.print(value, BIN);
  Serial.println();
    address = address + 1;
  if (address == EEPROM.length()){
    address = 0;
  }  
  delay(500);
}
