//*************************Define pines del montaje***********************
long tiempoUlt;
//int TRIGGER = 7;   // triger
//int ECHO = 8;      // echo
double distancia,distAct;

void SetupDist()
{
  pinMode(TRIGGER, OUTPUT);
  pinMode(ECHO, INPUT);
}  

float dist()
{
  
      digitalWrite(TRIGGER,LOW); /* Por cuestiÃ³n de estabilizaciÃ³n del sensor*/
      delayMicroseconds(5);
      // lanzamos un pequeÃ±o pulso para activar el sensor
      digitalWrite(TRIGGER, HIGH);
      delayMicroseconds(10);
      digitalWrite(TRIGGER, LOW);
      
      // medimos el pulso de respuesta
      tiempoUlt = (pulseIn(ECHO, HIGH,6000)/2); // dividido por 2 por que es el 
                                           // tiempo que el sonido tarda
                                           // en ir y en volver
      // ahora calcularemos la distancia en cm
      // sabiendo que el espacio es igual a la velocidad por el tiempo
      // y que la velocidad del sonido es de 343m/s y que el tiempo lo 
      // tenemos en millonesimas de segundo
      distAct = double(tiempoUlt * 0.03432);


return  distancia = (distancia+distAct)/2;
      Serial.println(dist());
}            
