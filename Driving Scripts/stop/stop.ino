#include <QTRSensors.h>

#define NUM_SENSORS   6     // number of sensors used
#define TIMEOUT       2500  // waits for 2500 microseconds for sensor outputs to go low
#define EMITTER_PIN   2     // emitter is controlled by digital pin 2

// sensors 0 through 7 are connected to digital pins 3 through 10, respectively
QTRSensorsRC qtrrc((unsigned char[]) {
  4, 7, 8, 11, 12, 13
},
NUM_SENSORS, TIMEOUT, EMITTER_PIN);
unsigned int sensorValues[NUM_SENSORS];


void setup()
{
  delay(500);
  for (int i = 0; i < 400; i++)
  {
    qtrrc.calibrate();
  }

  Serial.begin(9600); // set the data rate in bits per second for serial data transmission
  for (int i = 0; i < NUM_SENSORS; i++)
  {
    Serial.print(qtrrc.calibratedMinimumOn[i]);
    Serial.print(' ');
  }
  Serial.println();
  for (int i = 0; i < NUM_SENSORS; i++)
  {
    Serial.print(qtrrc.calibratedMaximumOn[i]);
    Serial.print(' ');
  }
  Serial.println();
  Serial.println();
  delay(1000);
  analogWrite(6,50);
  analogWrite(10,50);
}


void loop()
{
  // read raw sensor values
  unsigned int position = qtrrc.readLine(sensorValues);
  int sum = 0;
  for(int i=0;i<6;i++){
    sum = sum + sensorValues[i];
  }
  if(sum<100){
    analogWrite(6,0);
    analogWrite(10,0);
  }
}
