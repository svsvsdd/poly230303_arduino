#include <Wire.h>
#include <EEPROM.h>
#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>
#include <JC_Button.h>

Button joystickSelect(A0, 10, true, false); // 조이스틱 Select 버튼 설정
Button joystickUp(A1, 10, true, false); // 조이스틱 Up 버튼 설정
Button joystickDown(A2, 10, true, false); // 조이스틱 Down 버튼 설정

SoftwareSerial BTserial(9, 8); // 블루투스 모듈 RX, TX 설정
LiquidCrystal_I2C lcd(0x3F, 16, 2); // 16x2 I2C LCD 설정

int alarmHour = 0; // 알람 설정 시
int alarmMinute = 0; // 알람 설정 분
int alarmSecond = 0; // 알람 설정 초
int alarmSound = 0; // 알람 노래 소리 선택
bool alarmOn = false; // 알람이 울리는 상태인지 여부

int hour = 0; // 현재 시
int minute = 0; // 현재 분
int second = 0; // 현재 초
bool timeSetMode = false; // 시간 설정 모드인지 여부
bool alarmSetMode = false; // 알람 시간 설정 모드인지 여부
bool alarmSoundSetMode = false; // 알람 노래 소리 선택 모드인지 여부
bool isAlarmSounding = false; // 알람 소리가 울리고 있는지 여부

const int EEPROM_ALARM_HOUR_ADDR = 0; // EEPROM 주소: 알람 시간 시
const int EEPROM_ALARM_MINUTE_ADDR = 1; // EEPROM 주소: 알람 시간 분
const int EEPROM_ALARM_SECOND_ADDR = 2; // EEPROM 주소: 알람 시간 초
const int EEPROM_ALARM_SOUND_ADDR = 3; // EEPROM 주소: 알람 노래 소리 선택

void setup() {
    lcd.init(); // LCD 초기화
    lcd.backlight(); // LCD 백라이트 켜기
    lcd.setCursor(0, 0); // LCD 커서 위치 설정
    lcd.print("Korea Polytech"); // 첫 번째 줄에 "Korea Polytech" 출력

    joystickSelect.begin(); // 조이스틱 Select 버튼 설정 시작
    joystickUp.begin(); // 조이스틱 Up 버튼 설정 시작
    joystickDown.begin(); // 조이스틱 Down 버튼 설정 시작

    BTserial.begin(9600); // 블루투스 시리얼 통신 시작

    // EEPROM에서 알람 시간과 노래 소리를 읽어옴
    alarmHour = EEPROM.read(EEPROM_ALARM_HOUR_ADDR);
    alarmMinute = EEPROM.read(EEPROM_ALARM_MINUTE_ADDR);
    alarmSecond = EEPROM.read(EEPROM_ALARM_SECOND_ADDR);
    alarmSound = EEPROM.read(EEPROM_ALARM_SOUND_ADDR);
}

void loop() {
    // 현재 시간 읽어오기
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis >= 1000) { // 1초마다 시간 업데이트








        previousMillis = currentMillis;

        // 현재 시간 읽어오기
        int hour = RTC.getHour(h12, PM); // 시
        int minute = RTC.getMinute(); // 분
        int second = RTC.getSecond(); // 초
        bool pm = RTC.getPM(); // PM 여부

        // 알람 울리는 시간과 현재 시간이 일치하는지 확인
        if (alarmOn && hour == alarmHour && minute == alarmMinute && second == alarmSecond) {
            playAlarmSound();
        }

        // 시간 설정 모드인 경우 blink 처리
        if (settingTime) {
            blink = !blink;
        }

        // LCD에 표시할 시간 문자열 만들기
        String timeString = String(hour) + ":" + (minute < 10 ? "0" : "") + String(minute) + ":" + (second < 10 ? "0" : "") + String(second) + (pm ? " PM" : " AM");

        // LCD 첫번째 줄에 "Korea Polytech" 출력
        lcd.setCursor(0, 0);
        lcd.print("Korea Polytech");

        // LCD 두번째 줄에 현재 시간 출력
        lcd.setCursor(0, 1);
        if (settingTime && blink) {
            lcd.print(" ");
        }
        else {
            lcd.print(timeString);
        }

        // 조이스틱 select 버튼 클릭 시
        joystickSelect.read();
        if (joystickSelect.wasPressed()) {
            if (!settingTime) {
                settingTime = true;
                blink = true;
                lcd.clear();
            }
            else {
                // 시간 설정 모드에서 select 버튼 클릭 시 다음 항목으로 넘어감
                switch (settingIndex) {
                case 0:
                    settingIndex = 1;
                    break;
                case 1:
                    settingIndex = 2;
                    break;
                case 2:
                    settingIndex = 3;
                    break;
                case 3:
                    settingTime = false;
                    blink = false;
                    settingIndex = 0;
                    lcd.clear();
                    // 설정된 시간을 EEPROM에 저장
                    EEPROM.write(0, hour);
                    EEPROM.write(1, minute);
                    EEPROM.write(2, second);
                    EEPROM.write(3, pm ? 1 : 0);
                    EEPROM.commit();
                    break;
                }
            }
        }

        // 조이스틱 up 버튼 클릭 시
        joystickUp.read();
        if (joystickUp.wasPressed()) {
            if (settingTime) {
                switch (settingIndex) {
                case 0: // AM/PM 설정
                    pm = !pm;
                    break;
                case 1: // 시간 설정
                    hour = (hour + 1) % 12;
                    if (hour == 0) {
                        hour = 12;
                    }
                    break;
                case 2: // 분 설정
                    minute = (minute + 1) % 60;
                    break;
                case 3: // 초 설정
                    second = (second + 1) % 60;
                    break;
                }
            }
        }

        // 조이스틱 down 버튼 클릭 시
        joystickDown.read();
        if (joystickDown.wasPressed()) {
            if (settingTime) {
                switch (settingIndex) {
                case 0: // AM/PM 설정
                    pm = !pm;
                    break;
                case 1: // 시간 설정
                    hour = (hour + 11) % 12;
                    if (hour == 0) {
                        hour = 12;
                    }
                    break;
                case 2: // 분 설정
                    minute = (minute + 59) % 60;
                    break;
                case 3: // 초 설정
                    second = (second + 59) % 60;
                    break;
                case 4: // 알람 노래 소리 선택
                    alarmSound = (alarmSound + 1) % 2;
                    break;
                }
                updateDisplay();
            }
        }
        // 조이스틱 select 버튼 클릭 시
        joystickSelect.read();
        if (joystickSelect.wasPressed()) {
            if (!settingTime) {
                settingIndex = 0;
                settingTime = true;
            }
            else {
                settingIndex = (settingIndex + 1) % 5;
                if (settingIndex == 0) {
                    settingTime = false;
                }
            }
            updateDisplay();
        }
        // 조이스틱 select 버튼 3초 이상 누를 시 알람 시간 설정 모드
        if (joystickSelect.pressedFor(3000)) {
            settingAlarmTime = true;
            alarmHour = 0;
            alarmMinute = 0;
            alarmSecond = 0;
            alarmSound = 0;
            updateDisplay();
        }
        // 알람 시간 설정 모드에서 조이스틱 select 버튼 클릭 시
        if (settingAlarmTime && joystickSelect.wasPressed()) {
            settingAlarmTime = false;
            EEPROM.write(0, alarmHour);
            EEPROM.write(1, alarmMinute);
            EEPROM.write(2, alarmSecond);
            EEPROM.write(3, alarmSound);
        }
        // 더블클릭으로 알람 노래 소리 선택 모드 진입
        if (joystickSelect.pressedFor(500)) {
            if (joystickSelect.wasReleased()) {
                joystickSelect.reset();
                if (joystickSelect.wasPressed()) {
                    if (settingAlarmTime) {
                        alarmSound = (alarmSound + 1) % 2;
                        updateDisplay();
                    }
                }
            }
        }
        // 알람 울리는지 확인
        if (alarmOn && hour == alarmHour && minute == alarmMinute && second == alarmSecond) {
            playAlarm();
        }
    }








    /*
    }

    // 알람 울리는지 확인
    if (alarmOn && hour == alarmHour && minute == alarmMinute && second == alarmSecond) {
    playAlarm();
    }*/

    // 알람 울리는 중이면 알람 소리 정지 처리
    if (alarmPlaying) {
        joystickSelect.read();
        if (joystickSelect.wasPressed()) {
            stopAlarm();
        }
    }

