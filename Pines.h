

/********************************************************
 * Definicion de pines para robot seguidor de linea
 * 
 * configuración de board que se este usando
 * 
 ********************************************************/
 #pragma once
/********************************************************
 * Definiciones para las shield disponibles
 * Comentar la linea define para usar o no la shield
 * 
 * ShieldMotor adafruit 0
 * Shield SENA TB6612   1
 * Shield STM32         2
 * Shield ESP32         3
 * 
 *******************************************************/
#define SHIELD_ADAFRUIT
//***********************************
#ifdef SHIELD_ADAFRUIT

#include <AFMotor.h>
#include "ShieldMotor.h"
#include "DIRl293.h"
#endif


//****************************************
//#define SHIELD_SENA 
//**************************
#ifdef SHIELD_SENA 

#include <SparkFun_TB6612.h>
#include "Shield_tb6612.h"
#include "DIRTB6612.h"

#endif

//*************************************************
// Tiempos de tareas
#define Ts1 50      // Periodo de la tarea 1 LED blink
#define Ts2 50      // Periodo de la tarea 2 Medicion Sensor

//************************************************

// tarea de comunicacion configura la velocidad (9600,...)
#define BAUD_RATE 115200

// configura el pin de blink led
#define BLED_PCU  13

// configura los pines de conexion de sensor HC-SR04
#define TRIGGER  A0
#define ECHO A1
