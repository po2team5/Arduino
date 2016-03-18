#include <Motor.h>
//Motor pins
#define MOTOR_L1      5
#define MOTOR_L2      6
#define MOTOR_R1      9
#define MOTOR_R2      10
#define BASIS_SNELHEID  10

#define turn_time 200

Motor motorLinks = Motor(MOTOR_L1,MOTOR_L2);
Motor motorRechts = Motor(MOTOR_R1,MOTOR_R2);

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}

void turn(boolean direction) {
  if(direction){
    motorLinks.setMotorSpeed(-BASIS_SNELHEID);
    motorRechts.setMotorSpeed(BASIS_SNELHEID);
  }else{
    motorLinks.setMotorSpeed(BASIS_SNELHEID);
    motorRechts.setMotorSpeed(-BASIS_SNELHEID);
  }
}

