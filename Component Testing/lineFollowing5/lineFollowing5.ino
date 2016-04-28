//Line sensor            Notes:
  //Pins
  #define LINE_EMITTER  2   //Unused
  #define LINE_ONE    4
  #define LINE_TWO    7
  #define LINE_THREE    8
  #define LINE_FOUR   11
  #define LINE_FIVE   12
  #define LINE_SIX    13
  //Settings
  #define LINE_NUM    6
  #define LINE_TIMEOUT  2500
//Motors
  //Pins
  #define MOTOR_R1    5
  #define MOTOR_R2    6
  #define MOTOR_L1    10
  #define MOTOR_L2    9
  //Settings
  #define BASIS_R  35
  #define BASIS_L  30
//PID Parameters
  #define SETPOINT  2750
  #define K_PROP      2.5   //Increase overshoot, decrease constant error
//  #define K_INT     5   //Increase overshoot, eliminate constant error
  #define K_DIFF      1   //Decrease overshoot, keep small for stability

#include <QTRSensors.h>
#include <Motor.h>

int turn = 0;
int lastError = 0;

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


void PID(){
  unsigned int position = lineSensor.readLine(lineValues);
  int error = SETPOINT - position;
  turn = K_PROP * error + K_DIFF * (error - lastError);
  Serial.println(turn);
  turn = map(turn,-5000,5000,-BASIS_R,BASIS_L);
  lastError = error;
}

boolean calibrateLineSensor(){
	delay(500);
	Serial.println("Hold the sensor over the high reflectance surface (line).");
	for (int i = 0; i < 100; i++){
		lineSensor.calibrate();
	}
	Serial.println("Hold the sensor over the low reflectance surface (background).");
	for (int i = 0; i < 100; i++){
		lineSensor.calibrate();
	}
	int boolSum = 0;
	for (int i; i<LINE_NUM; i++){
    Serial.print(lineSensor.calibratedMinimumOn[i]);
    Serial.print(" - ");
    Serial.print(lineSensor.calibratedMaximumOn[i]);
    Serial.println();
	}
}

boolean labviewStart(){
	return true;
}

void setup(){
	Serial.begin(115200);
  calibrateLineSensor();
  Serial.println("Done Calibrating!");
	//while (not calibrateLineSensor()){}
	//while (not labviewStart());
}

void loop(){
	PID();
  Serial.println(turn);
  if (turn>0){
    analogWrite(MOTOR_L1,BASIS_L - turn);
    analogWrite(MOTOR_R1,BASIS_R + turn);
  }else{
    analogWrite(MOTOR_L1,BASIS_L - turn);
    analogWrite(MOTOR_R1,BASIS_R + turn);
  }
}
