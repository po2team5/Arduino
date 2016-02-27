#include <Motor.h>

Motor motorA = Motor(3,5);
Motor motorB = Motor(6,9);



void setup() {
  motorA.setMotorSpeed(-1);
  motorB.setMotorSpeed(1);
  motorA.startMotor();
  motorB.startMotor();

}

void loop() {

}
