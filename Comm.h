#pragma once


String s = "";    //declaramos variable string de recepcion de datos


//
void SetupComm() {
  // put your setup code here, to run once:
Serial.begin(BAUD_RATE);     //Configura velocidad de comunicacion, inicializa puerto
}



void serialEvent() 
{ s="";   //incia la variable en vacio
  while (Serial.available())          //Mientras haya datos disponibles en el puerto serial
  {   char c = Serial.read();         //guarda en c lo que tiene el puerto serial
      while ( c != '\n' )            //Hasta que el caracter sea intro
        {     s = s + c ;             //concatenamos c con lo que tenia s
              delay(1);               //espera 1 ms
              c = Serial.read();      //guarda en c lo que tiene el puerto serial
        }
  }
    if ( s.startsWith("sp="))          //Si la cadena s inicia con "on"

     {
        String Temp = s.substring(3);
        Serial.println(Temp);
        SetPoint=Temp.toInt(); 

     }
    if ( s.startsWith("rc="))         //Si la cadena s inicia con "off"
    {
      String Temp = s.substring(3);
    //Setpoint=Temp.toInt(); 
   //  digitalWrite(ledPin,LOW);       //pin apaga
    }

    if ( s.startsWith("d?"))           //Si la cadena s inicia con "*"
    {
    Serial.println(distancia);           // el pin invierte su estado
    }
}