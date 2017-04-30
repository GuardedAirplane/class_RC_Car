#include "Motor.h"

Motor motor(2,4,3);
Motor motor1(5,7,6);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  int currentSpeed = 200;
  Serial.println("First For-Loop");
  for (int i=0; i<=255; i++){
    motor.run(i);
    motor1.run(i);
    delay(10);
  }
  Serial.println("Second For-Loop");
  for (int i=254; i>=0; i--){
    motor.run(i);
    motor1.run(i);
    delay(10);
  }
  Serial.println("Third For-Loop");
  for (int i=0; i<=255; i++){
    motor.run(-i);
    motor1.run(-i);
    delay(10);
  }
  Serial.println("Forth For-Loop");
  for (int i=254; i>=0; i--){
    motor.run(-i);
    motor1.run(-i);
    delay(10);
  }
};
