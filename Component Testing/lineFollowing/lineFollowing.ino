#include <QTRSensors.h>
#include <Motor.h>
//Line sensor pins
#define LINE_EMITTER  2
#define LINE_ONE      4
#define LINE_TWO      7
#define LINE_THREE    8
#define LINE_FOUR     11
#define LINE_FIVE     12
#define LINE_SIX      13
#define LINE_NUM      6
#define LINE_TIMEOUT  2500
//Motor pins
#define MOTOR_L1      5
#define MOTOR_L2      6
#define MOTOR_R1      9
#define MOTOR_R2      10
#define BASIS_SNELHEID  10

QTRSensorsRC lineSensor((unsigned char[])
{LINE_ONE,
LINE_TWO,
LINE_THREE,
LINE_FOUR,
LINE_FIVE,
LINE_SIX},
LINE_NUM,
LINE_TIMEOUT,
LINE_EMITTER);
unsigned int lineValues[LINE_NUM];

int links;
int rechts;
int midden;

Motor motorLinks = Motor(MOTOR_L1,MOTOR_L2);
Motor motorRechts = Motor(MOTOR_R1,MOTOR_R2);

int linksCorrectie = 0;
int rechtsCorrectie = 0;

void setup() {
  delay(500);
  for (int i = 0; i < 100; i++){
    lineSensor.calibrate();
  }
  Serial.begin(9600);
  motorLinks.setMotorSpeed(BASIS_SNELHEID);
  motorRechts.setMotorSpeed(-BASIS_SNELHEID);
  motorLinks.startMotor();
  motorRechts.startMotor();
}

void loop() {
  unsigned int position = lineSensor.readLine(lineValues);
  parseLine(lineValues);
  Serial.print(links);
  Serial.print("\t");
  Serial.print(midden);
  Serial.print("\t");
  Serial.print(rechts);
  Serial.println();
  checkDirection();
  updateMotorSpeed();
}

void parseLine(unsigned int values[]){
  int links1 = 1000 - values[0];
  int links2 = 1000 - values[1];
  int rechts1 = 1000 - values[4];
  int rechts2 = 1000 - values[5];
  links = (links1*2 + links2)/3;
  midden = 1000 - (values[2]+values[3])/2;
  rechts = (rechts1+rechts2*2)/3;
}

void checkDirection(){
  if(links>midden){
    linksCorrectie++;
  }else{
    linksCorrectie=0;
  }
  if(rechts>midden){
    rechtsCorrectie++;
  }else{
    rechtsCorrectie=0;
  }
  
}

void updateMotorSpeed(){
  motorLinks.setMotorSpeed(BASIS_SNELHEID + linksCorrectie);
  motorRechts.setMotorSpeed(BASIS_SNELHEID + rechtsCorrectie);
}

