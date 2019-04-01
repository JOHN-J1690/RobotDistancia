
#include <PID_v1.h>

//Define Variables we'll be connecting to
double Setpoint, Input, Output;

//Specify the links and initial tuning parameters
PID myPID(&Input, &Output, &Setpoint,10,3,5,P_ON_E, DIRECT); //P_ON_M specifies that Proportional on Measurement be used
                                                            //P_ON_E (Proportional on Error) is the default behavior

void SetupPid()
{
  //initialize the variables we're linked to
  Input = dist();
  Setpoint = 25;

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
      Motor1.run(RELEASE);
      Motor2.run(RELEASE);}
    else
    {   if (Output > 0)
        {     Motor1.run(BACKWARD);
              Motor1.setSpeed(Output);
              Motor2.run(BACKWARD);
              Motor2.setSpeed(Output);
          }
        else
        {     int temp = abs(Output);
              Motor1.run(FORWARD);
              Motor1.setSpeed(temp);
              Motor2.run(FORWARD);
              Motor2.setSpeed(temp);
          }

      }

}
