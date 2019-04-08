class ROBOT{
  private:
  double Output;

  public:

  void ADELANTE(double Output){
              int temp = abs(Output);
              Motor1.run(FORWARD);
              Motor1.setSpeed(temp);
              Motor2.run(FORWARD);
              Motor2.setSpeed(temp);
    }

    void ATRAS(double Output){
              Motor1.run(BACKWARD);
              Motor1.setSpeed(Output);
              Motor2.run(BACKWARD);
              Motor2.setSpeed(Output);
      }

      void PARAR(double Output){
              Motor1.run(RELEASE);
              Motor2.run(RELEASE);
        }
  };
