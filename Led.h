// -- LED management task -------------------------------------------------
#pragma once

boolean LEDStatus = LOW;

 
void SetupLED() {
  pinMode(BLED_PCU,OUTPUT);
}
 
void UpdateLED(void) {
  digitalWrite(BLED_PCU, LEDStatus);
  LEDStatus = !LEDStatus;
}
