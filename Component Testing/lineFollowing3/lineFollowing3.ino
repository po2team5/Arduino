#include <Constants.h>
#include <QTRSensors.h>
#include <Motor.h>

Motor motorLeft = Motor(MOTOR_L1,MOTOR,L2);
Motor motorRight = Motor(MOTOR_R1,MOTOR,R2);
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
	Serial.println("Hold the sensor over the high reflectance surface (line).")
	for (int i = 0; i < 400; i++){
		lineSensor.calibrate();
	}
	Serial.println("Hold the sensor over the low reflectance surface (background).")
	for (int i = 0; i < 400; i++){
		lineSensor.calibrate();
	}
	int boolSum = 0;
	for (int i; i<LINE_NUM; i++) boolSum = boolSum + (lineSensor.calibratedMinimumOn[i]<lineSensor.calibratedMaximumOn[i]);
	return boolSum==0;
}

void parseSensors(){
	lineSensor.read(rawLineValues);
	for (int i; i<LINE_NUM; i++){
		lineValues[i] = (rawLineValues > LINE_TRESHOLD);
	}
}

int calculateProportional(){
	int sum = 0;
	int lPos = 10;
	int rPos = 10;
	for (int i; i<LINE_NUM/2; i++){
		sum = sum + lineValues[i] + lineValues[LINE_NUM-i];
		if(lineValues[i]==1) posLeft = i-3;
		if(lineValues[LINE_NUM-i]==1) posRight = (LINE_NUM-i) - 4;
	}
	if(sum==0){
		if(lineLastError<0) lineCurrentError = -8
		else lineCurrentError = 8
	}
	else if(posRight!=10 && posLeft!=10) lineCurrentError = 0;
	else if(posLeft!=10) error=posLeft*2+sum;
 	else if(posRight!=10) error=posRight*2-sum;
 	return lineCurrentError;
}

boolean labviewStart(){
	return true;
}

void setup(){
	Serial.begin(9600);
	while (not calibrateLineSensor()){}
	while (not labviewStart());
	motorLeft.setSpeed(BASIS_SNELHEID);
	motorRight.setSpeed(BASIS_SNELHEID);
	motorLeft.startMotor();
	motorRight.startMotor();
}

void loop(){
	turn = PID();
	turn = Map(turn, 0, 255, 0, BASIS_SNELHEID);
	motorLeft.setSpeed(BASIS_SNELHEID + (turn>0)*turn;);
	motorRight.setSpeed(BASIS_SNELHEID + (turn<0)*turn;);
	
}