#include <SharpIR.h>

SharpIR distanceSensor(A0,20150);

void setup() {
  Serial.begin(9600);
}

void loop() {
  Serial.println(distanceSensor.distance());
  delay(100);
}
