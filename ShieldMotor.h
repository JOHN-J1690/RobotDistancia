/**********************************************************
 * 
 * Programa manejo de motor para el robot de distancia
 * 
 * 
**********************************************************/
//librerias

AF_DCMotor Motor1(1);//puerto x1(shield) coneccion motor 1
AF_DCMotor Motor2(2);//puerto x2(shield) coneccion motor 2

int Speed = 255;//VELOCIDAD MÁXIMA DE LOS MOTORES 
void SetupMOTOR(){
  Motor1.run(RELEASE);          //inicializo motores
  Motor2.run(RELEASE);
  }

void pruebaMOTOR(){  
      Motor1.run(FORWARD);
      Motor1.setSpeed(Speed);
      
      Motor2.run(FORWARD); 
      Motor2.setSpeed(Speed);  
   Speed --;
   if (Speed <0)Speed = 255;
}
//
//void tareaMOTOR()
//{  
//  if (dist() > Setpoint)
//  {
//      Motor1.run(FORWARD);
//      Motor1.setSpeed(Speed);
//      Motor2.run(FORWARD);
//      Motor2.setSpeed(Speed);
//   }
//  else
//  {
//    Motor1.run(RELEASE);
//    Motor2.run(RELEASE);
//    }
//  
//}
