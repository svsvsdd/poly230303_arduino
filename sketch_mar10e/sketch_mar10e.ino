void setup() {
  Serial.begin(9600);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);  
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
}
 
void loop() {
  int val_0 = analogRead(A0);
  int val_1 = analogRead(A1);
  Serial.print("VRx : ");
  Serial.print(val_0);
  Serial.print("    ");
  Serial.print("VRy : ");
  Serial.println(val_1);
  delay(200);
  if (val_0 < 300) {
    digitalWrite(6, HIGH);
  }
  else if (val_0 > 700) {
    digitalWrite(5, HIGH);
  }
  else {
    digitalWrite(5, LOW);
    digitalWrite(6, LOW);
  }
  
  if (val_1 < 300) {
    digitalWrite(3, HIGH);
  }
  else if (val_1 > 700) {
    digitalWrite(4, HIGH);
  }
  else {
    digitalWrite(3, LOW);
    digitalWrite(4, LOW);
  }
}

