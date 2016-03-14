#include <QTRSensors.h>
#include <Motor.h>

#define LINE_EMITTER  2
#define LINE_ONE      4
#define LINE_TWO      7
#define LINE_THREE    8
#define LINE_FOUR     11
#define LINE_FIVE     12
#define LINE_SIX      13
#define LINE_NUM      6
#define LINE_TIMEOUT  2500

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

int links;
int rechts;
int midden;

Motor motorLinks = Motor(5,6);
Motor motorRechts = Motor(9,10);

void setup() {
  delay(500);
  for (int i = 0; i < 100; i++){
    lineSensor.calibrate();
  }
  Serial.begin(9600);
  motorLinks
}

void loop() {
  unsigned int position = lineSensor.readLine(lineValues);
  parseLine(lineValues);
  Serial.print(links);
  Serial.print("\t");
  Serial.print(midden);
  Serial.print("\t");
  Serial.print(rechts);
  Serial.println();
  delay(250);
}

void parseLine(unsigned int values[]){
  int links1 = 1000 - values[0];
  int links2 = 1000 - values[1];
  int rechts1 = 1000 - values[4];
  int rechts2 = 1000 - values[5];
  links = (links1*2 + links2)/3;
  midden = 1000 - (values[2]+values[3])/2;
  rechts = (rechts1+rechts2*2)/3;
}

