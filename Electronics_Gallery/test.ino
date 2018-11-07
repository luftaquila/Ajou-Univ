#include "HX711.h"
#include <Keyboard.h>

#define calibration_factor -7050.0 //This value is obtained using the SparkFun_HX711_Calibration sketch

#define DOUT  12
#define CLK  11

HX711 scale(DOUT, CLK);

void setup() {
  for(int i = 2; i < 11; i++)  {pinMode(i, INPUT_PULLUP); }
  Keyboard.begin();
  Serial.begin(9600);

  scale.set_scale(calibration_factor);
  scale.tare();
}

void loop() {
  float weight = scale.get_units() * 0.4536;
  if(weight < 0.5) Serial.println(1);
  else if(weight >= 0.5 && weight < 1) Serial.println(2);
  else Serial.println(3);

  sendKey(2, 113, 30);// Q
  sendKey(3, 101, 30);// E
  sendKey(5, ' ', 30);// Space Bar
  sendKey(6, 'a', 30);// A
  sendKey(7, 'w', 30);// W
  sendKey(9, 'd', 30);// D
  sendKey(8, 's', 30);// S
  sendKey(10, KEY_ESC, 30);// Esc

  if(digitalRead(4) == LOW)
  {
    Keyboard.press(KEY_LEFT_ALT);
    delay(10);
    Keyboard.press(KEY_TAB);
    delay(30);
    Keyboard.releaseAll();
  }
  
  if(digitalRead(13) == LOW)
  {
    Keyboard.press(KEY_LEFT_ALT);
    delay(10);
    Keyboard.press(KEY_F4);
    delay(30);
    Keyboard.releaseAll();
  }
}

void sendKey(int pin, char key, int wait)
{
  if(digitalRead(pin) == LOW)
  {
    Keyboard.press(key);
    delay(wait);
    Keyboard.releaseAll();
  }
}
