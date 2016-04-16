#include <QTRSensors.h>
#include <Motor.h>
#include <PID_v1.h>
//Line sensor pins
#define LINE_EMITTER  2
#define LINE_ONE      4
#define LINE_TWO      7
#define LINE_THREE    8
#define LINE_FOUR     11
#define LINE_FIVE     12
#define LINE_SIX      13
#define LINE_NUM      6
#define LINE_TIMEOUT  2500
//Motor pins
#define MOTOR_L1      5
#define MOTOR_L2      6
#define MOTOR_R1      9
#define MOTOR_R2      10
#define BASIS_SNELHEID  15
//PID Tuning Parameters
  //Proportional
  #define KP_OUTER 3
  #define KP_MIDDLE 2
  #define KP_INNER 1
  //Integrating
  #define KI_OUTER 0.5
  #define KI_MIDDLE .3
  #define KI_INNER .1
  //Differentiating
  #define KD_OUTER 1
  #define KD_MIDDLE .6
  #define KD_INNER .3

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

double sp1,sp2,sp3,sp4,sp5,sp6
double in1,in2,in3,in4,in5,in6;
double out1,out2,out3,out4,out5,out6;

PID linePID1(&in1, &out1, &sp1, KP_OUTER, KI_OUTER, KD_OUTER, DIRECT);
PID linePID2(&in2, &out2, &sp2, KP_MIDDLE, KI_MIDDLE, KD_MIDDLE, DIRECT);
PID linePID3(&in3, &out3, &sp3, KP_INNER, KI_INNER, KD_INNER, DIRECT);
PID linePID4(&in4, &out4, &sp4, KP_INNER, KI_INNER, KD_INNER, DIRECT);
PID linePID5(&in5, &out5, &sp5, KP_MIDDLE, KI_MIDDLE, KD_MIDDLE, DIRECT);
PID linePID6(&in6, &out6, &sp6, KP_OUTER, KI_OUTER, KD_OUTER, DIRECT);

void setup() {
  delay(500);
  for (int i = 0; i < 100; i++){
    lineSensor.calibrate();
  }
  Serial.begin(9600);
}

void loop() {
  unsigned int position = lineSensor.readLine(lineValues);
  PIDScript(lineValues);
  delay(1);
}

void PIDScript(unsigned int values[]){
  
}

