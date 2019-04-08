
//librerias

const int offsetA = 1;
const int offsetB = 1;

#define AIN1 9
#define BIN1 7
#define AIN2 10
#define BIN2 8
#define PWMA 5
#define PWMB 6
#define STBY 12

Motor motor1 = Motor(AIN1, AIN2, PWMA, offsetA, STBY);
Motor motor2 = Motor(BIN1, BIN2, PWMB, offsetB, STBY);
