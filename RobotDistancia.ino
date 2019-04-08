  
  /* *******************************************************************
 *  Planificador de tareas, basado en el trabajo de:
 *  
 *  http://www.jovenescientificos.es/programacion-asincrona-de-arduino/
 *  
 *  En este planificador se llaman las tareas de forma temporizada
 *  
 *  
 **************************************************************/
// -- Librerias ------------------------------------------
//Espacio para agregar las librerias necesitadas en el proyecto 

float dist();

//---Llamada a las diferentes tareas realizadas en .h----
#include "Pines.h"              // Configuracion de pines y shields a utilizar
#include "Led.h"                // Se debe incluir todas las tareas que se han agregado como .h entre comillas dobles
#include "Distancia.h"    // Tarea para medir distancia para el uso en el planeador de tareas
#include "Pid.h"
#include "Comm.h"               // Tarea de comunicacion y algunos comandos para utilizar desde el puerto serial

 
// -- Variables de control de tiempo ---------------------
 
unsigned long int T =0;     // Tiempo total (microsegundos)
 
// -- Variables de temporizacion de tareas --------------- Creacion de variables 
 
// Tarea 1: LED

unsigned long int ts1;   // Tiempo parcial (tarea 1)
unsigned long int t01;   // Tiempo de la ultima ejecucion

 // Tarea 2: Control PID
unsigned long int ts2;   // Tiempo parcial (tarea 1)
unsigned long int t02;   // Tiempo de la ultima ejecucion

// -- Funciones de definicion de tareas ------------------

// -- Inicializacion -------------------------------------
 
void setup() {
  // Inicializacion de temporizadores de tarea
  ts1 = 0;
  t01 = 0;
  ts2 = 0;
  t02 = 0;
  SetupPid();
  SetupLED();
  SetupDist();
  SetupComm();
//  SetupMOTOR();
} 
 
// -- Bucle principal ------------------------------------
 
void loop() { 
  // Actualizar tiempo
  T = millis();               // Tiempo de planeador basado en milisegundos
  // Temporizacion tarea 1
  ts1 = T - t01;
  if (ts1 >= Ts1) {
    UpdateLED();              // en este espacio se hace la llamada a la tarea de acuerdo a
    t01 = T;                  // la configuración de tiempos Ts1
  }

  // Temporizacion tarea medicion de distancia
  ts2 = T - t02;
  if (ts2 >= Ts2) {
    TareaPID();             // en este espacio se hace la llamada a la tarea de acuerdo a
    t02 = T;                  // la configuración de tiempos Ts2
  }
}
