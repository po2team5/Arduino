#include <Motor.h>

Motor motorA = Motor(5,6);
Motor motorB = Motor(9,10);



void setup() {
  motorA.setMotorSpeed(20);
  motorB.setMotorSpeed(20);
  motorA.startMotor();
  motorB.startMotor();

}

void loop() {

}
