#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <EEPROM.h>
LiquidCrystal_I2C lcd(0x27,16,2);
int h;
int m;
int s;
const int hourAdd = 0;
const int minuteAdd = 2;
const int secondAdd = 4;
void setup() {
  Serial.begin(9600);
  lcd.begin();
  lcd.backlight();
  h = EEPROM.read(hourAdd);
  m = EEPROM.read(minuteAdd);
  s = EEPROM.read(secondAdd);
}
void loop() {
  lcd.setCursor(4,0);
  lcd.print("POLYTECH");
  h = EEPROM.read(hourAdd);
  m = EEPROM.read(minuteAdd);
  s = EEPROM.read(secondAdd);
  if(++s == 60) {
    s = 0;
    if(++m == 60) {
      m = 0;
      if(++h == 24) {
        h = 0;
      }
    }
  }
  EEPROM.write(hourAdd, h);
  EEPROM.write(minuteAdd, m);
  EEPROM.write(secondAdd, s);
  String hourStr = "";
  if (h < 10) {
    hourStr += "0";
  }
  hourStr += String(h);
  String minuteStr = "";
  if (m < 10) {
    minuteStr += "0";
  }
  minuteStr += String(m);
  String secondStr = "";
  if (s < 10) {
    secondStr += "0";
  }
  secondStr += String(s);
  String ampmStr = "";
  if (h < 12) {
    ampmStr = "AM";
  } else {
    ampmStr = "PM";
    if (h > 12) {
      h = h-12;
    }
  }
  String timeStr = ampmStr + " " +hourStr + ":" + minuteStr + ":" + secondStr;
  lcd.setCursor(0, 1);
  lcd.print(timeStr);
  delay(1000);
}