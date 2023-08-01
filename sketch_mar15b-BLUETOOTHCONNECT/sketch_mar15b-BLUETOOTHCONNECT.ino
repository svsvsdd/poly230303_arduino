#include <SoftwareSerial.h>
SoftwareSerial mySerial(6,7);


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("HM-10 BLE");
  mySerial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (mySerial.available())
  {
    Serial.write(mySerial.read());
  }
  if (Serial.available())
  {  mySerial.write(Serial.read());
  }
}
