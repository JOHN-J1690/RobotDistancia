class ROBOT{
  private:
  double Output;

  public:

  void ADELANTE(double Output){
              int temp = abs(Output);

              
              forward(motor1, motor2, temp);
    }

    void ATRAS(double Output){
            back(motor1, motor2, Output);
      }

      void PARAR(double Output){
              brake(motor1, motor2);
        }
  };
