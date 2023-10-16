#include <Arduino.h>

// put function declarations here:
int myFunction(int, int);

void setup() {
  // put your setup code here, to run once:
  int result = myFunction(2, 3);
  pinMode(LEDB, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(LEDB, HIGH);
  delay(1);
  digitalWrite(LEDB, LOW);
  delay(1);
}

// put function definitions here:
int myFunction(int x, int y) {
  return x + y;
}