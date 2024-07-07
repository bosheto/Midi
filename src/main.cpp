#include <Arduino.h>
#include "buttons.h"



void setup() {
  Serial.begin(9600);
  SetButtonEnable(false);
  SetupButtons();
}

void loop() {
  ButtonsLoop();
 
}
