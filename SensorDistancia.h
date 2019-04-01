
// -- ULTRASONIC management task -------------------------------------------------

float distancia;
/********************************************************************
 * 
 * tarea de medicion de distancia por ultrasonidos
 * 
 * 
 * 
 * 
*********************************************************************/
float tiempo;

//*******************************************************************************
void SetupUlt(){
pinMode(TRIGGER, OUTPUT); 
pinMode(ECHO, INPUT);
}


//************************************************************************************

float dist() {
  digitalWrite(TRIGGER, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIGGER, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER, LOW);
  // Calcula la distancia midiendo el tiempo del estado alto del pin ECHO
  tiempo = pulseIn(ECHO, HIGH, 5827);
  
distancia = double(tiempo * 0.03432/2);

return distancia;
}

void tareaDist()
{
  Serial.println(dist());
}
