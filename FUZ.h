
#include <Fuzzy.h>
#include <FuzzyComposition.h>
#include <FuzzyInput.h>
#include <FuzzyIO.h>
#include <FuzzyOutput.h>
#include <FuzzyRule.h>
#include <FuzzyRuleAntecedent.h>
#include <FuzzyRuleConsequent.h>
#include <FuzzySet.h>
//#include <Ultrasonic.h>

//Ultrasonic ultrasonic(2,3,11020); // (Trig PIN,Echo PIN, TIME PIN) 
Fuzzy*control = new Fuzzy();  //se declara el objeto fuzzy, se llamará, control.
//int distancia; //variable donde se guardará la distancia leida por el sensor
int set_point; //variable desde la que se controla el set point del sistema
int ERROR; // Es la resta entre el Set point y la distancia leida por el sensor
int POTENCIA; // Variable en la cual se guarda el nivel de potencia del PWM

ROBOT robot;
void Setupfuzzy() 
{
Serial.begin(9600);  //se inicia la transmisión  serial
//pinMode(8,OUTPUT);  //declaro los pines de salida del PWM
//pinMode(9,OUTPUT);  //declaro los pines de salida del PWM




//se declara el universo de entrada
FuzzyInput*error = new FuzzyInput(1);  //el universo de entrada será el error, el error se define como  Set Point-Distancia 
//se establecen los conjuntos del universo ERROR con sus respectivas funciones de membresia
///////////////////////////////////////////////////////////////////
FuzzySet*ng = new FuzzySet(-200, -197, -154, -128); //Negativo Grande, trapecio.
error->addFuzzySet(ng); //Se añade el conunto al universo de entrada.
//////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
FuzzySet*nm = new FuzzySet(-300, -300, -170, -90); //Negativo Mediano, trapecio.
error->addFuzzySet(nm); //Se añade el conunto al universo de entrada.
//////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
FuzzySet*nb = new FuzzySet(-170, -90, -90, -75); //Negativo Bajo, trapecio.
error->addFuzzySet(nb); //Se añade el conunto al universo de entrada.
//////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
FuzzySet*n = new FuzzySet(-75, -10, -10, 0); //Negativo, trapecio.
error->addFuzzySet(n); //Se añade el conunto al universo de entrada.
//////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
FuzzySet*cero = new FuzzySet(-10, 0, 0, 10); //Cero, triangular.
error->addFuzzySet(cero); //Se añade el conunto al universo de entrada.
//////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
FuzzySet*p = new FuzzySet(0, 32, 180, 200); //Positivo, trapecio.
error->addFuzzySet(p); //Se añade el conunto al universo de entrada.
//////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
FuzzySet*pb = new FuzzySet(50, 88, 180, 200); //Positivo Bajo, trapecio.
error->addFuzzySet(pb); //Se añade el conunto al universo de entrada.
//////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
FuzzySet*pm = new FuzzySet(86, 116, 180, 200); //Positivo Medio, trapecio.
error->addFuzzySet(pm); //Se añade el conunto al universo de entrada.
//////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
FuzzySet*pg = new FuzzySet(126, 155, 180, 200); //Positivo Grande, trapecio.
error->addFuzzySet(pg); //Se añade el conunto al universo de entrada.
//////////////////////////////////////////////////////////////////

control->addFuzzyInput(error); //se agrega al sistema fuzzy el universo con sus conjuntos.





//se declara la salida del sistema, en este caso será la POTENCIA
FuzzyOutput*potencia = new FuzzyOutput(1);
//se crean los cunjuntos pertenicientes a este universo, junto a sus funciones de membresia
///////////////////////////////////////////////////////////////////
FuzzySet*ultra_baja = new FuzzySet(0, 1, 24, 42); //Potencia ultra baja, trapecio.
potencia->addFuzzySet(ultra_baja); //Se añade el conunto al universo de salida.
//////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
FuzzySet*muy_baja = new FuzzySet(0, 1, 49, 69); //Potencia muy baja, trapecio.
potencia->addFuzzySet(muy_baja); //Se añade el conunto al universo de salida.
//////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
FuzzySet*media_baja = new FuzzySet(0, 1, 70, 90); //Potencia media baja, trapecio.
potencia->addFuzzySet(media_baja); //Se añade el conunto al universo de salida.
//////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
FuzzySet*baja = new FuzzySet(0, 1, 93, 114); //Potencia baja, trapecio.
potencia->addFuzzySet(baja); //Se añade el conunto al universo de salida.
//////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
FuzzySet*media = new FuzzySet(98, 122, 122, 150); //Potencia media, triangular.
potencia->addFuzzySet(media); //Se añade el conunto al universo de salida.
//////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
FuzzySet*alta = new FuzzySet(131, 149, 253, 255); //Potencia alta, trapecio.
potencia->addFuzzySet(alta); //Se añade el conunto al universo de salida.
//////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
FuzzySet*media_alta = new FuzzySet(159, 180, 253, 255); //Potencia media_alta, trapecio.
potencia->addFuzzySet(media_alta); //Se añade el conunto al universo de salida.
//////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
FuzzySet*muy_alta = new FuzzySet(183, 206, 253, 255); //Potencia muy_alta, trapecio.
potencia->addFuzzySet(muy_alta); //Se añade el conunto al universo de salida.
//////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
FuzzySet*ultra_alta = new FuzzySet(213, 235, 253, 255); //Potencia ultra_alta, trapecio.
potencia->addFuzzySet(ultra_alta); //Se añade el conunto al universo de salida.
//////////////////////////////////////////////////////////////////

control->addFuzzyOutput(potencia); //se agraga el universo de salida con sus conjuntos al sistema Fuzzy






//se establecen las reglas, cada regla debe tener un antecedente, una consecuencia y una asignación.

/////////////////////////////////Si error es CERO, entonces potencia es MEDIA//////////////////////////////////////////
FuzzyRuleAntecedent*si_error_es_cero = new FuzzyRuleAntecedent();
si_error_es_cero->joinSingle(cero);                    //Antecedente

FuzzyRuleConsequent*entonces_potencia_es_media = new FuzzyRuleConsequent();
entonces_potencia_es_media->addOutput(media);          //Consecuencia

FuzzyRule*regla_1 = new FuzzyRule(1, si_error_es_cero,entonces_potencia_es_media);
control->addFuzzyRule(regla_1);                        //Asignación
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////Si error es PG(POSITIVO GRANDE), entonces potencia es ULTRA BAJA////////////////////////
FuzzyRuleAntecedent*si_error_es_pg = new FuzzyRuleAntecedent();
si_error_es_pg->joinSingle(pg);                    //Antecedente

FuzzyRuleConsequent*entonces_potencia_es_ultra_baja = new FuzzyRuleConsequent();
entonces_potencia_es_ultra_baja->addOutput(ultra_baja);          //Consecuencia

FuzzyRule*regla_2 = new FuzzyRule(2, si_error_es_pg,entonces_potencia_es_ultra_baja);
control->addFuzzyRule(regla_2);                        //Asignación
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////Si error es PB(POSITIVO BAJO), entonces potencia es MEDIA BAJA////////////////////////
FuzzyRuleAntecedent*si_error_es_pb = new FuzzyRuleAntecedent();
si_error_es_pb->joinSingle(pb);                    //Antecedente

FuzzyRuleConsequent*entonces_potencia_es_media_baja = new FuzzyRuleConsequent();
entonces_potencia_es_media_baja->addOutput(media_baja);          //Consecuencia

FuzzyRule*regla_3 = new FuzzyRule(3, si_error_es_pb,entonces_potencia_es_media_baja);
control->addFuzzyRule(regla_3);                        //Asignación
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////Si error es P(POSITIVO), entonces potencia es BAJA////////////////////////
FuzzyRuleAntecedent*si_error_es_p = new FuzzyRuleAntecedent();
si_error_es_p->joinSingle(p);                    //Antecedente

FuzzyRuleConsequent*entonces_potencia_es_baja = new FuzzyRuleConsequent();
entonces_potencia_es_baja->addOutput(baja);          //Consecuencia

FuzzyRule*regla_4 = new FuzzyRule(4, si_error_es_p,entonces_potencia_es_baja);
control->addFuzzyRule(regla_4);                        //Asignación
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////Si error es N(NEGATIVO), entonces potencia es ALTA////////////////////////
FuzzyRuleAntecedent*si_error_es_n = new FuzzyRuleAntecedent();
si_error_es_n->joinSingle(n);                    //Antecedente

FuzzyRuleConsequent*entonces_potencia_es_alta = new FuzzyRuleConsequent();
entonces_potencia_es_alta->addOutput(alta);          //Consecuencia

FuzzyRule*regla_5 = new FuzzyRule(5, si_error_es_n,entonces_potencia_es_alta);
control->addFuzzyRule(regla_5);                        //Asignación
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////Si error es NB(NEGATIVO BAJO), entonces potencia es  MEDIA ALTA////////////////////////
FuzzyRuleAntecedent*si_error_es_nb = new FuzzyRuleAntecedent();
si_error_es_nb->joinSingle(nb);                    //Antecedente

FuzzyRuleConsequent*entonces_potencia_es_media_alta = new FuzzyRuleConsequent();
entonces_potencia_es_media_alta->addOutput(media_alta);          //Consecuencia

FuzzyRule*regla_6 = new FuzzyRule(6, si_error_es_nb,entonces_potencia_es_media_alta);
control->addFuzzyRule(regla_6);                        //Asignación
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////Si error es NG(NEGATIVO GRANDE), entonces potencia es ULTRA ALTA////////////////////////
FuzzyRuleAntecedent*si_error_es_ng = new FuzzyRuleAntecedent();
si_error_es_ng->joinSingle(ng);                    //Antecedente

FuzzyRuleConsequent*entonces_potencia_es_ultra_alta = new FuzzyRuleConsequent();
entonces_potencia_es_ultra_alta->addOutput(ultra_alta);          //Consecuencia

FuzzyRule*regla_7 = new FuzzyRule(7, si_error_es_ng,entonces_potencia_es_ultra_alta);
control->addFuzzyRule(regla_7);                        //Asignación
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////Si error es NM(NEGATIVO MEDIANO), entonces potencia es MUY ALTA////////////////////////
FuzzyRuleAntecedent*si_error_es_nm = new FuzzyRuleAntecedent();
si_error_es_nm->joinSingle(nm);                    //Antecedente

FuzzyRuleConsequent*entonces_potencia_es_muy_alta = new FuzzyRuleConsequent();
entonces_potencia_es_muy_alta->addOutput(muy_alta);          //Consecuencia

FuzzyRule*regla_8 = new FuzzyRule(8, si_error_es_nm,entonces_potencia_es_muy_alta);
control->addFuzzyRule(regla_8);                        //Asignación
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////Si error es PM(POSITIVO MEDIANO), entonces potencia es MUY BAJA////////////////////////
FuzzyRuleAntecedent*si_error_es_pm = new FuzzyRuleAntecedent();
si_error_es_pm->joinSingle(pm);                    //Antecedente

FuzzyRuleConsequent*entonces_potencia_es_muy_baja = new FuzzyRuleConsequent();
entonces_potencia_es_muy_baja->addOutput(muy_baja);          //Consecuencia

FuzzyRule*regla_9 = new FuzzyRule(9, si_error_es_pm,entonces_potencia_es_muy_baja);
control->addFuzzyRule(regla_9);                        //Asignación
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}

void TAREAFUZZY() 
{
  set_point=30; // Es la distancia donde se quiere estabilizar la pelota.
  distancia= dist(); //se guarda la distancia que lee el sensor en la variable distancia
  ERROR=set_point-distancia;  //se establece el valor del error restando el set point con la distancia que lee el sensor
  control->setInput(1,ERROR);   // se asigna al sistema Fuzzy llamado control una entrada con el valor de ERROR
  control->fuzzify();   //Se fuzifica el sistema
  POTENCIA = control->defuzzify(1); // Se des-fuzifica el sistema, guardando la salida en la variable potencia.
  int Output = POTENCIA;
  //analogWrite(5,POTENCIA);  //Se establece la potencia del PWM 
  //analogWrite(6,0);         //Se deja el pin 6 en cero.

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
  
  Serial.print("carro a: ");
  Serial.print(distancia); 
  Serial.print(" cm " );
  Serial.print(" Potencia: ");
  Serial.println(POTENCIA); 
  
  delay(5000);
  
}
