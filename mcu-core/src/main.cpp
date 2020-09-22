#include <Arduino.h>
#include <SoftwareSerial.h>

#define BT_RX 3
#define BT_TX 4

#define INPUT_A 9

#define BUZZER 13
#define LED_STANDBY 12
#define LED_START 11
#define LED_SENDING 10

#define STARTING '1'

#define NUM_INPUT 1
#define NUM_OUTPUT 4

SoftwareSerial bluetooth(BT_TX, BT_RX);

void ledIndicator(int pins) {
  digitalWrite(LED_START, pins == LED_START ? 1 : 0);
  digitalWrite(LED_STANDBY, pins == LED_STANDBY ? 1 : 0);
  digitalWrite(LED_SENDING, pins == LED_SENDING ? 1 : 0);
}

void setup() {
  bluetooth.begin(9600);
  int num = NUM_OUTPUT + NUM_INPUT, pins[num] = {
    LED_STANDBY, LED_START, LED_SENDING, BUZZER,
    INPUT_A
  };
  for (int i = 0; i < num; i ++) {
    pinMode(pins[i], i < NUM_OUTPUT ? 1 : 0);
  }
}

void loop() {
  ledIndicator(LED_STANDBY);
  if (bluetooth.available() > 0) {
    char recv = bluetooth.read();
    if (recv == STARTING) {
      ledIndicator(LED_START);
      unsigned long finalCounter = 0, startCounter = millis();
      while (true) {
        if (digitalRead(INPUT_A)) {
          break;
        }
        finalCounter = millis();
      }
      ledIndicator(LED_SENDING);
      bluetooth.print(finalCounter - startCounter);
      delay(500);
    }
  }
}
