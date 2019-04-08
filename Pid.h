
#include <PID_v1.h>


//Define Variables we'll be connecting to
double Setpoint, Input, Output;

//Specify the links and initial tuning parameters
PID myPID(&Input, &Output, &Setpoint,10,3,5,P_ON_E, DIRECT); //P_ON_M specifies that Proportional on Measurement be used
                                                            //P_ON_E (Proportional on Error) is the default behavior
ROBOT robot;

void SetupPid()
{
  
  //initialize the variables we're linked to
  Input = dist();
  Setpoint = 15;

  //turn the PID on
    myPID.SetTunings(10,3,1);
    myPID.SetControllerDirection(DIRECT);
    myPID.SetSampleTime(100);
    myPID.SetOutputLimits(-255,255);
//    myPID.Initialize();  
    myPID.SetMode(AUTOMATIC);

}

void TareaPID()
{
  Input = dist();
  myPID.Compute();
//Serial.print(Input);
//Serial.print(" ");
//Serial.println(Output);

  
    if (Output==0)
    {
      robot.PARAR(Output);

    }
    else
    {   
      if (Output > 0)
        {    
          robot.ATRAS(Output);

        }
        else
        {     
          robot.ADELANTE(Output);

        }

      }

}
