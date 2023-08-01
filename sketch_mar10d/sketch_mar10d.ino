int R = 9;
int G = 10;
int B = 11;


void setup() {
pinMode(R, OUTPUT);  // put your setup code here, to run once:
pinMode(G, OUTPUT); 
pinMode(B, OUTPUT); 
}

void loop() {
RGB_color(255, 0, 0);
delay(1000);
RGB_color(0, 255, 0);
delay(1000);
RGB_color(0, 0, 255);
delay(1000);
RGB_color(255, 255, 125);
delay(1000);
RGB_color(0, 255, 255);
delay(1000);
RGB_color(255, 0, 255);
delay(1000);
RGB_color(255, 255, 0);
delay(1000);
RGB_color(255, 255, 255);
delay(1000);
}

void RGB_color(int red_light_value, int green_light_value, int blue_light_value)
{
  analogWrite(R, red_light_value);
analogWrite(G, green_light_value);
analogWrite(B, blue_light_value);
  }


