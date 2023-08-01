int time1 = 0, time2 = 0, press_time = 0, unpress_time = 0, last_press_time = 0;
volatile bool button_pressed = false;

void button_isr()
{
  button_pressed = true;
}

void loop()
{
  if (button_pressed)
  {
    button_pressed = false;

    if (digitalRead(2) == 0)
    {
      time1 = millis();
      unpress_time = time1 - time2;
    }
    else
    {
      time2 = millis();
      last_press_time = press_time;
      press_time = time2 - time1;

      if (press_time > 1000)
      {
        Serial.println("Long Key");
      }
      if (last_press_time < 500 && press_time < 500 && unpress_time < 500)
      {
        Serial.println("Double click");
      }
    }
  }
}