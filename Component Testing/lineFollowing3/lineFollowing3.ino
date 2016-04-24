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
  #define LINE_TRESHOLD 1400   //Treshold for boolean conversion
//Motors
  //Pins
  #define MOTOR_L1    5
  #define MOTOR_L2    6
  #define MOTOR_R1    9
  #define MOTOR_R2    10
  //Settings
  #define BASIS_SNELHEID  30
//PID Tuning Parameters
  #define K_PROP      10   //Increase overshoot, decrease constant error
  #define K_INT     5   //Increase overshoot, eliminate constant error
  #define K_DIFF      2   //Decrease overshoot, keep small for stability

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
int lineValues[LINE_NUM];
int lineLastError = 0;


int PID(){
	parseSensors();
	
	int lineCurrentError = calculateProportional();
	int linePropValue = lineCurrentError;
	int lineDiffValue = lineLastError - lineCurrentError;
	int lineIntValue = lineIntValue + linePropValue;
	lineLastError = lineCurrentError;
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

/*int calculateProportional(){
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
  Serial.print(lineCurrentError);
 	return lineCurrentError;
}*/

int calculateProportional(){
  int sum = 0;
  int lPos = 10;
  int rPos = 10;
  int lineCurrentError;
  for (int i=0; i<LINE_NUM/2; i++){
    sum=sum+lineValues[i];
    if(lineValues[i]==1){
      lPos=i-3;
    }
  }
  for (int i=LINE_NUM-1; i>=LINE_NUM/2; i--){
     sum=sum+lineValues[i];
     if(lineValues[i]==1){
       rPos=i-4;
     }
  }
  if(sum>=3){
     sum=2;
  }
  if(sum==0){
    if(lineLastError<0){
      lineCurrentError=-8;
    } else{
    lineCurrentError=8; }
    }
  else if((lPos!=10)&&(rPos!=10)){
    lineCurrentError=0; }
  else if(lPos!=10){
    lineCurrentError=lPos*2+sum;
  }
  else if(rPos!=10){
    lineCurrentError=rPos*2-sum;
  }
  Serial.print(rPos); Serial.print("\t"); Serial.print(lPos);
  Serial.println();
  Serial.println(lineCurrentError);
  return lineCurrentError;
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
	motorLeft.setMotorSpeed(BASIS_SNELHEID);
	motorRight.setMotorSpeed(BASIS_SNELHEID);
	motorLeft.startMotor();
	motorRight.startMotor();
}

void loop(){
	turn = PID();
  Serial.println(turn);
  if (turn>0){
    analogWrite(MOTOR_L1,BASIS_SNELHEID - turn);
    analogWrite(MOTOR_R1,BASIS_SNELHEID);
  }else{
    analogWrite(MOTOR_L1,BASIS_SNELHEID);
    analogWrite(MOTOR_R1,BASIS_SNELHEID + turn);
  }
	delay(250);
}
