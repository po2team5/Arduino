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
}


void loop()
{
  // read raw sensor values
  unsigned int position = qtrrc.readLine(sensorValues);

  // print the sensor values as numbers from 0 to 2500, where 0 means maximum reflectance and
  // 1023 means minimum reflectance
  for (unsigned char i = 0; i < NUM_SENSORS; i++)
  {
    Serial.print(sensorValues[i]);
    Serial.print('\t'); // tab to format the raw data into columns in the Serial monitor
  }
  Serial.println();
  //Serial.println(position);

  delay(1000);
}
