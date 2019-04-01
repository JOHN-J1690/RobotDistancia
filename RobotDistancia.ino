// Planificador
 
// -- Librerias ------------------------------------------
//Espacio para agregar las librerias necesitadas en el proyecto 



//---Llamada a las diferentes tareas realizadas en .h----
#include "Pines.h" 
#include "Led.h"            // Se debe incluir todas las tareas que se han agregado como .h entre comillas dobles
#include "SensorDistancia.h" 

#include "Comm.h"

 
// -- Variables de control de tiempo ---------------------
 
unsigned long int T;     // Tiempo total (microsegundos)
 
// -- Variables de temporizacion de tareas ---------------
 
// Tarea 1: LED

unsigned long int ts1;   // Tiempo parcial (tarea 1)
unsigned long int t01;   // Tiempo de la ultima ejecucion

 // Tarea 2: Sensor Ultrasonido

unsigned long int ts2;   // Tiempo parcial (tarea 1)
unsigned long int t02;   // Tiempo de la ultima ejecucion

// -- Funciones de definicion de tareas ------------------





//--------------------------------------------------------
 

// -- Inicializacion -------------------------------------
 
void setup() {
  // Inicializacion de temporizadores de tarea
  ts1 = 0;
  t01 = 0;
  ts2 = 0;
  t02 = 0;
    
  SetupLED();
  SetupUlt();
  SetupComm();
  SetupMOTOR();
} 
 
// -- Bucle principal ------------------------------------
 
void loop() { 
  // Actualizar tiempo
  T = millis();
  // Temporizacion tarea 1
  ts1 = T - t01;
  if (ts1 >= Ts1) {
    UpdateLED();              // en este espacio se hace la llamada a la tarea de acuerdo a
    t01 = T;                  // la configuración de tiempos Ts1
  }

  // Temporizacion tarea medicion de distancia
  ts2 = T - t02;
  if (ts2 >= Ts2) {
    tareaMOTOR();              // en este espacio se hace la llamada a la tarea de acuerdo a
    t02 = T;                  // la configuración de tiempos Ts1
  }
}
