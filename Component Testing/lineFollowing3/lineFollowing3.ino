#include <Constants.h>
#include <QTRSensors.h>
#include <Motor.h>

Motor motorLeft = Motor(MOTOR_L1,MOTOR,L2);
Motor motorRight = Motor(MOTOR_R1,MOTOR,R2);

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
int lineCurrentError = 0;
int lineLastError = 0;
int linePropValue = 0;		//proportional line following component
int lineIntValue = 0;		//integrating component
int lineDiffValue = 0;		//deriving component


void PID(){
	
}