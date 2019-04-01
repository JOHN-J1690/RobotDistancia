/*******************************************************************************
 * 
 * Tarea de blink led usando planeador de tareas
 * Al utilizar esta tarea nos percatamos de que el planeador este en funcionamiento
 * se debe declarar BLED_PCU en pines.h para cambiar el pin de salida
 * 
*****************************************************************************/
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
