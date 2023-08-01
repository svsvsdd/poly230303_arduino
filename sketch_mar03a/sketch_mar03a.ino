void setup()  {
  pinMode(LED_BUILTIN, OUTPUT); // LED_BUILTIN은 내장 LED 핀입니다.
}

void loop() {
  for (int i = 0; i < 30; i++) { // 3초간 0.1초 단위로 LED 깜빡이기
    digitalWrite(LED_BUILTIN, HIGH); // LED 켜기
    delay(100); // 0.1초 동안 대기
    digitalWrite(LED_BUILTIN, LOW); // LED 끄기
    delay(100); // 0.1초 동안 대기
  }
  digitalWrite(LED_BUILTIN, LOW); // 5초 동안 LED 끄기
  delay(5000); // 5초 동안 대기

}
