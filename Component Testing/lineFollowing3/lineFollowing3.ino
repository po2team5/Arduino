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
  #define LINE_TRESHOLD 600   //Treshold for boolean conversion
//Motors
  //Pins
  #define MOTOR_L1    5
  #define MOTOR_L2    6
  #define MOTOR_R1    9
  #define MOTOR_R2    10
  //Settings
  #define BASIS_SNELHEID  15
//PID Tuning Parameters
  #define K_PROP      1   //Increase overshoot, decrease constant error
  #define K_INT     1   //Increase overshoot, eliminate constant error
  #define K_DIFF      1   //Decrease overshoot, keep small for stability

#include <QTRSensors.h>
#include <Motor.h>

Motor motorLeft = Motor(MOTOR_L1,MOTOR_L2);
Motor motorRight = Motor(MOTOR_R1,MOTOR_R2);
int speedLeft;
int speedRight;
int turn = 0;

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

unsigned int rawLineValues[LINE_NUM];
bool lineValues[LINE_NUM];
int lineLastError = 0;


int PID(){
	parseSensors();
	
	int lineCurrentError = calculateProportional();
	int linePropValue = lineCurrentError;
	int lineDiffValue = lineLastError - lineCurrentError;
	int lineIntValue = lineIntValue + linePropValue;
	
	if (lineIntValue > 255) lineIntValue = 255;
	else if (lineIntValue < -255) lineIntValue = -255;
	turn = linePropValue*K_PROP + lineIntValue*K_INT + lineDiffValue*K_DIFF;
	if(turn > 255) return 255;
	else if (turn < -255) return -255;
	else return turn;
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

void parseSensors(){
	lineSensor.read(rawLineValues);
	for (int i; i<LINE_NUM; i++){
		lineValues[i] = (rawLineValues[i] > LINE_TRESHOLD);
	}
}

int calculateProportional(){
	int sum = 0;
	int lPos = 10;
	int rPos = 10;
  int lineCurrentError;
	for (int i; i<LINE_NUM/2; i++){
		sum = sum + lineValues[i] + lineValues[LINE_NUM-i];
		if(lineValues[i]==1) lPos = i-3;
		if(lineValues[LINE_NUM-i]==1) rPos = (LINE_NUM-i) - 4;
	}
	if(sum==0){
		if(lineLastError<0) lineCurrentError = -8;
		else lineCurrentError = 8;
	}
	else if(rPos!=10 && lPos!=10) lineCurrentError = 0;
	else if(lPos!=10) lineCurrentError=lPos*2+sum;
 	else if(rPos!=10) lineCurrentError=rPos*2-sum;
 	return lineCurrentError;
}

boolean labviewStart(){
	return true;
}

void setup(){
	Serial.begin(9600);
  calibrateLineSensor();
  Serial.println("Done Calibrating!");
	//while (not calibrateLineSensor()){}
	//while (not labviewStart());
	motorLeft.setMotorSpeed(BASIS_SNELHEID);
	motorRight.setMotorSpeed(BASIS_SNELHEID);
	motorLeft.startMotor();
	motorRight.startMotor();
}

void loop(){
	turn = PID();
	turn = map(turn, 0, 255, 0, BASIS_SNELHEID);
  for (int i; i<LINE_NUM; i++){
    Serial.print(lineValues[i]);
    Serial.print("\t");
  }
  Serial.println();
  Serial.println(turn);
  if (turn>0){
    motorLeft.setMotorSpeed(BASIS_SNELHEID - turn);
    motorRight.setMotorSpeed(BASIS_SNELHEID);
  }else{
    motorLeft.setMotorSpeed(BASIS_SNELHEID);
    motorRight.setMotorSpeed(BASIS_SNELHEID + turn);
  }
	delay(250);
}
