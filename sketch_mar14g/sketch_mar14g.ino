#include <EEPROM.h>

void setup() {
  // put your setup code here, to run once:
  int value1 = 512;  //Variable to store in EEPROM. 0x200
  int value2 = 270;  //0x10E
  int eeAddress = 0;   //Location we want the data to be put.
  int temp = 0;

  Serial.begin(9600);
  EEPROM.put(eeAddress, value1);
  EEPROM.put(eeAddress + sizeof(int), value2);

  temp =EEPROM.read(0);
  Serial.println(temp);
  temp =EEPROM.read(1);
  Serial.println(temp);
  temp =EEPROM.read(2);
  Serial.println(temp);
  temp =EEPROM.read(3);
  Serial.println(temp);


}

void loop() {
  // put your main code here, to run repeatedly:

}
