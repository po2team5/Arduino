/*
Program:			Motor Library

File:				Motor.h

Author:				John Tatum

Notes:				None
*/
#ifndef Motor_h
#define Motor_h

#include <Arduino.h>
//#include <WProgram.h>

class Motor {
	private:
	int intSpeed;
	int pin1;
	int pin2;
	bool isRunning;

	public:
	Motor();
	Motor(int intIn1, int intIn2);
	void setMotorSpeed(int intIn);
	int getMotorSpeed();
	bool isMotorRunning();
	void stopMotor();
	void startMotor();
};
#endif