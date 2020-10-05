#include <Arduino.h>

#define INPUT_A A0

void setup(void) {
  Serial.begin(9600);
  pinMode(INPUT_A, INPUT);
}

void loop(void) {
  Serial.println(analogRead(INPUT_A));
}
