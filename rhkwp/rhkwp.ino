void setup() {
  Serial.begin(9600);
  pinMode(8,INPUT_PULLUP);

}

void loop() {
  long pressed = pulseIn(8,LOW,10000000L);
  if(pressed)

    Serial.println(pressed);

}
