#include <Motor.h>
//Motor pins
#define MOTOR_L1      5
#define MOTOR_L2      6
#define MOTOR_R1      9
#define MOTOR_R2      10
#define BASIS_SNELHEID  30

#define TURN_TIME 500

Motor motorLinks = Motor(MOTOR_L1,MOTOR_L2);
Motor motorRechts = Motor(MOTOR_R1,MOTOR_R2);

void setup() {
}

void loop() {
  motorLinks.setMotorSpeed(BASIS_SNELHEID);
  motorRechts.setMotorSpeed(BASIS_SNELHEID);
  motorLinks.startMotor();
  motorRechts.startMotor();
  delay(2000);
  motorLinks.stopMotor();
  motorRechts.stopMotor();
  turn(true);
}

int turn(boolean direction){
  if(direction){
    motorLinks.setMotorSpeed(-BASIS_SNELHEID);
    motorRechts.setMotorSpeed(BASIS_SNELHEID);
  }else{
    motorLinks.setMotorSpeed(BASIS_SNELHEID);
    motorRechts.setMotorSpeed(-BASIS_SNELHEID);
  }
  motorLinks.startMotor();
  motorRechts.startMotor();
  for(int i = 0; i<TURN_TIME; i++){
    if(labviewCheck()){
      delay(1);
    }
    else{
      return 0;
    }
  }
  motorLinks.stopMotor();
  motorRechts.stopMotor();
  return 1;
}

//voorlopige functie in afwachting van stop knop van labview
boolean labviewCheck(){
  return true;
}
