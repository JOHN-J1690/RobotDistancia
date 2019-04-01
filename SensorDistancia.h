
// -- ULTRASONIC management task -------------------------------------------------

float distancia;
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
  tiempo = pulseIn(ECHO, HIGH);
  
//  distancia = tiempo / 58.00;
distancia = double(tiempo * 0.03432/2);
/*
    Serial.print(distancia);
    Serial.println("cm");
    delay(100);
*/
return distancia;
}

void tareaDist()
{
  
  Serial.println(dist());
  }
